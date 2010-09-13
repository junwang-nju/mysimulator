
#include "property-list.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main() {
  ifstream ifs;
  Vector<unsigned int> sz;
  
  PropertyList<unsigned int> nbID;
  PropertyList<double> df;
  char buff[2048];
  ifs.open("12-conf.basic-move");
  allocate(sz,15037);
  for(unsigned int i=0,tu;i<15037;++i) {
    ifs>>tu;
    ifs>>sz[i];
    ifs.getline(buff,2047);
  }
  allocate(nbID,sz);
  allocate(df,sz);
  ifs.seekg(0,ios::beg);
  for(unsigned int i=0,tu;i<15037;++i) {
    ifs>>tu;
    ifs>>tu;
    for(unsigned int k=0;k<sz[i];++k)
    ifs>>nbID[i][k];
  }
  ifs.close();
  ifs.open("12623.df");
  double td;
  for(unsigned int i=0,tu,tv;i<50043;++i) {
    ifs>>tu;
    ifs>>tv;
    ifs>>td;
    for(unsigned int k=0;k<sz[tu];++k)
      if(nbID[tu][k]==tv) { df[tu][k]=td; break; }
    for(unsigned int k=0;k<sz[tv];++k)
      if(nbID[tv][k]==tu) { df[tv][k]=td; break; }
    ifs>>td;
  }
  ifs.close();

  Vector<unsigned int> maxdI;
  Vector<double> maxdf;
  allocate(maxdI,15037);
  allocate(maxdf,15037);
  for(unsigned int i=0,tu;i<15037;++i) {
    td=-1;
    tu=0;
    for(unsigned int k=0;k<sz[i];++k)
      if(df[i][k]>td) { td=df[i][k]; tu=k; }
    maxdI[i]=nbID[i][tu];
    maxdf[i]=td;
  }

  for(unsigned int i=0;i<15037;++i) {
    if(maxdI[i]>i) {
      if(maxdI[maxdI[i]]==i) {
        for(unsigned int k=0;k<sz[i];k++)
          if(nbID[i][k]==maxdI[i]) { nbID[i][k]=i; break; }
        for(unsigned int k=0;k<sz[maxdI[i]];k++)
          if(nbID[maxdI[i]][k]==i) { nbID[maxdI[i]][k]=maxdI[i]; break; }
      }
    }
  }
  
  Vector<int> cstate;
  Vector<unsigned int> ccache,rcache;
  unsigned int ncache,nrcache,nowc;
  allocate(cstate,15037);
  allocate(ccache,15037);
  allocate(rcache,15037);
  assign(cstate,-1);
  ncache=0;
  nowc=0;
  for(unsigned int i=0;i<15037;++i) {
    if(cstate[i]!=-1) continue;
    ncache=1;
    ccache[0]=i;
    cstate[i]=nowc;
    nrcache=0;
    do {
      for(unsigned int u=0;u<ncache;++u) {
        for(unsigned int k=0;k<sz[ccache[u]];++k) {
          if(cstate[nbID[ccache[u]][k]]==-1) {
            cstate[nbID[ccache[u]][k]]=nowc;
            rcache[nrcache]=nbID[ccache[u]][k];
            nrcache++;
          }
        }
      }
      swap(ccache,rcache);
      ncache=nrcache;
      nrcache=0;
    } while (ncache!=0);
    ++nowc;
  }
  for(unsigned int i=0;i<15037;++i)
    cout<<i<<"\t"<<cstate[i]<<endl;
  return 0;
}

