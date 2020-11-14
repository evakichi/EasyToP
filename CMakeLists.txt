cmake_minimum_required(VERSION 3.10)

project(helloworld VERSION 0.5)
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER "/usr/local/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/local/bin/clang++")
set(_GNU_SOURCE)
set(_DEBUG)
set(__STDC_CONSTANT_MACROS)
set(__STDC_FORMAT_MACROS)
set(__STDC_LIMIT_MACROS)

set(STSTIC_SYSTEM_LIBRARIES
    /usr/lib/x86_64-redhat-linux6E/lib64/librt.a
    /usr/lib/x86_64-redhat-linux6E/lib64/libdl.a
    /usr/lib/x86_64-redhat-linux6E/lib64/libpthread.a
)
set(SHARED_SYSTEM_LIBRARIES
    /usr/lib64/libz.so
)
set(STATIC_LLVM_LIBRARIES 
    /usr/local/lib/libLLVMTableGen.a
    /usr/local/lib/libLLVMSymbolize.a
    /usr/local/lib/libLLVMDebugInfoPDB.a
    /usr/local/lib/libLLVMOrcJIT.a 
    /usr/local/lib/libLLVMOrcError.a 
    /usr/local/lib/libLLVMJITLink.a 
    /usr/local/lib/libLLVMObjectYAML.a 
    /usr/local/lib/libLLVMMCA.a 
    /usr/local/lib/libLLVMLTO.a 
    /usr/local/lib/libLLVMPasses.a 
    /usr/local/lib/libLLVMHelloNew.a 
    /usr/local/lib/libLLVMCoroutines.a 
    /usr/local/lib/libLLVMObjCARCOpts.a 
    /usr/local/lib/libLLVMExtensions.a 
    /usr/local/lib/libLLVMLineEditor.a 
    /usr/local/lib/libLLVMLibDriver.a 
    /usr/local/lib/libLLVMInterpreter.a 
    /usr/local/lib/libLLVMInterfaceStub.a 
    /usr/local/lib/libLLVMFuzzMutate.a 
    /usr/local/lib/libLLVMMCJIT.a 
    /usr/local/lib/libLLVMExecutionEngine.a 
    /usr/local/lib/libLLVMRuntimeDyld.a 
    /usr/local/lib/libLLVMDWARFLinker.a 
    /usr/local/lib/libLLVMDlltoolDriver.a 
    /usr/local/lib/libLLVMOption.a 
    /usr/local/lib/libLLVMDebugInfoGSYM.a 
    /usr/local/lib/libLLVMCoverage.a 
    /usr/local/lib/libLLVMXCoreDisassembler.a 
    /usr/local/lib/libLLVMXCoreCodeGen.a 
    /usr/local/lib/libLLVMXCoreDesc.a 
    /usr/local/lib/libLLVMXCoreInfo.a 
    /usr/local/lib/libLLVMX86Disassembler.a 
    /usr/local/lib/libLLVMX86AsmParser.a 
    /usr/local/lib/libLLVMX86CodeGen.a 
    /usr/local/lib/libLLVMX86Desc.a 
    /usr/local/lib/libLLVMX86Info.a 
    /usr/local/lib/libLLVMWebAssemblyDisassembler.a 
    /usr/local/lib/libLLVMWebAssemblyCodeGen.a 
    /usr/local/lib/libLLVMWebAssemblyDesc.a 
    /usr/local/lib/libLLVMWebAssemblyAsmParser.a 
    /usr/local/lib/libLLVMWebAssemblyInfo.a 
    /usr/local/lib/libLLVMSystemZDisassembler.a 
    /usr/local/lib/libLLVMSystemZCodeGen.a 
    /usr/local/lib/libLLVMSystemZAsmParser.a 
    /usr/local/lib/libLLVMSystemZDesc.a 
    /usr/local/lib/libLLVMSystemZInfo.a 
    /usr/local/lib/libLLVMSparcDisassembler.a 
    /usr/local/lib/libLLVMSparcCodeGen.a 
    /usr/local/lib/libLLVMSparcAsmParser.a 
    /usr/local/lib/libLLVMSparcDesc.a 
    /usr/local/lib/libLLVMSparcInfo.a 
    /usr/local/lib/libLLVMRISCVDisassembler.a 
    /usr/local/lib/libLLVMRISCVCodeGen.a 
    /usr/local/lib/libLLVMRISCVAsmParser.a 
    /usr/local/lib/libLLVMRISCVDesc.a 
    /usr/local/lib/libLLVMRISCVUtils.a 
    /usr/local/lib/libLLVMRISCVInfo.a 
    /usr/local/lib/libLLVMPowerPCDisassembler.a 
    /usr/local/lib/libLLVMPowerPCCodeGen.a 
    /usr/local/lib/libLLVMPowerPCAsmParser.a 
    /usr/local/lib/libLLVMPowerPCDesc.a 
    /usr/local/lib/libLLVMPowerPCInfo.a 
    /usr/local/lib/libLLVMNVPTXCodeGen.a 
    /usr/local/lib/libLLVMNVPTXDesc.a 
    /usr/local/lib/libLLVMNVPTXInfo.a 
    /usr/local/lib/libLLVMMSP430Disassembler.a 
    /usr/local/lib/libLLVMMSP430CodeGen.a 
    /usr/local/lib/libLLVMMSP430AsmParser.a 
    /usr/local/lib/libLLVMMSP430Desc.a 
    /usr/local/lib/libLLVMMSP430Info.a 
    /usr/local/lib/libLLVMMipsDisassembler.a 
    /usr/local/lib/libLLVMMipsCodeGen.a 
    /usr/local/lib/libLLVMMipsAsmParser.a 
    /usr/local/lib/libLLVMMipsDesc.a 
    /usr/local/lib/libLLVMMipsInfo.a 
    /usr/local/lib/libLLVMLanaiDisassembler.a 
    /usr/local/lib/libLLVMLanaiCodeGen.a 
    /usr/local/lib/libLLVMLanaiAsmParser.a 
    /usr/local/lib/libLLVMLanaiDesc.a 
    /usr/local/lib/libLLVMLanaiInfo.a 
    /usr/local/lib/libLLVMHexagonDisassembler.a 
    /usr/local/lib/libLLVMHexagonCodeGen.a 
    /usr/local/lib/libLLVMHexagonAsmParser.a 
    /usr/local/lib/libLLVMHexagonDesc.a 
    /usr/local/lib/libLLVMHexagonInfo.a 
    /usr/local/lib/libLLVMBPFDisassembler.a 
    /usr/local/lib/libLLVMBPFCodeGen.a 
    /usr/local/lib/libLLVMBPFAsmParser.a 
    /usr/local/lib/libLLVMBPFDesc.a 
    /usr/local/lib/libLLVMBPFInfo.a 
    /usr/local/lib/libLLVMAVRDisassembler.a 
    /usr/local/lib/libLLVMAVRCodeGen.a 
    /usr/local/lib/libLLVMAVRAsmParser.a 
    /usr/local/lib/libLLVMAVRDesc.a 
    /usr/local/lib/libLLVMAVRInfo.a 
    /usr/local/lib/libLLVMARMDisassembler.a 
    /usr/local/lib/libLLVMARMCodeGen.a 
    /usr/local/lib/libLLVMARMAsmParser.a 
    /usr/local/lib/libLLVMARMDesc.a 
    /usr/local/lib/libLLVMARMUtils.a 
    /usr/local/lib/libLLVMARMInfo.a 
    /usr/local/lib/libLLVMAMDGPUDisassembler.a 
    /usr/local/lib/libLLVMAMDGPUCodeGen.a 
    /usr/local/lib/libLLVMMIRParser.a 
    /usr/local/lib/libLLVMipo.a 
    /usr/local/lib/libLLVMInstrumentation.a 
    /usr/local/lib/libLLVMVectorize.a 
    /usr/local/lib/libLLVMLinker.a 
    /usr/local/lib/libLLVMIRReader.a 
    /usr/local/lib/libLLVMAsmParser.a 
    /usr/local/lib/libLLVMFrontendOpenMP.a 
    /usr/local/lib/libLLVMAMDGPUAsmParser.a 
    /usr/local/lib/libLLVMAMDGPUDesc.a 
    /usr/local/lib/libLLVMAMDGPUUtils.a 
    /usr/local/lib/libLLVMAMDGPUInfo.a 
    /usr/local/lib/libLLVMAArch64Disassembler.a 
    /usr/local/lib/libLLVMMCDisassembler.a 
    /usr/local/lib/libLLVMAArch64CodeGen.a 
    /usr/local/lib/libLLVMCFGuard.a 
    /usr/local/lib/libLLVMGlobalISel.a 
    /usr/local/lib/libLLVMSelectionDAG.a 
    /usr/local/lib/libLLVMAsmPrinter.a 
    /usr/local/lib/libLLVMDebugInfoDWARF.a 
    /usr/local/lib/libLLVMCodeGen.a 
    /usr/local/lib/libLLVMTarget.a 
    /usr/local/lib/libLLVMScalarOpts.a 
    /usr/local/lib/libLLVMInstCombine.a 
    /usr/local/lib/libLLVMAggressiveInstCombine.a 
    /usr/local/lib/libLLVMTransformUtils.a 
    /usr/local/lib/libLLVMBitWriter.a 
    /usr/local/lib/libLLVMAnalysis.a 
    /usr/local/lib/libLLVMProfileData.a 
    /usr/local/lib/libLLVMObject.a 
    /usr/local/lib/libLLVMTextAPI.a 
    /usr/local/lib/libLLVMBitReader.a 
    /usr/local/lib/libLLVMCore.a 
    /usr/local/lib/libLLVMRemarks.a 
    /usr/local/lib/libLLVMBitstreamReader.a 
    /usr/local/lib/libLLVMAArch64AsmParser.a 
    /usr/local/lib/libLLVMMCParser.a 
    /usr/local/lib/libLLVMAArch64Desc.a 
    /usr/local/lib/libLLVMMC.a 
    /usr/local/lib/libLLVMDebugInfoCodeView.a 
    /usr/local/lib/libLLVMDebugInfoMSF.a 
    /usr/local/lib/libLLVMBinaryFormat.a 
    /usr/local/lib/libLLVMAArch64Utils.a 
    /usr/local/lib/libLLVMAArch64Info.a 
    /usr/local/lib/libLLVMSupport.a 
    /usr/local/lib/libLLVMDemangle.a
)

enable_testing()
add_subdirectory(sources)
add_subdirectory(libs)
add_subdirectory(tests)


configure_file(include/helloworld.h.in include/helloworld.h)
add_test(NAME Test_1 COMMAND ./sources/helloworld)
set_tests_properties(Test_1 PROPERTIES PASS_REGULAR_EXPRESSION "hello world")
add_test(NAME Test_2 COMMAND ./sources/analyzer)
set_tests_properties(Test_2 PROPERTIES PASS_REGULAR_EXPRESSION "This is analyzer.")
add_test(NAME Test_3 COMMAND ./sources/creater)
set_tests_properties(Test_3 PROPERTIES PASS_REGULAR_EXPRESSION "This is pragma creater.")
add_test(NAME Test_4 COMMAND ./sources/optimizer)
set_tests_properties(Test_4 PROPERTIES PASS_REGULAR_EXPRESSION "This is optimizer.")
add_test(NAME Test_5 COMMAND ./sources/measure)
set_tests_properties(Test_5 PROPERTIES PASS_REGULAR_EXPRESSION "This is measure.")
