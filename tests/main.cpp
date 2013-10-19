/************************************************************************/
/** @mainpage

Unit tests for the library ElectronicHorizonLFLL.

*/
/************************************************************************/


#include <gtest/gtest.h>


int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	int k = RUN_ALL_TESTS();

#ifdef _WIN32
	system("PAUSE");
#endif
	return k;
}