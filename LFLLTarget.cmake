set(SOURCE_FILES

lfll/engine/detail/LFLLInputFuzzifierDetail.h
lfll/engine/detail/LFLLRulesEngineDetail.h
lfll/engine/detail/LFLLTupleDetail.h
lfll/engine/LFLLAggregator.h
lfll/engine/LFLLArray.h
lfll/engine/LFLLConsequence.h
lfll/engine/LFLLDefinitions.h
lfll/engine/LFLLInputFuzzifier.h
lfll/engine/LFLLMath.h
lfll/engine/LFLLMembership.h
lfll/engine/LFLLRule.h
lfll/engine/LFLLRulesEngine.h
lfll/engine/LFLLStaticAssert.h
lfll/engine/LFLLTuple.h
lfll/LFLL.h
lfll/LFLLConfig.h
lfll/mamdani/detail/LFLLMamdaniBisectorDefuzzifier.h
lfll/mamdani/detail/LFLLMamdaniCentroidDefuzzifier.h
lfll/mamdani/detail/LFLLMamdaniDefuzzifierDetail.h
lfll/mamdani/detail/LFLLMamdaniLargestOfMaximumDefuzzifier.h
lfll/mamdani/detail/LFLLMamdaniMeanOfMaximumDefuzzifier.h
lfll/mamdani/detail/LFLLMamdaniSmallestOfMaximumDefuzzifier.h
lfll/mamdani/LFLLMamdaniDefuzzifier.h
lfll/norms/LFLLCNorm.h
lfll/norms/LFLLSNorm.h
lfll/norms/LFLLTNorm.h
lfll/sugeno/detail/LFLLSugenoDefuzzifierDetail.h
lfll/sugeno/LFLLSugenoDefuzzifier.h
lfll/sugeno/LFLLSugenoTerms.h
lfll/terms/detail/LFLLAccumulatedDetail.h
lfll/terms/LFLLAccumulated.h
lfll/terms/LFLLBell.h
lfll/terms/LFLLBoolean.h
lfll/terms/LFLLFunction.h
lfll/terms/LFLLFunctor.h
lfll/terms/LFLLGaussian.h
lfll/terms/LFLLGaussianProduct.h
lfll/terms/LFLLLRamp.h
lfll/terms/LFLLPiShape.h
lfll/terms/LFLLRectangle.h
lfll/terms/LFLLRRamp.h
lfll/terms/LFLLSigmoid.h
lfll/terms/LFLLSigmoidDifference.h
lfll/terms/LFLLSigmoidProduct.h
lfll/terms/LFLLSingleton.h
lfll/terms/LFLLSShape.h
lfll/terms/LFLLTrapezoid.h
lfll/terms/LFLLTriangle.h
lfll/terms/LFLLZShape.h
)


  
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lfll")

# lfll custom target
install(DIRECTORY ${SOURCE_DIR}
    DESTINATION "${INSTALL_INCLUDE_DIR}"
	FILES_MATCHING PATTERN "*.h")
add_custom_target(lfll SOURCES ${SOURCE_FILES})

