#include <lfll/LFLLAggregator.h>
#include <lfll/LFLLMaxOperator.h>
#include <lfll/LFLLMath.h>

#include "LFLLTests.h"

using namespace math;

TEST(LFLLAggregatorTest, Agregator)
{
    const size_t NR = 3;
    const size_t NT = 2;

    LFLLAggregator<LFLLMaxOperator> aggregator;

    LFLLConsequence<NR, NT> consequence;

    consequence.membershipValue(0, 0) = scalarToDom(0.25f);
    consequence.membershipValue(0, 1) = scalarToDom(0.f);
    consequence.membershipValue(0, 2) = scalarToDom(0.f);

    consequence.membershipValue(1, 0) = scalarToDom(0.f);
    consequence.membershipValue(1, 1) = scalarToDom(0.75f);
    consequence.membershipValue(1, 2) = scalarToDom(0.10f);

    LFLLMembership<NT> membership = aggregator.aggregateConsequence(consequence);

    ASSERT_EQ(membership[0], scalarToDom(0.25f));
    ASSERT_EQ(membership[1], scalarToDom(0.75f));
}
