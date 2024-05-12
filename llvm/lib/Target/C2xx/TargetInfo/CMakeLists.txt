add_llvm_component_library(LLVMC2xxInfo
  C2xxTargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  C2xx
  )

