/*
The MIT License (MIT)

Copyright (c) 2013 Nicolas Pauss

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef LFLLRULESENGINEDETAIL_H
#define LFLLRULESENGINEDETAIL_H

#include <lfll/engine/LFLLDefinitions.h>
#include <lfll/engine/LFLLRule.h>
#include <lfll/engine/LFLLStaticAssert.h>
#include <lfll/engine/LFLLTuple.h>


LFLL_BEGIN_NAMESPACE

// You should not use these structs but use LFLLRulesEngine instead.

namespace detail
{


/**
*  Calculate consequence of rule for the input InputIndex
*/
template<size_t InputIndex,
         size_t NI,
         size_t NR,
         size_t NO,
         class AndOp,
         class OrOp,
         class NotOp>
class LFLLAntecedentEngine
{
public:
    LFLLAntecedentEngine(const LFLLRule<NI, NO>& rule)
        : m_prevAntecedent(rule)
        , m_ignore(rule.inputVariables[InputIndex-1] == 0)
        , m_useNotOp(rule.inputVariables[InputIndex-1] < 0)
        , m_useOrOp(rule.orOperator)
        // if ignore then m_membershipIndex = 0
        // else if membershipIndex < 0, then
        //    m_membershipIndex = (-membershipIndex -1)
        // else
        //    m_membershipIndex = (membershipIndex -1)
        , m_membershipIndex(m_ignore ? 0 :
            ((m_useNotOp ?
                -rule.inputVariables[InputIndex-1] :
                rule.inputVariables[InputIndex-1]) - 1))
    {}


    template <class AntecedentTuple>
    inline scalar calculateAntecedent(
        const AntecedentTuple& antecedents,
        AndOp andOp,
        OrOp orOp,
        NotOp notOp) const
    {
        if (m_ignore) {
            return m_prevAntecedent.calculateAntecedent(
                antecedents, andOp, orOp, notOp);
        }

        const scalar val = m_useNotOp ?
            notOp(getLFLLTuple<InputIndex-1>(antecedents)->getVal(m_membershipIndex)) :
            getLFLLTuple<InputIndex-1>(antecedents)->getVal(m_membershipIndex);

        if (m_prevAntecedent.hasPrevValue()) {
            if (m_useOrOp) {
                return orOp(
                    m_prevAntecedent.calculateAntecedent(
                        antecedents, andOp, orOp, notOp),
                    val);
            } else {
                return andOp(
                    m_prevAntecedent.calculateAntecedent(
                        antecedents, andOp, orOp, notOp),
                    val);
            }
        }
        return val;
    }


    inline bool hasPrevValue() const
    {
        return m_prevAntecedent.hasPrevValue() || !m_ignore;
    }

private:
    const LFLLAntecedentEngine<InputIndex-1, NI, NR, NO, AndOp, OrOp, NotOp>
        m_prevAntecedent;
    const bool m_ignore;
    const bool m_useNotOp;
    const bool m_useOrOp;
    const lfll_uint m_membershipIndex;
};


template<size_t NI,
         size_t NR,
         size_t NO,
         class AndOp,
         class OrOp,
         class NotOp>
class LFLLAntecedentEngine<0, NI, NR, NO, AndOp, OrOp, NotOp>
{
public:
    LFLLAntecedentEngine(const LFLLRule<NI, NO>&)
    {}

    template <class AntecedentTuple>
    inline scalar calculateAntecedent(
        const AntecedentTuple&,
        AndOp,
        OrOp,
        NotOp) const
    {
        return ZERO_SCALAR;
    }


    inline bool hasPrevValue() const
    {
        return false;
    }
};

/**
 * Apply consequences to array dependending of the ouput OutputIndex
 */
template<size_t OutputIndex,
         size_t RuleIndex,
         size_t NI,
         size_t NR,
         size_t NO,
         class AndOp,
         class OrOp,
         class NotOp>
class LFLLConsequenceEngine
{
public:
    LFLLConsequenceEngine(const LFLLRule<NI, NO>& rule)
        : m_prevConsequence(rule)
        , m_ignore(rule.outputVariables[OutputIndex-1] == 0)
        , m_useNotOp(rule.outputVariables[OutputIndex-1] < 0)
        // if membershipIndex < 0, then
        //    m_membershipIndex = -membershipIndex
        // else m_membershipIndex = membershipIndex
        , m_membershipIndex(m_useNotOp ?
                -rule.outputVariables[OutputIndex-1] :
                rule.outputVariables[OutputIndex-1])
    {}


    template <class ConsequenceTuple>
    inline void setConsequences(
        const scalar val,
        ConsequenceTuple& consequences,
        NotOp notOp) const
    {
        // Apply previous consequence
        m_prevConsequence.setConsequences(val, consequences, notOp);

        if (m_ignore) {
            return;
        }

        getLFLLTuple<OutputIndex-1>(consequences)->setTermIndex(
            RuleIndex-1, m_membershipIndex);

        if (m_useNotOp) {
            getLFLLTuple<OutputIndex-1>(consequences)->setVal(
                RuleIndex-1, notOp(val));
        } else {
            getLFLLTuple<OutputIndex-1>(consequences)->setVal(
                RuleIndex-1, val);
        }
    }

private:
    const LFLLConsequenceEngine
        <OutputIndex-1, RuleIndex, NI, NR, NO, AndOp, OrOp, NotOp>
        m_prevConsequence;
    const bool m_ignore;
    const bool m_useNotOp;
    const lfll_uint m_membershipIndex;
};

template<size_t RuleIndex,
         size_t NI,
         size_t NR,
         size_t NO,
         class AndOp,
         class OrOp,
         class NotOp>
class LFLLConsequenceEngine<0, RuleIndex, NI, NR, NO, AndOp, OrOp, NotOp>
{
public:
    LFLLConsequenceEngine(const LFLLRule<NI, NO>& rule)
    {}

    template <class ConsequenceTuple>
    inline void setConsequences(
        const scalar,
        ConsequenceTuple&,
        NotOp) const
    {}
};


/**
 * Iterate through each rules and calculate consequences of rule with index
 * RuleIndex.
 */
template<size_t RuleIndex,
         size_t NI,
         size_t NR,
         size_t NO,
         class AndOp,
         class OrOp,
         class NotOp>
class LFLLRulesEngineImpl
{
public:
    inline LFLLRulesEngineImpl(
        const LFLLRules<NI, NR, NO>& rules)
        : m_prevRule(rules)
        , m_ancededents(rules.rules[RuleIndex-1])
        , m_consequences(rules.rules[RuleIndex-1])
        , m_weight(rules.rules[RuleIndex-1].weight)
    {}

    template <class AntecedentTuple, class ConsequenceTuple>
    inline void applyRules(
        const AntecedentTuple& antecedents,
        ConsequenceTuple& consequences,
        AndOp andOp,
        OrOp orOp,
        NotOp notOp) const
    {
        // Apply previous rule
        m_prevRule.applyRules(antecedents, consequences, andOp, orOp, notOp);

        // Calculate current rule
        const scalar val = m_ancededents.calculateAntecedent(antecedents, andOp, orOp, notOp);
        // Apply weight to current rule
        const scalar wval = lfll_math::srel(m_weight, ZERO_SCALAR, val);
        // Set computed consequence to array
        m_consequences.setConsequences(wval, consequences, notOp);
    }

private:
    const LFLLRulesEngineImpl<RuleIndex-1, NI, NR, NO, AndOp, OrOp, NotOp>
        m_prevRule;
    const LFLLAntecedentEngine<NI, NI, NR, NO, AndOp, OrOp, NotOp>
        m_ancededents;
    const LFLLConsequenceEngine<NO, RuleIndex, NI, NR, NO, AndOp, OrOp, NotOp>
        m_consequences;
    const scalar m_weight;
};

/**
 * If there is no more
 */
template<size_t NI,
         size_t NR,
         size_t NO,
         class AndOp,
         class OrOp,
         class NotOp>
class LFLLRulesEngineImpl<0, NI, NR, NO, AndOp, OrOp, NotOp>
{
public:
    inline LFLLRulesEngineImpl(const LFLLRules<NI, NR, NO>&)
    {}

    template <class AntecedentTuple, class ConsequenceTuple>
    inline void applyRules(
        const AntecedentTuple&,
        ConsequenceTuple&,
        AndOp,
        OrOp,
        NotOp) const
    {}
};

}


LFLL_END_NAMESPACE

#endif //LFLLRULESENGINEDETAIL_H
