add_llvm_component_library(LLVMC2xxDesc
  C2xxMCTargetDesc.cpp
  
  LINK_COMPONENTS
  MC
  C2xxInfo
  Support

  ADD_TO_COMPONENT
  C2xx
  )