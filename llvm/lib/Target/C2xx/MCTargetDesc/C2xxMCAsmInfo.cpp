#include "C2xxMCAsmInfo.h"
using namespace llvm;

void C2xxMCAsmInfo::anchor() { }

C2xxMCAsmInfo::C2xxMCAsmInfo(const Triple &TT) {
  // Since C2xx-GCC already generates 32-bit DWARF information, we will
  // also store 16-bit pointers as 32-bit pointers in DWARF, because using
  // 32-bit DWARF pointers is already a working and tested path for LLDB
  // as well.
  CodePointerSize = 4;
  CalleeSaveStackSlotSize = 2;

  CommentString = ";";
  SeparatorString = "{";

  AlignmentIsInBytes = false;
  UsesELFSectionDirectiveForBSS = true;

  SupportsDebugInformation = true;

  ExceptionsType = ExceptionHandling::DwarfCFI;
}
