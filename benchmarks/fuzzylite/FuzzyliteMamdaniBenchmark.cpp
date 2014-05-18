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

#include <hayai.hpp>
#include <fl/Headers.h>


class MamdaniFixture : public hayai::Fixture
{
public:
	virtual void SetUp()
	{
        m_engine = new fl::Engine;
        m_engine->setName("SimpleMamdani");

        m_inputVariable1 = new fl::InputVariable;
        m_inputVariable1->setEnabled(true);
        m_inputVariable1->setName("i1");
        m_inputVariable1->setRange(0.000, 1.000);
        m_inputVariable1->addTerm(new fl::Gaussian("t1", 0.200, 0.200));
        m_inputVariable1->addTerm(new fl::Trapezoid("t2", 0.000, 0.350, 0.550, 1.000));
        m_inputVariable1->addTerm(new fl::PiShape("t3", 0.000, 0.730, 0.790, 1.000));
        m_inputVariable1->addTerm(new fl::SShape("t4", 0.000, 1.000));
        m_engine->addInputVariable(m_inputVariable1);

        m_inputVariable2 = new fl::InputVariable;
        m_inputVariable2->setEnabled(true);
        m_inputVariable2->setName("i2");
        m_inputVariable2->setRange(0.000, 1.000);
        m_inputVariable2->addTerm(new fl::Triangle("t1", -0.060, 0.500, 1.000));
        m_inputVariable2->addTerm(new fl::Rectangle("t2", 0.110, 0.370));
        m_inputVariable2->addTerm(new fl::Sigmoid("t3", 0.400, 5.000));
        m_engine->addInputVariable(m_inputVariable2);

        m_outputVariable = new fl::OutputVariable;
        m_outputVariable->setEnabled(true);
        m_outputVariable->setName("o1");
        m_outputVariable->setRange(0.000, 1.000);
        m_outputVariable->fuzzyOutput()->setAccumulation(new fl::Maximum);
        m_outputVariable->setDefuzzifier(new fl::Bisector(200));
        m_outputVariable->setDefaultValue(fl::nan);
        m_outputVariable->setLockValidOutput(false);
        m_outputVariable->setLockOutputRange(false);
        m_outputVariable->addTerm(new fl::Bell("t1", 0.260, 0.250, 3.000));
        m_outputVariable->addTerm(new fl::Sigmoid("t2", 0.500, 20.000));
        m_engine->addOutputVariable(m_outputVariable);

        fl::RuleBlock* ruleBlock = new fl::RuleBlock;
        ruleBlock->setEnabled(true);
        ruleBlock->setName("");
        ruleBlock->setConjunction(new fl::Minimum);
        ruleBlock->setDisjunction(new fl::Maximum);
        ruleBlock->setActivation(new fl::Minimum);
        ruleBlock->addRule(fl::Rule::parse("if i1 is t1 and i2 is t1 then o1 is t1", m_engine));
        ruleBlock->addRule(fl::Rule::parse("if i1 is t1 and i2 is t2 then o1 is t2", m_engine));
        ruleBlock->addRule(fl::Rule::parse("if i1 is t1 and i2 is t3 then o1 is t1", m_engine));
        ruleBlock->addRule(fl::Rule::parse("if i1 is t2 and i2 is t1 then o1 is t2", m_engine));
        ruleBlock->addRule(fl::Rule::parse("if i1 is t2 and i2 is t2 then o1 is t1", m_engine));
        ruleBlock->addRule(fl::Rule::parse("if i1 is t2 and i2 is t3 then o1 is t2", m_engine));
        ruleBlock->addRule(fl::Rule::parse("if i1 is t3 and i2 is t1 then o1 is t1", m_engine));
        ruleBlock->addRule(fl::Rule::parse("if i1 is t3 and i2 is t2 then o1 is t2", m_engine));
        ruleBlock->addRule(fl::Rule::parse("if i1 is t3 and i2 is t3 then o1 is t1", m_engine));
        ruleBlock->addRule(fl::Rule::parse("if i1 is t4 and i2 is t1 then o1 is t2", m_engine));
        ruleBlock->addRule(fl::Rule::parse("if i1 is t4 and i2 is t2 then o1 is t1", m_engine));
        ruleBlock->addRule(fl::Rule::parse("if i1 is t4 and i2 is t3 then o1 is t2", m_engine));
        m_engine->addRuleBlock(ruleBlock);
	}
	
	virtual void TearDown()
	{
	    delete m_engine;
	}

	fl::Engine* m_engine;
	fl::InputVariable* m_inputVariable1;
	fl::InputVariable* m_inputVariable2;
	fl::OutputVariable* m_outputVariable;
};


BENCHMARK_F(MamdaniFixture, Fuzzylite, 20, 100)
{
    m_inputVariable1->setInputValue(0.2f);
    m_inputVariable1->setInputValue(0.5f);
    m_engine->process();
    m_outputVariable->defuzzify();
}
