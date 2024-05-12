add_llvm_component_group(C2xx)

set(LLVM_TARGET_DEFINITIONS C2xx.td)

tablegen(LLVM C2xxGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM C2xxGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(C2xxCommonTableGen)

add_llvm_target(C2xxCodeGen
  C2xxSubtarget.cpp
  C2xxTargetMachine.cpp
  
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