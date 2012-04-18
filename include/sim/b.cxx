
#include "array/1d/allocate.h"
#include "array/1d/release.h"
#include "array/common/refer.h"
#include "array/1d/compare.h"
#include "array/1d/copy.h"
#include "array/1d/fill.h"
#include "array/1d/norm.h"
#include "array/1d/scale.h"
#include "array/1d/shift.h"
#include "array/1d/inverse.h"
#include <iostream>
using namespace std;
using namespace mysimulator;

int main() {
  double *p=allocate<double>(100);
  p[2]=1290.90;
  double *q=NULL;
  refer(q,p);
  cout<<size(q)<<endl;
  cout<<"=====  "<<IsSameSize(p,q)<<endl;
  cout<<"=====  "<<IsSame(p,q)<<endl;
  release(p);
  cout<<p<<endl;
  cout<<q[2]<<endl;
  cout<<size(q)<<endl;
  release(q);
  cout<<size(q)<<endl;
  return 0;
}

