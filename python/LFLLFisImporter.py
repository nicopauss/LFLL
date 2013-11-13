#!/usr/bin/env python
# -*- coding: utf-8 -*- 

import argparse
import sys
import os.path
import re


if sys.hexversion > 0x03000000:
    _range = range
    def _filter(function, iterable):
        return list(filter(function, iterable))
else:
    _range = xrange
    _filter = filter
    
    
def exitError(str):
    print(str)
    exit(-1)


def checkDictKeysIsSeq(d):
    for x in _range(1, len(d)+1):
        if x not in d:
            return False
    return True


class NumericalValueParser:
    def __init__(self, args):
        self.r = \
            re.compile('^[+-]?(?=([.]?)[0-9])[0-9]*(?:([.])[0-9]*)?((?:[Ee][+-]?[0-9]+)?)')
        if args.suffix is None:
            self.suffix = ''
        else:
            self.suffix = args.suffix
        
    
    def parse(self, val):
        m = self.r.match(val)
        if not m:
            exitError('Error, "{}" is not a correct numerical value'.format(val))
        val = m.group(0)
        
        # check if value contains a decimal point character or exponent character
        if not (m.group(1) or m.group(2) or m.group(3)):
            numChar = '.' # add one if not present
        else:
            numChar = ''
            
        return val + numChar + self.suffix
        
        
class NonNumericalValueParser:
    def __init__(self, args):
        pass
        
    def parse(self, val):
        return val     
        
        
        

class FuzzyValues:
    # Type enum
    TYPE_MAMDANI = 'LFLLMamdaniDefuzzifier'
    TYPE_SUGENO = 'LFLLSugenoDefuzzifier'
    
    # CNorm enum
    CNORM_NOT = 'LFLLNot'
    
    # TNorm enum
    TNORM_MIN = 'LFLLMin'
    TNORM_PROB = 'LFLLProbabilisticProduct'
    TNORM_BOUNDED_DIFF = 'LFLLBoundedDifference'
    TNORM_DRASTIC_PROD = 'LFLLDrasticProduct'
    TNORM_NILPOTENT_MIN = 'LFLLNilpotentMin'
    TNORM_EINSTEIN_PROD = 'LFLLEinsteinProduct'
    TNORM_HAMACHER_PROD = 'LFLLHamacherProduct'
    
    # SNorm enum
    SNORM_MAX = 'LFLLMax'
    SNORM_PROB = 'LFLLProbabilisticSum'
    SNORM_BOUNDED_SUM = 'LFLLBoundedSum'
    SNORM_DRASTIC_SUM = 'LFLLDrasticSum'
    SNORM_NILPOTENT_MAX = 'LFLLNilpotentMax'
    SNORM_EINSTEIN_SUM = 'LFLLEinsteinSum'
    SNORM_HAMACHER_SUM = 'LFLLHamacherSum'
    
    # Defuzzizer
    MAMDANI_BISECTOR = 'LFLLMamdaniBisector'
    MAMDANI_CENTROID = 'LFLLMamdaniCentroid'
    MAMDANI_MOM = 'LFLLMamdaniMeanOfMaximum'
    MAMDANI_SOM = 'LFLLMamdaniSmallestOfMaximum'
    MAMDANI_LOM = 'LFLLMamdaniLargestOfMaximum'
    SUGENO_AVG = 'LFLLSugenoWeightedAverage'
    SUGENO_SUM = 'LFLLSugenoWeightedSum'
    
    # Terms
    TERM_BELL = 'LFLLBell'
    TERM_BOOLEAN = 'LFLLBoolean'
    TERM_GAUSSIAN = 'LFLLGaussian'
    TERM_GAUSSIANPROD = 'LFLLGaussianProduct'
    TERM_LRAMP = 'LFLLLRamp'
    TERM_PISHAPE = 'LFLLPiShape'
    TERM_RECTANGLE = 'LFLLRectangle'
    TERM_RRAMP = 'LFLLRRamp'
    TERM_SIGMOID = 'LFLLSigmoid'
    TERM_SIGMOIDDIFF = 'LFLLSigmoidDifference'
    TERM_SIGMOIDPROD = 'LFLLSigmoidProduct'
    TERM_SINGLETON = 'LFLLSingleton'
    TERM_SSHAPE = 'LFLLSShape'
    TERM_TRAPEZOID = 'LFLLTrapezoid'
    TERM_TRIANGLE = 'LFLLTriangle'
    TERM_ZSHAPE = 'LFLLZShape'
    
    # Sugeno terms
    TERM_SUGENO_CONSTANT = 'LFLLSugenoZeroOrderTerm'
    TERM_SUGENO_LINEAR = 'LFLLSugenoFirstOrderTerm'
    

    class System:
        def __init__(self):
            self.name = None
            self.type = None
            self.andMethod = None
            self.orMethod = None
            self.notMethod = None
            self.impMethod = None
            self.aggMethod = None
            self.defuzzMethod = None
            
    class Input:
        def __init__(self):
            self.name = None
            self.mfs = {}

    class Output:
        def __init__(self):
            self.name = None
            self.range = None
            self.mfs = {}
    
    class Rule:
        def __init__(self):
            self.antecedents = []
            self.consequences = []
            self.weight = None
            self.orMethod = False
            
    class MF:
        def __init__(self):
            self.name = None
            self.type = None
            self.parameters = []
        
    def __init__(self):
        self.system = FuzzyValues.System()
        self.inputs = {}
        self.outputs = {}
        self.rules = []
    

class FisReader:

    FUZZY_VALUES_DICT = {
        # Type enum
        'mamdani': FuzzyValues.TYPE_MAMDANI,
        'sugeno': FuzzyValues.TYPE_SUGENO,
        
        # TNorm enum
        'min': FuzzyValues.TNORM_MIN,
        'prod': FuzzyValues.TNORM_PROB,
        'bdiff': FuzzyValues.TNORM_BOUNDED_DIFF,
        'dprod': FuzzyValues.TNORM_DRASTIC_PROD,
        'nmin': FuzzyValues.TNORM_NILPOTENT_MIN,
        'eprod': FuzzyValues.TNORM_EINSTEIN_PROD,
        'hprod': FuzzyValues.TNORM_HAMACHER_PROD,

        # SNorm enum
        'max': FuzzyValues.SNORM_MAX,
        'probor': FuzzyValues.SNORM_PROB,
        'sum': FuzzyValues.SNORM_BOUNDED_SUM,
        'dsum': FuzzyValues.SNORM_DRASTIC_SUM,
        'nmax': FuzzyValues.SNORM_NILPOTENT_MAX,
        'emax': FuzzyValues.SNORM_EINSTEIN_SUM,
        'hmax': FuzzyValues.SNORM_HAMACHER_SUM,

        # Defuzzizer
        'bisector': FuzzyValues.MAMDANI_BISECTOR,
        'centroid': FuzzyValues.MAMDANI_CENTROID,
        'mom': FuzzyValues.MAMDANI_MOM,
        'som': FuzzyValues.MAMDANI_SOM,
        'lom': FuzzyValues.MAMDANI_LOM,
        'wtaver': FuzzyValues.SUGENO_AVG,
        'wtsum': FuzzyValues.SUGENO_SUM,

        # Terms
        'gbellmf': FuzzyValues.TERM_BELL,
        'boolmf': FuzzyValues.TERM_BOOLEAN,
        'gaussmf': FuzzyValues.TERM_GAUSSIAN,
        'gauss2mf': FuzzyValues.TERM_GAUSSIANPROD,
        'lrampmf': FuzzyValues.TERM_LRAMP,
        'pimf': FuzzyValues.TERM_PISHAPE,
        'rectmf': FuzzyValues.TERM_RECTANGLE,
        'rrampmf': FuzzyValues.TERM_RRAMP,
        'sigmf': FuzzyValues.TERM_SIGMOID,
        'dsigmf': FuzzyValues.TERM_SIGMOIDDIFF,
        'psigmf': FuzzyValues.TERM_SIGMOIDPROD,
        'singmf': FuzzyValues.TERM_SINGLETON,
        'smf': FuzzyValues.TERM_SSHAPE,
        'trapmf': FuzzyValues.TERM_TRAPEZOID,
        'trimf': FuzzyValues.TERM_TRIANGLE,
        'zmf': FuzzyValues.TERM_ZSHAPE,
        
        # Sugeno terms
        'constant': FuzzyValues.TERM_SUGENO_CONSTANT,
        'linear': FuzzyValues.TERM_SUGENO_LINEAR,
        
    }



##
## Reader section classes
##
    class DefaultSectionReader:
        def readValue(self, line):
            try:
                (key, value) = line.split('=', 1)
                self.readKeyValue(key, value)
            except ValueError:
                exitError('Error: Parse error, non valid line "{}"'.format(line))

    class SystemSectionReader(DefaultSectionReader):
        def __init__(self, section, result):
            self.systemResult = result.system
            self.systemResult.notMethod = FuzzyValues.CNORM_NOT
    
        def readKeyValue(self, key, value):
            if (key == 'NumInputs' or key == 'NumOutputs' 
                or key == 'NumRules' or key == 'Version'):
                return
            
            if (value[0] != "'" or value[-1] != "'" or len(value) == 2):
                exitError('Error: Parse error, system non valid value "{}"'.format(value))
                
            value = value[1:-1]
        
            if (key == 'Name'):
                self.systemResult.name = value
            elif (key == 'Type'):
                self.systemResult.type = \
                    FisReader.FUZZY_VALUES_DICT.get(value, None)
                if (self.systemResult.type is None):
                    exitError('Error: Parse error, non valid fis type "{}"'.format(value))
            elif (key == 'AndMethod'):
                self.systemResult.andMethod = \
                    FisReader.FUZZY_VALUES_DICT.get(value, value)
            elif (key == 'OrMethod'):
                self.systemResult.orMethod = \
                    FisReader.FUZZY_VALUES_DICT.get(value, value)
            elif (key == 'NotMethod'):
                self.systemResult.notMethod = \
                    FisReader.FUZZY_VALUES_DICT.get(value, value)
            elif (key == 'ImpMethod'):
                self.systemResult.impMethod = \
                    FisReader.FUZZY_VALUES_DICT.get(value, value)
            elif (key == 'AggMethod'):
                self.systemResult.aggMethod = \
                    FisReader.FUZZY_VALUES_DICT.get(value, value)
            elif (key == 'DefuzzMethod'):
                self.systemResult.defuzzMethod = \
                    FisReader.FUZZY_VALUES_DICT.get(value, value)
            else:
                print('Warning: Parse warning, ignored unknown key "{}"'.format(key))
                
                
        def end(self):
            if (self.systemResult.name is None):
                exitError('Error: Parse error, system name is missing')
                
            if (self.systemResult.type is None):
                exitError('Error: Parse error, system type is missing')
                
            if (self.systemResult.andMethod is None):
                exitError('Error: Parse error, system andMethod is missing')
                
            if (self.systemResult.orMethod is None):
                exitError('Error: Parse error, system orMethod is missing')
                
            if (self.systemResult.defuzzMethod is None):
                exitError('Error: Parse error, system defuzzMethod is missing')
                
            if (self.systemResult.type == FuzzyValues.TYPE_MAMDANI):
                if (self.systemResult.impMethod is None):
                    exitError('Error: Parse error, system impMethod is missing')
                    
                if (self.systemResult.aggMethod is None):
                    exitError('Error: Parse error, system aggMethod is missing')
            
                
    class InputSectionReader(DefaultSectionReader):
        def __init__(self, section, result):
            self.inputResult = FuzzyValues.Input()
            self.mfReader = FisReader.MFReader()
            inputIndex = int(section[5:])
            if (inputIndex in result.inputs):
                exitError('Error: Parse error, input already exists for index "{}"'\
                    .format(inputIndex))
                    
            result.inputs[inputIndex] = self.inputResult
    
        def readKeyValue(self, key, value):
            if (key == 'Range' or key == 'NumMFs'):
                return
            
            if (key == 'Name'):
                if (value[0] != "'" or value[-1] != "'" or len(value) == 2):
                    exitError('Error: Parse error, input non valid name "{}"'.format(value))
                self.inputResult.name = value[1:-1]
                return
            
            if (key[:2] != 'MF'):
                print('Warning: Parse warning, ignored unknown key "{}"'.format(key))
                return
                
            if (len(key) == 2):
                exitError('Error: Parse error, input mf key non valid')
            
            mfIndex = int(key[2:])
            mfResult = FuzzyValues.MF()
            
            if (mfIndex in self.inputResult.mfs):
                exitError('Error: Parse error, input mf already exists for index "{}"'\
                    .format(mfIndex))
                
            self.inputResult.mfs[mfIndex] = mfResult
            self.mfReader.readMf(value, mfResult)
        
        def end(self):
            if (self.inputResult.name is None):
                exitError('Error: Parse error, input name is missing')
            
            if not checkDictKeysIsSeq(self.inputResult.mfs):
                exitError('Error: Parse error, input mfs are not in a correct sequence')
            
    class OutputSectionReader(DefaultSectionReader):
        def __init__(self, section, result):
            self.outputResult = FuzzyValues.Output()
            self.mfReader = FisReader.MFReader()
            outputIndex = int(section[6:])
            if (outputIndex in result.outputs):
                exitError('Error: Parse error, output already exists for index "{}"'\
                    .format(outputIndex))
            result.outputs[outputIndex] = self.outputResult
    
        def readKeyValue(self, key, value):
            if (key == 'NumMFs' or key == 'Default'):
                return
            
            if (key == 'Name'):
                if (value[0] != "'" or value[-1] != "'" or len(value) == 2):
                    exitError('Error: Parse error, output non valid name "{}"'.format(value))
                    
                self.outputResult.name = value[1:-1]
                return
                
            if (key == 'Range'):
                if (value[0] != "[" or value[-1] != "]" or len(value) == 2):
                    exitError('Error: Parse error, output non valid range "{}"'.format(value))
                    
                self.outputResult.range = _filter(None, value[1:-1].split()) 
                if len(self.outputResult.range) != 2:
                    exitError('Error: Parse error, output non valid range "{}"'.format(value))
                    
                return
            
            if (key[:2] != 'MF'):
                print('Warning: Parse warning, ignored unknown key "{}"'.format(key))
                return
                
            if (len(key) == 2):
                exitError('Error: Parse error, output mf key non valid')
            
            mfIndex = int(key[2:])
            mfResult = FuzzyValues.MF()
            
            if (mfIndex in self.outputResult.mfs):
                exitError('Error: Parse error, output mf already exists for index "{}"'\
                    .format(mfIndex))
            
            
            self.outputResult.mfs[mfIndex] = mfResult
            self.mfReader.readMf(value, mfResult)
        
        def end(self):
            if (self.outputResult.name is None):
                exitError('Error: Parse error, output name is missing')
                
            if (self.outputResult.range is None):
                exitError('Error: Parse error, output range is missing')
            
            if not checkDictKeysIsSeq(self.outputResult.mfs):
                exitError('Error: Parse error, output mfs are not in a correct sequence')
            
    class RulesSectionReader:
        def __init__(self, section, result):
            self.rules = result.rules
    
        def readValue(self, line):
            lineRe = re.compile('^([^,]+),\s*([^(]+)\(([^)]+)\)\s*:\s*([12])$')
            intRe = re.compile('-?[0-9]+')
            matchLine = lineRe.match(line)
            if matchLine is None:
                exitError('Error: Parse error, rule non valid value "{}"'.format(line))
            
            rule = FuzzyValues.Rule()
            
            rule.antecedents = intRe.findall(matchLine.group(1))
            rule.consequences = intRe.findall(matchLine.group(2))
            rule.weight = matchLine.group(3)
            rule.orMethod = (matchLine.group(4) == '2')
            
            self.rules.append(rule)
            
            
        def end(self):
            pass
    
    class MFReader:
        def readMf(self, mfValue, mfResult):
            (mfName, rest) = mfValue.split(':', 1)
            (mfType, mfParameters) = rest.split(',', 1)
            
            if (mfName[0] != "'" or mfName[-1] != "'" or len(mfName) == 2):
                exitError('Error: Parse error, mf non valid value "{}"'.format(mfName))
            
            if (mfType[0] != "'" or mfType[-1] != "'" or len(mfType) == 2):
                exitError('Error: Parse error, mf non valid value "{}"'.format(mfType))
            
            if (mfParameters[0] != "[" or mfParameters[-1] != "]"):
                exitError('Error: Parse error, mf non valid value "{}"'.format(mfParameters))
                
            mfName = mfName[1:-1]
            mfType = mfType[1:-1]
            mfParameters = mfParameters[1:-1]
            
            mfResult.name = mfName
            mfResult.type = FisReader.FUZZY_VALUES_DICT.get(mfType, mfType)
            # split and filter empty elements
            mfResult.parameters = filter(None, mfParameters.split()) 
            
            
        
            

##
## FisReader methods
##
    def __init__(self):
        self._sectionReader = None
    
    def readFile(self, args):
        self._sectionReader = None
        result = FuzzyValues()
        
        for line in args.file:
            line = line.strip()
            if (line == '' or line[0] == '%'):
                continue
            self._parseLine(line, result)
            
        if (self._sectionReader is not None):
            self._sectionReader.end()
        
        if not checkDictKeysIsSeq(result.inputs):
            exitError('Error: Parse error, inputs are not in a correct sequence')
            
        if not checkDictKeysIsSeq(result.outputs):
            exitError('Error: Parse error, outputs are not in a correct sequence')
            
        return result
            
    def _parseLine(self, line, result):
        if (line[0] == '[' and line[-1] == ']'):
            self._parseSection(line[1:-1], result)
        else:
            self._parseValue(line)
    
    def _parseSection(self, section, result):
        if (self._sectionReader is not None):
            self._sectionReader.end()
    
        if (section == 'System'):
            self._sectionReader = FisReader.SystemSectionReader(section, result)
        elif (section[:5] == 'Input'):
            self._sectionReader = FisReader.InputSectionReader(section, result)
        elif (section[:6] == 'Output'):
            self._sectionReader = FisReader.OutputSectionReader(section, result)
        elif (section == 'Rules'):
            self._sectionReader = FisReader.RulesSectionReader(section, result)
        else:
            exitError('Error: Parse file error, section unknown')
            
    
    def _parseValue(self, line):
        if self._sectionReader is None:
            exitError('Error: Parse file error, value in no section')
        self._sectionReader.readValue(line)
        
        
class HeaderWriter:
    def writeFile(self, args, fuzzyValues):
        fileName = args.output + '.' + args.headerExt
        headerGuard = ''.join(x for x in args.output.upper() \
            if not x.isspace()) + '_H'
        namespace = args.namespace
        nbInputs = len(fuzzyValues.inputs)
        nbOutputs = len(fuzzyValues.outputs)
        print('Writing file "{}"'.format(fileName))
        with open(fileName, 'w') as f:
            f.write("#ifndef {}\n".format(headerGuard))
            f.write("#define {}\n\n".format(headerGuard))
            f.write("#include <lfll/LFLL.h>\n\n")
            f.write("class {}\n".format(args.className))
            f.write("{\npublic:\n")
            f.write("\tstatic void process(\n")
            f.write("\t\tconst {0}LFLLArray<{1}>& inputs,\n"\
                .format(namespace, nbInputs))
            f.write("\t\t{0}LFLLArray<{1}>& outputs);\n\n"\
                .format(namespace, nbOutputs))
            f.write("private:\n")
            f.write("\t{}() ".format(args.className))
            f.write("{}\n};\n\n")
            f.write("#endif // {}\n".format(headerGuard))
            
class ImplWriter:
    def writeFile(self, args, fuzzyValues):
        headerFileName = args.output + '.' + args.headerExt
        implFileName = args.output + '.' + args.implExt
        namespace = args.namespace
        nbInputs = len(fuzzyValues.inputs)
        nbOutputs = len(fuzzyValues.outputs)
        nbRules = len(fuzzyValues.rules)
        
        inputs = [fuzzyValues.inputs[i] for i in _range(1, nbInputs+1)]
        outputs = [fuzzyValues.outputs[i] for i in _range(1, nbOutputs+1)]
        
        mfsInputs = [[x.mfs[i] for i in _range(1, len(x.mfs)+1)] for x in inputs]
        mfsOutputs = [[x.mfs[i] for i in _range(1, len(x.mfs)+1)] for x in outputs]
        
        isSugeno = (fuzzyValues.system.type == FuzzyValues.TYPE_SUGENO)
        
        if args.numeric:
            numeric = NumericalValueParser(args)
        else:
            numeric = NonNumericalValueParser(args)
        
        print('Writing file "{}"'.format(implFileName))
        with open(implFileName, 'w') as f:
            f.write('#include "{}"\n\n'.format(headerFileName))
            f.write('namespace\n{\n\n')
            f.write('\tconst size_t NbInputs = {};\n'.format(nbInputs))
            f.write('\tconst size_t NbOutputs = {};\n'.format(nbOutputs))
            f.write('\tconst size_t NbRules = {};\n\n'.format(nbRules))
            
            for i, x in enumerate(inputs):
                f.write('\tconst size_t NbMfsForInput{0} = {1};\n'\
                    .format(i+1, len(x.mfs)))
                    
            f.write('\n')
            
            for i, x in enumerate(inputs):
                for j, y in enumerate(mfsInputs[i]):
                    joinedParameters = ', '.join([numeric.parse(x) for x in y.parameters])
                    f.write('\tconst {0}{1} i{2}mf{3}({4});\n'\
                        .format(namespace, y.type, i+1, j+1, joinedParameters))
                f.write('\n')
                
            for i, x in enumerate(outputs):
                for j, y in enumerate(mfsOutputs[i]):
                    joinedParameters = ', '.join([numeric.parse(x) for x in y.parameters])
                    f.write('\tconst {0}{1}'\
                        .format(namespace, y.type))
                    if isSugeno:
                        if (y.type == FuzzyValues.TERM_SUGENO_LINEAR):
                            f.write('<{}>'.format(len(y.parameters)-1))
                        f.write(' o{0}t{1} = {{{2}}};\n'.format(i+1, j+1, joinedParameters))
                    else:
                        f.write(' o{0}mf{1}({2});\n'.format(i+1, j+1, joinedParameters))
                f.write('\n')
            
            f.write('\tconst {0}LFLLRules<NbInputs, NbRules, NbOutputs> rules = {{{{\n'\
                .format(namespace))
            notFirstRule = False
            for x in fuzzyValues.rules:
                if notFirstRule:
                    f.write(',\n')
                else:
                    notFirstRule = True
                joinedAnte = ', '.join(x.antecedents)
                joinedCons = ', '.join(x.consequences)
                orMethod = 'true' if x.orMethod else 'false'
                f.write('\t\t{{{{{0}}}, {{{1}}}, {2}, {3}}}'\
                    .format(joinedAnte, joinedCons, numeric.parse(x.weight), orMethod))
            f.write('\n\t}};\n')
            f.write('\tconst {0}LFLLRulesEngine<NbInputs, NbRules, NbOutputs> rulesEngine(rules);\n\n\n'\
                .format(namespace))
            
            
            
            for i, x in enumerate(inputs):
                f.write('\ttypedef {0}LFLLTuple<\n'.format(namespace))
                notFirstTuple = False
                for j, y in enumerate(mfsInputs[i]):
                    if notFirstTuple:
                        f.write(',\n')
                    else:
                        notFirstTuple = True
                    f.write('\t\tconst {0}{1}'.format(namespace, y.type))
                f.write('\n\t> Input{}Tuple;\n'.format(i+1))
                
                f.write('\tconst Input{0}Tuple input{0}Tuple = {1}makeLFLLTuple('\
                    .format(i+1, namespace))
                notFirstInput = False
                for j in _range(len(mfsInputs[i])):
                    if notFirstInput:
                        f.write(', ')
                    else:
                        notFirstInput = True
                    if (j % 8 == 0):
                        f.write('\n\t\t')
                    f.write('i{0}mf{1}'.format(i+1, j+1))
                f.write(');\n')
                f.write('\tconst {0}LFLLInputFuzzifier<Input{1}Tuple>'.format(namespace, i+1))
                f.write(' input{0}Fuzzifier(input{0}Tuple);\n\n'.format(i+1))
            f.write('\n')
            
            
            
            for i, x in enumerate(outputs):
                f.write('\ttypedef {0}LFLLTuple<\n'.format(namespace))
                notFirstTuple = False
                for j, y in enumerate(mfsOutputs[i]):
                    if notFirstTuple:
                        f.write(',\n')
                    else:
                        notFirstTuple = True
                    f.write('\t\tconst {0}{1}'.format(namespace, y.type))
                    if (y.type == FuzzyValues.TERM_SUGENO_LINEAR):
                        f.write('<{}>'.format(len(y.parameters)-1))
                        
                f.write('\n\t> Output{}Tuple;\n'.format(i+1))
                
                f.write('\tconst Output{0}Tuple output{0}Tuple = {1}makeLFLLTuple('\
                    .format(i+1, namespace))
                notFirstOutput = False
                for j in _range(len(mfsOutputs[i])):
                    if notFirstOutput:
                        f.write(', ')
                    else:
                        notFirstOutput = True
                    if (j % 8 == 0):
                        f.write('\n\t\t')
                    if isSugeno:
                        f.write('o{0}t{1}'.format(i+1, j+1))
                    else:
                        f.write('o{0}mf{1}'.format(i+1, j+1))
                f.write(');\n')
                
                if isSugeno:
                    f.write('\tconst {1}{2}<Output{0}Tuple, {1}{3}>\n\t\toutput{0}Defuzzifier'\
                        .format(i+1, namespace, fuzzyValues.system.type, \
                            fuzzyValues.system.defuzzMethod))
                    f.write('(output{0}Tuple);\n\n'.format(i+1))
                else:
                    startRange = numeric.parse(x.range[0])
                    endRange = numeric.parse(x.range[1])
                    f.write('\tconst {1}{2}<Output{0}Tuple,'\
                        .format(i+1, namespace, fuzzyValues.system.type))
                    f.write('\n\t\t{1}{2}, {1}{3}, {1}{4}>\n\t\toutput{0}Defuzzifier'\
                        .format(i+1, namespace, \
                            fuzzyValues.system.defuzzMethod, \
                            fuzzyValues.system.impMethod,
                            fuzzyValues.system.aggMethod))
                    f.write('(output{0}Tuple, {1}, {2});\n\n'\
                        .format(i+1, startRange, endRange))
                
            f.write('}\n\n\n')
            
            f.write('void {0}::process(\n\t\tconst {1}LFLLArray<{2}>& inputs,\n'\
                .format(args.className, namespace, nbInputs))
            f.write('\t\t{0}LFLLArray<{1}>& outputs)\n'.format(namespace, nbOutputs))
            f.write('{\n')
            
            for i in _range(nbInputs):
                f.write('\tconst {1}LFLLMembership<NbMfsForInput{0}> antecedent{0} =\n'\
                    .format(i+1, namespace))
                f.write('\t\tinput{0}Fuzzifier.fuzzifyVariable(inputs[{1}]);\n'\
                    .format(i+1, i))
            f.write('\n')
            
            for i in _range(nbOutputs):
                f.write('\t{1}LFLLConsequence<NbRules> consequence{0};\n'\
                    .format(i+1, namespace))
            f.write('\n')
            
            f.write('\ttypedef {0}LFLLTuple<\n'.format(namespace))
            notFirstInput = False
            for i in _range(nbInputs):
                if notFirstInput:
                    f.write(',\n')
                else:
                    notFirstInput = True
                f.write('\t\tconst {1}LFLLMembership<NbMfsForInput{0}>'\
                    .format(i+1, namespace))
            f.write('\n\t> AntecedentTuple;\n\n')
            
            f.write('\ttypedef {0}LFLLTuple<\n'.format(namespace))
            notFirstOutput = False
            for i in _range(nbOutputs):
                if notFirstOutput:
                    f.write(',\n')
                else:
                    notFirstOutput = True
                f.write('\t\t{0}LFLLConsequence<NbRules>'.format(namespace))
            f.write('\n\t> ConsequenceTuple;\n\n')
            
            
            f.write('\tconst AntecedentTuple antecedents = {0}makeLFLLTuple('\
                .format(namespace))
            notFirstInput = False
            for i in _range(nbInputs):
                if notFirstInput:
                    f.write(', ')
                else:
                    notFirstInput = True
                if (i % 4 == 0):
                    f.write('\n\t\t')
                f.write('antecedent{}'.format(i+1))
            f.write(');\n\n')
            
            f.write('\tConsequenceTuple consequences = {0}makeLFLLTuple('\
                .format(namespace))
            notFirstOutput = False
            for i in _range(nbOutputs):
                if notFirstOutput:
                    f.write(', ')
                else:
                    notFirstOutput = True
                if (i % 4 == 0):
                    f.write('\n\t\t')
                f.write('consequence{}'.format(i+1))
            f.write(');\n\n')
            
            f.write('\trulesEngine.applyRules(antecedents, consequences);\n\n')
            
            for i in _range(nbOutputs):
                f.write('\toutputs[{}] = '.format(i))
                if isSugeno:
                    f.write('output{0}Defuzzifier.defuzzifyConsequence(inputs, consequence{0});\n'\
                        .format(i+1))
                else:
                    f.write('output{0}Defuzzifier.defuzzifyConsequence(consequence{0});\n'\
                        .format(i+1))
                
            f.write('}\n')



if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description="Convert a Matlab/Octave FIS file into LFLL C++ code.")
    parser.add_argument('file', type=argparse.FileType('r'),
        help='Input file to export (.fis)')
    parser.add_argument('-o', dest='output', default=None,
        help='Output files name, default is input file\'s name')
    parser.add_argument('-c', '--class', dest='className', default=None,
        help='Class name, default is deduced by fis\'s name')
    parser.add_argument('-hpp', dest='headerExt', default='h',
        help='Header extension, default is "h"')
    parser.add_argument('-cpp', dest='implExt', default='cpp',
        help='Implementation extension, default is "cpp"')
    parser.add_argument('-n', '--namespace', dest='namespace', default=None,
        help='Use namespace for LFLL types')
    parser.add_argument('-f', '--float', dest='float', action='store_true',
        help='Force float type, equivalent to "-s f"')
    parser.add_argument('-s', '--suffix', dest='suffix', default=None,
        help='Add suffix to numerical value, implies "-num"')
    parser.add_argument('-num', '--numeric', dest='numeric', action='store_true',
        help='Check and convert terms parameters to numeric value')
        
    args = parser.parse_args()
    
    filePath = args.file.name
    fileName = os.path.basename(filePath)
    
    (inputRoot, inputExt) = os.path.splitext(fileName)
    
    if (args.output is None):
        args.output = inputRoot
    
    if args.namespace:
        args.namespace = args.namespace + '::'
    else:
        args.namespace = ''
        
    if args.float:
        args.suffix = 'f'
    
    if args.suffix:
        args.numeric = True
        
    fuzzyValues = FisReader().readFile(args)
    
    if (args.className is None):
        args.className = ''.join(x[0].upper() + x[1:] for x in \
            fuzzyValues.system.name.split(' '))
            
    HeaderWriter().writeFile(args, fuzzyValues)
    ImplWriter().writeFile(args, fuzzyValues)
