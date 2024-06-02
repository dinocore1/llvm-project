include_directories( ${CMAKE_CURRENT_BINARY_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/.. )

add_llvm_component_library(LLVMC2xxAsmParser
  C2xxAsmParser.cpp

  LINK_COMPONENTS
  C2xxDesc
  C2xxInfo
  CodeGenTypes
  MC
  MCParser
  Support
  TargetParser

  ADD_TO_COMPONENT
  C2xx
  )

