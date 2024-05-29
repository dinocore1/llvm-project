add_llvm_component_group(C2xx)

set(LLVM_TARGET_DEFINITIONS C2xx.td)

# tablegen(LLVM C2xxGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM C2xxGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM C2xxGenCallingConv.inc -gen-callingconv)
tablegen(LLVM C2xxGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM C2xxGenDisassemblerTables.inc -gen-disassembler)
tablegen(LLVM C2xxGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM C2xxGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM C2xxGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM C2xxGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(C2xxCommonTableGen)

add_llvm_target(C2xxCodeGen
  C2xxSubtarget.cpp
  C2xxTargetMachine.cpp
  C2xxMachineFunctionInfo.cpp
  C2xxInstrInfo.cpp
  C2xxRegisterInfo.cpp
  
  LINK_COMPONENTS
  Core
  Support
  C2xxInfo
  Target

  ADD_TO_COMPONENT
  C2xx
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)