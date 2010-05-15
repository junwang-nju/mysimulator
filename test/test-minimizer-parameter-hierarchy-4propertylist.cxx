
#include "minimizer-parameter-hierarchy-4propertylist.h"
#include "distance-evaluate-direct.h"
#include "free-space.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- initialize"<<endl;
  MinimizerParameter4PropertyListHierarchy<DistanceEvalDirect,FreeSpace> MP;
  cout<<endl;

  cout<<"Test -- introduce data"<<endl;
  Vector<unsigned int> sz;
  allocate(sz,5);
  for(unsigned int i=0;i<sz.size;++i) sz[i]=i+3;
  allocate(MP.iMask,sz(),sz.size);
  allocate(MP.dMask,sz(),sz.size);
  allocate(MP.DEval,3,5);
  allocate(MP.Geo,3);
  allocate(sz,3);
  for(unsigned int i=0;i<sz.size;++i) sz[i]=i+1;
  allocate(MP.ParamLst,sz(),sz.size);
  for(unsigned int i=0;i<3;++i)
  for(unsigned int k=0;k<sz[i];++k)
    allocate(MP.ParamLst[i][k],i*2+3);
  allocate(MP.IMLst,3);
  for(unsigned int i=0;i<MP.IMLst.size;++i) allocate(MP.IMLst[i]);
  allocate(sz,3);
  for(unsigned int i=0;i<sz.size;++i) sz[i]=i+1;
  allocate(MP.IdxLst,sz(),sz.size);
  for(unsigned int i=0;i<3;++i)
  for(unsigned int k=0;k<sz[i];++k)
    allocate(MP.IdxLst[i][k],i/2+2);
  finalize(MP);
  cout<<endl;

  cout<<"Test -- assign"<<endl;
  MinimizerParameter4PropertyListHierarchy<DistanceEvalDirect,FreeSpace> MP2;
  allocate(sz,5);
  for(unsigned int i=0;i<sz.size;++i) sz[i]=i+3;
  allocate(MP2.iMask,sz(),sz.size);
  allocate(MP2.dMask,sz(),sz.size);
  allocate(MP2.DEval,3,5);
  allocate(MP2.Geo,3);
  allocate(sz,3);
  for(unsigned int i=0;i<sz.size;++i) sz[i]=i+1;
  allocate(MP2.ParamLst,sz(),sz.size);
  for(unsigned int i=0;i<3;++i)
  for(unsigned int k=0;k<sz[i];++k)
    allocate(MP2.ParamLst[i][k],i*2+3);
  allocate(MP2.IMLst,3);
  for(unsigned int i=0;i<MP2.IMLst.size;++i) allocate(MP2.IMLst[i]);
  allocate(sz,3);
  for(unsigned int i=0;i<sz.size;++i) sz[i]=i+1;
  allocate(MP2.IdxLst,sz(),sz.size);
  for(unsigned int i=0;i<3;++i)
  for(unsigned int k=0;k<sz[i];++k)
    allocate(MP2.IdxLst[i][k],i/2+2);
  finalize(MP2);
  assign(MP2,MP);
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(MP2);
  cout<<endl;

  cout<<"Test -- check avalability"<<endl;
  cout<<IsAvailable(MP)<<endl;
  cout<<IsAvailable(MP2)<<endl;
  cout<<endl;

  cout<<"Test -- refer"<<endl;
  refer(MP2,MP);
  cout<<endl;

  cout<<"Test -- update"<<endl;
  updateParameter(MP2);
  cout<<endl;

  return 0;
}

