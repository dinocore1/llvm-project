#ifndef LLVM_LIB_TARGET_C2XX_MCTARGETDESC_C2XXMCASMINFO_H
#define LLVM_LIB_TARGET_C2XX_MCTARGETDESC_C2XXMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class Triple;

class C2xxMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit C2xxMCAsmInfo(const Triple &TT);
};

} // namespace llvm

#endif
