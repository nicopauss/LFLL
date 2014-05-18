#include "LFLLSimpleSugeno.h"

namespace
{

	const size_t NbInputs = 2;
	const size_t NbOutputs = 1;
	const size_t NbRules = 12;

	const size_t NbMfsForInput1 = 4;
	const size_t NbMfsForInput2 = 3;

	const LFLLGaussian i1mf1(0.200, 0.200);
	const LFLLTrapezoid i1mf2(0.000, 0.350, 0.550, 1.000);
	const LFLLPiShape i1mf3(0.000, 0.730, 0.790, 1.000);
	const LFLLSShape i1mf4(0.000, 1.000);

	const LFLLTriangle i2mf1(-0.060, 0.500, 1.000);
	const LFLLRectangle i2mf2(0.110, 0.370);
	const rampmf i2mf3(0.000, 1.000);

	const LFLLSugenoZeroOrderTerm o1t1 = {0.250};
	const LFLLSugenoZeroOrderTerm o1t2 = {0.750};

	const LFLLRules<NbInputs, NbRules, NbOutputs> rules = {{
		{{1, 1}, {1}, 1, false},
		{{1, 2}, {2}, 1, false},
		{{1, 3}, {1}, 1, false},
		{{2, 1}, {2}, 1, false},
		{{2, 2}, {1}, 1, false},
		{{2, 3}, {2}, 1, false},
		{{3, 1}, {1}, 1, false},
		{{3, 2}, {2}, 1, false},
		{{3, 3}, {1}, 1, false},
		{{4, 1}, {2}, 1, false},
		{{4, 2}, {1}, 1, false},
		{{4, 3}, {2}, 1, false}
	}};
	const LFLLRulesEngine<NbInputs, NbRules, NbOutputs> rulesEngine(rules);


	typedef LFLLTuple<
		const LFLLGaussian,
		const LFLLTrapezoid,
		const LFLLPiShape,
		const LFLLSShape
	> Input1Tuple;
	const Input1Tuple input1Tuple = makeLFLLTuple(
		i1mf1, i1mf2, i1mf3, i1mf4);
	const LFLLInputFuzzifier<Input1Tuple> input1Fuzzifier(input1Tuple);

	typedef LFLLTuple<
		const LFLLTriangle,
		const LFLLRectangle,
		const rampmf
	> Input2Tuple;
	const Input2Tuple input2Tuple = makeLFLLTuple(
		i2mf1, i2mf2, i2mf3);
	const LFLLInputFuzzifier<Input2Tuple> input2Fuzzifier(input2Tuple);


	typedef LFLLTuple<
		const LFLLSugenoZeroOrderTerm,
		const LFLLSugenoZeroOrderTerm
	> Output1Tuple;
	const Output1Tuple output1Tuple = makeLFLLTuple(
		o1t1, o1t2);
	const LFLLSugenoDefuzzifier<Output1Tuple, LFLLSugenoWeightedAverage>
		output1Defuzzifier(output1Tuple);

}


void SimpleSugeno::process(
		const LFLLArray<2>& inputs,
		LFLLArray<1>& outputs)
{
	const LFLLMembership<NbMfsForInput1> antecedent1 =
		input1Fuzzifier.fuzzifyVariable(inputs[0]);
	const LFLLMembership<NbMfsForInput2> antecedent2 =
		input2Fuzzifier.fuzzifyVariable(inputs[1]);

	LFLLConsequence<NbRules> consequence1;

	typedef LFLLTuple<
		const LFLLMembership<NbMfsForInput1>,
		const LFLLMembership<NbMfsForInput2>
	> AntecedentTuple;

	typedef LFLLTuple<
		LFLLConsequence<NbRules>
	> ConsequenceTuple;

	const AntecedentTuple antecedents = makeLFLLTuple(
		antecedent1, antecedent2);

	ConsequenceTuple consequences = makeLFLLTuple(
		consequence1);

	rulesEngine.applyRules(antecedents, consequences);

	outputs[0] = output1Defuzzifier.defuzzifyConsequence(inputs, consequence1);
}
