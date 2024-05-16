#ifndef LLVM_LIB_TARGET_C2XX_MCTARGETDESC_C2XXFIXUPKINDS_H
#define LLVM_LIB_TARGET_C2XX_MCTARGETDESC_C2XXFIXUPKINDS_H

#include "llvm/MC/MCFixup.h"

#undef C2XX

namespace llvm {
namespace C2xx {

// This table must be in the same order of
// MCFixupKindInfo Infos[C2xx::NumTargetFixupKinds]
// in C2xxAsmBackend.cpp.
//
enum Fixups {
  // A 32 bit absolute fixup.
  fixup_32 = FirstTargetFixupKind,
  // A 10 bit PC relative fixup.
  fixup_10_pcrel,
  // A 16 bit absolute fixup.
  fixup_16,
  // A 16 bit PC relative fixup.
  fixup_16_pcrel,
  // A 16 bit absolute fixup for byte operations.
  fixup_16_byte,
  // A 16 bit PC relative fixup for command address.
  fixup_16_pcrel_byte,
  // A 10 bit PC relative fixup for complicated polymorphs.
  fixup_2x_pcrel,
  // A 16 bit relaxable fixup.
  fixup_rl_pcrel,
  // A 8 bit absolute fixup.
  fixup_8,
  // A 32 bit symbol difference fixup.
  fixup_sym_diff,

  // Marker
  LastTargetFixupKind,
  NumTargetFixupKinds = LastTargetFixupKind - FirstTargetFixupKind
};
} // end namespace C2xx
} // end namespace llvm

#endif
