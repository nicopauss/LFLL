#ifndef LFLLSIMPLESUGENO_H
#define LFLLSIMPLESUGENO_H

#include <lfll/LFLL.h>

class SimpleSugeno
{
public:
	static void process(
		const LFLLArray<2>& inputs,
		LFLLArray<1>& outputs);

private:
	SimpleSugeno() {}
};

#endif // LFLLSIMPLESUGENO_H
