#include "Lresolution.h"

int test(){
  Lresolution tr("PVDIS");

  double kin[3] = {3.3, 23.0, 43.0};
  double res[4];
  
  tr.PrintResolution(kin, -1);
  tr.GetResolution(kin, res, "e-");

  tr.PrintDomain();

  return 0;
}
