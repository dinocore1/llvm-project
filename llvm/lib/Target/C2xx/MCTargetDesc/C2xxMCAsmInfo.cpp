#include "C2xxMCAsmInfo.h"
using namespace llvm;

void C2xxMCAsmInfo::anchor() { }

C2xxMCAsmInfo::C2xxMCAsmInfo(const Triple &TT) {
  CodePointerSize = 4;
  CalleeSaveStackSlotSize = 2;

  CommentString = ";";
  SeparatorString = "{";

  AlignmentIsInBytes = false;
  UsesELFSectionDirectiveForBSS = true;

  SupportsDebugInformation = true;

  ExceptionsType = ExceptionHandling::DwarfCFI;
}
