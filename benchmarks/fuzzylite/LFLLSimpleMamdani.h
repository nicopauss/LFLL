#ifndef LFLLSIMPLEMAMDANI_H
#define LFLLSIMPLEMAMDANI_H

#include <lfll/LFLL.h>

class SimpleMamdani
{
public:
	static void process(
		const LFLLArray<2>& inputs,
		LFLLArray<1>& outputs);

private:
	SimpleMamdani() {}
};

#endif // LFLLSIMPLEMAMDANI_H
