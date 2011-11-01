
#include "io/error.h"
#include "array/2d/allocate.h"
#include "array/2d/copy.h"
#include "array/2d/fill.h"
#include "array/1d/io.h"
#include "array/1d/allocate.h"
#include "array/1d/copy.h"
#include "array/1d/scale.h"
#include "array/1d/shift.h"
#include "array/1d/norm.h"
#include "array/1d/fill.h"

#include "interaction/func/allocate.h"
#include "boundary/free/allocate.h"
#include "system/interface.h"
#include "minimizer/regular/allocate.h"

using namespace mysimulator;

int main() {
  FileInput FI;

  Array2D<double> Pos,NPos;
  unsigned int n;
  FI.open("1gb1.ca");
  FI>>n;
  allocate(Pos,n,3);
  for(unsigned int i=0;i<n;++i) FI>>Pos[i];
  FI.close();
  imprint(NPos,Pos);
  copy(NPos,Pos);

  Array2D<unsigned int> Cnt;
  FI.open("1gb1.cnt");
  FI>>n;
  allocate(Cnt,n,2);
  for(unsigned int i=0;i<n;++i) FI>>Cnt[i];
  FI.close();

  typedef InteractionFunc<FreeSpace,double> FuncType;
  typedef Array1D<int> IDType;
  typedef Array1D<Unique64Bit>  ParamType;

  Array1D<double> tvec;
  allocate(tvec,3);
  n=NPos.NumLines();
  System<double,Array1D<FuncType>,Array1D<IDType>,Array1D<ParamType>,FreeSpace,Array2D> S;
  S.loadCoor(NPos);
  allocate(S.UMask,n,3);
  fill(S.UMask,1U);
  fill(S.UMask[0],0U);
  fill(S.UMask[n-1],0U);
  copy(S.Mask,S.UMask);
  n=n-1+Cnt.NumLines();
  allocate(S.Func,n);
  for(unsigned int i=0;i<Cnt.NumLines();++i)  allocate(S.Func[i],LJ612,3);
  for(unsigned int i=Cnt.NumLines();i<n;++i)  allocate(S.Func[i],Harmonic,3);
  allocate(S.Param,n);
  for(unsigned int i=0;i<Cnt.NumLines();++i)  allocate(S.Param[i],LJ612NumberParameters);
  for(unsigned int i=0;i<Cnt.NumLines();++i) {
    S.Param[i][LJ612EqEnergyDepth].d=1.;
    copy(tvec,NPos[Cnt[i][0]-1]);
    shift(tvec,-1.,NPos[Cnt[i][1]-1]);
    S.Param[i][LJ612EqRadius].d=norm(tvec);
    BuildParameterLJ612<double>(S.Param[i]);
  }
  for(unsigned int i=Cnt.NumLines();i<n;++i)  allocate(S.Param[i],HarmonicNumberParameters);
  for(unsigned int i=Cnt.NumLines(),j=0;i<n;++i,++j) {
    S.Param[i][HarmonicEqStrength].d=100.;
    copy(tvec,NPos[j]);
    shift(tvec,-1.,NPos[j+1]);
    S.Param[i][HarmonicEqLength].d=norm(tvec);
    BuildParameterHarmonic<double>(S.Param[i]);
  }
  allocate(S.ID,n);
  for(unsigned int i=0;i<n;++i) allocate(S.ID[i],2);
  for(unsigned int i=0;i<Cnt.NumLines();++i) {
    S.ID[i][0]=Cnt[i][0]-1;
    S.ID[i][1]=Cnt[i][1]-1;
  }
  for(unsigned int i=Cnt.NumLines(),j=0;i<n;++i,++j) {
    S.ID[i][0]=j;
    S.ID[i][1]=j+1;
  }

  n=NPos.NumLines();
  copy(tvec,NPos[n-1]);
  shift(tvec,-1.,NPos[0]);
  shift(Pos[n-1],0.001,tvec);

  release(S);
  release(tvec);
  release(Cnt);
  release(NPos);
  release(Pos);
  return 0;
}

