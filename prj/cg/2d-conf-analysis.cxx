
#include "property-list.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdio>
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

  Vector<unsigned int> mindI;
  Vector<double> mindf;
  allocate(mindI,15037);
  allocate(mindf,15037);
  for(unsigned int i=0,tu;i<15037;++i) {
    td=1e10;
    tu=0;
    for(unsigned int k=0;k<sz[i];++k)
      if(df[i][k]<td) { td=df[i][k]; tu=k; }
    mindI[i]=nbID[i][tu];
    mindf[i]=td;
  }

  for(unsigned int i=0,j;i<15037;++i) {
    for(unsigned int k=0;k<sz[i];++k) {
      j=nbID[i][k];
      if(j==mindI[i])  continue;
      if(j>i) {
        if(mindI[j]==i) continue;
        //cout<<i<<"\t"<<j<<endl;
        nbID[i][k]=i;
        for(unsigned int l=0;l<sz[j];++l)
          if(nbID[j][l]==i) { nbID[j][l]=j; break; }
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
  //for(unsigned int i=0;i<15037;++i)
  //  cout<<i<<"\t"<<cstate[i]<<endl;
  /*
  nowc=0;
  for(unsigned int z=0;z<6000;++z) {
    nowc=0;
    for(unsigned int i=0;i<15037;++i)
      if(cstate[i]==z)  { cout<<i<<" "; nowc++; }
    cout<<nowc<<endl;
  }
  */
  ifs.open("12-conf.basic-move");
  for(unsigned int i=0,tu;i<15037;++i) {
    ifs>>tu;
    ifs>>tu;
    for(unsigned int k=0;k<sz[i];++k)
      ifs>>nbID[i][k];
  }
  ifs.close();
  double maxCB,minCB;
  for(int u=0;u<5000;++u)
  for(int v=u+1;v<5000;++v) {
    minCB=1e10;
    maxCB=0;
    nowc=0;
    for(unsigned int i=0,j;i<15037;++i) {
      if((cstate[i]!=u)&&(cstate[i]!=v))  continue;
      for(unsigned int k=0;k<sz[i];++k) {
        j=nbID[i][k];
        if(i>=j) continue;
        if(((cstate[i]==u)&&(cstate[j]==v))||
           ((cstate[i]==v)&&(cstate[j]==u))) {
          ++nowc;
          td=df[i][k];
          if(minCB>td)  minCB=td;
          if(maxCB<td)  maxCB=td;
        }
      }
    }
    if(nowc>0)
      cout<<u<<"\t"<<v<<"\t"<<minCB<<"\t"<<maxCB<<endl;
  }
  return 0;
}

