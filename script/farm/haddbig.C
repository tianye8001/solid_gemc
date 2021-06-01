#include "TTree.h"

int haddbig() {
  TTree::SetMaxTreeSize( 1000000000000LL ); // 1 TB
  return 0;
}

namespace {
  static int i = haddbig();
}

