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

#include <lfll/LFLLDefinitions.h>
#include <lfll/LFLLRule.h>
#include <lfll/LFLLStaticAssert.h>


LFLL_BEGIN_NAMESPACE

// You should not use these structs but use LFLLRulesEng ine instead.

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
        , m_andOp()
        , m_orOp()
        , m_notOp()
    {}


    template <class AntecedentTuple>
    inline dom calculateAntecedent(
        const AntecedentTuple& antecedents) const
    {
        if (m_ignore) {
            return m_prevAntecedent.calculateAntecedent(antecedents);
        }

        const dom val = m_useNotOp ?
            m_notOp(antecedents.get<InputIndex-1>()->getVal(m_membershipIndex)) :
            antecedents.get<InputIndex-1>()->getVal(m_membershipIndex);

        if (m_prevAntecedent.hasPrevValue()) {
            if (m_useOrOp) {
                return m_orOp(
                    m_prevAntecedent.calculateAntecedent(antecedents),
                    val);
            } else {
                return m_andOp(
                    m_prevAntecedent.calculateAntecedent(antecedents),
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
    const uint32_t m_membershipIndex;
    const AndOp m_andOp;
    const OrOp m_orOp;
    const NotOp m_notOp;
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
    inline dom calculateAntecedent(
        const AntecedentTuple&) const
    {
        return MIN_DOM;
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
        // if membershipIndex == 0, then m_membershipIndex = 0
        // else if membershipIndex < 0, then
        //    m_membershipIndex = (-membershipIndex -1)
        // else m_membershipIndex = (membershipIndex -1)
        , m_membershipIndex(m_ignore ? 0 :
            ((m_useNotOp ?
                -rule.outputVariables[OutputIndex-1] :
                rule.outputVariables[OutputIndex-1]) - 1))
        , m_notOp()
    {}


    template <class ConsequenceTuple>
    inline void setConsequences(
        const dom val,
        ConsequenceTuple& consequences) const
    {
        // Apply previous consequence
        m_prevConsequence.setConsequences(val, consequences);

        if (m_ignore) {
            return;
        }

        if (m_useNotOp) {
            consequences.get<OutputIndex-1>()->setVal(
                m_membershipIndex, RuleIndex-1, m_notOp(val));
        } else {
            consequences.get<OutputIndex-1>()->setVal(
                m_membershipIndex, RuleIndex-1, val);
        }
    }

private:
    const LFLLConsequenceEngine
        <OutputIndex-1, RuleIndex, NI, NR, NO, AndOp, OrOp, NotOp>
        m_prevConsequence;
    const bool m_ignore;
    const bool m_useNotOp;
    const uint32_t m_membershipIndex;
    const NotOp m_notOp;
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
        const dom,
        ConsequenceTuple&) const
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
    inline LFLLRulesEngineImpl(const LFLLRules<NI, NR, NO>& rules)
        : m_prevRule(rules)
        , m_ancededents(rules.rules[RuleIndex-1])
        , m_consequences(rules.rules[RuleIndex-1])
        , m_weight(rules.rules[RuleIndex-1].weight)
    {}

    template <class AntecedentTuple, class ConsequenceTuple>
    inline void applyRules(
         const AntecedentTuple& antecedents,
         ConsequenceTuple& consequences) const
    {
        // Apply previous rule
        m_prevRule.applyRules(antecedents, consequences);

        // Calculate current rule
        const dom val = m_ancededents.calculateAntecedent(antecedents);
        // Apply weight to current rule
        const dom wval = math::sround<dom>(m_weight, MIN_DOM, val);
        // Set computed consequence to array
        m_consequences.setConsequences(wval, consequences);
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
         ConsequenceTuple&) const
    {}
};

}


LFLL_END_NAMESPACE

#endif //LFLLRULESENGINEDETAIL_H
