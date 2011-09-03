
#include "array/1d/allocate.h"
#include "array/1d/fill.h"
#include "array/1d/io.h"
#include "array/2d/allocate.h"
#include "array/2d/fill.h"
#include "io/console.h"
#include "intrinsic-type/exchange.h"
using namespace mysimulator;

#include <random>
using namespace std;

int main() {

  const unsigned int N=100;
  const unsigned int NC=N*3;

  Array1D<unsigned int> SiteState;
  Array1D<int> SiteGroup;
  Array2D<unsigned int> Connect;

  allocate(SiteState,N);
  fill(SiteState,1U);
  fill(SiteState,0U,20);

  allocate(SiteGroup,N);
  fill(SiteGroup,0);
  fill(SiteGroup,-1,20);

  allocate(Connect,NC,2U);
  unsigned int a,b;
  mt19937 engine;
  uniform_real_distribution<double> dist(0,1);
  bool fg;
  a=static_cast<unsigned int>(dist(engine)*N);
  b=static_cast<unsigned int>(dist(engine)*(N-1))+a;
  if(b>=N)  b-=N;
  if(a>b)   exchange(a,b);
  Connect[0][0]=a;
  Connect[0][1]=b;
  for(unsigned int i=1;i<NC;++i) {
    a=static_cast<unsigned int>(dist(engine)*N);
    b=static_cast<unsigned int>(dist(engine)*(N-1))+a;
    if(b>=N)  b-=N;
    if(a>b)   exchange(a,b);
    fg=false;
    for(unsigned int k=0;k<i;++k)
      if((a!=Connect[k][0])||(b!=Connect[k][1]))  { fg=true; break; }
    if(!fg) { --i; continue; }
    Connect[i][0]=a;
    Connect[i][1]=b;
  }

  int cid;
  cid=1;
  for(unsigned int i=0;i<N;++i) {
    if(SiteGroup[i]==-1)  SiteGroup[i]=cid;
    else continue;
    for(unsigned int k=0;k<NC;++k) {
      if(Connect[k][0]==i)  SiteGroup[Connect[k][1]]=cid;
      else
  }
  SiteGroup[0]=0;
  for(unsigned int i=0;i<NC;++i) {
    if(Connect[i][0]==0)  SiteGroup[Connect[i][1]]=0;
    else if(Connect[i][1]==0)   SiteGroup[Connect[i][0]]=0;
  }

  for(unsigned int i=0;i<N;++i)
    if(SiteGroup[i]==0) COut<<i<<Endl;

  release(Connect);
  release(SiteState);

  return 0;

}

