
#ifndef EXAMPLELFLLENGINE_H
#define EXAMPLELFLLENGINE_H

#include <lfll/LFLLDefinitions.h>

class ExampleLFLLEngine
{
public:
    /**
     * Process the inputs using the fuzzy engine
     */
    static scalar process(scalar input1, scalar input2);

private:
  ExampleLFLLEngine() {}
};


#endif //EXAMPLELFLLENGINE_H
