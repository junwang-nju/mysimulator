
#include "ref-vector.h"
#include "var-vector.h"
#include "fix-vector.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- refer to varVector"<<endl;
  refVector<double> rdV;
  varVector<double> dV(10);
  rdV.refer(dV);
  cout<<endl;

  cout<<"Test -- operate original vector throgh reference vector"<<endl;
  dV=0;
  dV[2]=3;
  cout<<rdV<<endl;
  cout<<endl;

  cout<<"Test -- refer to fix-vector"<<endl;
  fixVector<double,20> fdV;
  cout<<endl;

  cout<<"Test -- refer to ref-vector"<<endl;
  rdV.refer(fdV);
  cout<<endl;

  cout<<"Test -- refer part of fix -vector"<<endl;
  rdV.refer(fdV,5,3);
  cout<<endl;

  cout<<"Test -- refer part of var-vector"<<endl;
  rdV.refer(dV,2,5);
  cout<<endl;

  cout<<"Test -- refer part through ref-vector"<<endl;
  refVector<double> rdV2;
  rdV2.refer(rdV,1,3);
  cout<<endl;

  cout<<"Test -- ref info of ref-vector"<<endl;
  cout<<rdV.RefInfo().content()<<endl;
  cout<<endl;

  cout<<"Test -- type of ref-vector"<<endl;
  cout<<rdV.type()<<endl;
  cout<<endl;

  cout<<"Test -- clear ref-vector"<<endl;
  rdV.clear();
  cout<<rdV.IsAvailable()<<endl;
  cout<<rdV2.IsAvailable()<<endl;
  cout<<dV<<endl;
  cout<<endl;

  cout<<"Test -- state of ref-vector after clear of var-vector"<<endl;
  rdV.refer(dV);
  rdV.refer(fdV);
  dV.clear();
  cout<<rdV.IsAvailable()<<endl;
  cout<<rdV2.IsAvailable()<<endl;
  cout<<endl;

  cout<<"Test -- state of ref-vector after re-use"<<endl;
  dV.allocate(10);
  rdV.refer(dV);
  rdV2.refer(rdV);
  dV.clear();
  cout<<rdV.IsAvailable()<<endl;
  cout<<rdV2.IsAvailable()<<endl;
  cout<<endl;

  cout<<"Test -- assign with constant or by element"<<endl;
  varVector<int> vvI(10);
  refVector<int> vI;
  vI.refer(vvI);
  vI=3;
  cout<<vI<<endl;
  varVector<double> vvD(10);
  refVector<double> vD;
  vD.refer(vvD);
  for(unsigned int i=0;i<vD.size();++i) vD[i]=i*0.5;
  cout<<vD<<endl;
  cout<<endl;

  cout<<"Test -- type"<<endl;
  cout<<vI.type()<<endl;
  cout<<vD.type()<<endl;
  cout<<endl;

  cout<<"Test -- scale with constant"<<endl;
  vD.scale(4);
  cout<<vD<<endl;
  cout<<endl;

  cout<<"Test -- initate with number of mers"<<endl;
  varVector<double> vvDs(20);
  refVector<double> vDs;
  vDs.refer(vvDs);
  cout<<endl;

  cout<<"Test -- scale with vector"<<endl;
  for(unsigned int i=0;i<vD.size();++i) vDs[i]=10.-i;
  vD.scale(vDs);
  cout<<vD<<endl;
  cout<<endl;

  cout<<"Test -- scale part with part of vector"<<endl;
  vD.scale(vDs,5,2,1,1,1);
  cout<<vD<<endl;
  cout<<endl;

  cout<<"Test -- scale part with constant"<<endl;
  vD.scale(0.5,5,1,1);
  cout<<vD<<endl;
  cout<<endl;

  cout<<"Test -- shift with a vector"<<endl;
  vD.shift(vDs);
  cout<<vD<<endl;
  cout<<endl;

  cout<<"Test -- shift with a constant"<<endl;
  vD.shift(-10);
  cout<<vD<<endl;
  cout<<endl;

  cout<<"Test -- shift with a constant and a vector"<<endl;
  vD.shift(2,vDs);
  cout<<vD<<endl;
  cout<<endl;

  cout<<"Test -- shift with a vector and a constant"<<endl;
  vD.shift(vDs,-2);
  cout<<vD<<endl;
  cout<<endl;

  cout<<"Test -- shift with two vectors"<<endl;
  fixVector<double,20> vvDf;
  refVector<double> vDf;
  vDf.refer(vvDf);
  for(unsigned int i=0;i<20;++i)    vDf[i]=i+1;
  vD.shift(vDf,vDs);
  cout<<vD<<endl;
  cout<<endl;
  
  cout<<"Test -- shift with two vectors and a constant"<<endl;
  vD.shift(-2,vDf,vDs);
  cout<<vD<<endl;
  cout<<endl;

  cout<<"Test -- shift part with a constant and part of a vector"<<endl;
  vD.shift(2,vDs,5,2,1,1,1);
  cout<<vD<<endl;
  cout<<endl;

  cout<<"Test -- shift part with a constant"<<endl;
  vD.shift(6,4,1,2);
  cout<<vD<<endl;
  cout<<endl;

  cout<<"Test -- scale-shift with two constants and a vector"<<endl;
  vD.scaleshift(0.5,2,vDs);
  cout<<vD<<endl;
  cout<<endl;

  cout<<"Test -- scale-shift with two constants and two vectors"<<endl;
  vD.scaleshift(2,3,vDf,vDs);
  cout<<vD<<endl;
  cout<<endl;

  cout<<"Test -- scale-shift part with two constants and part of a vector";
  cout<<endl;
  vD.scaleshift(0.5,2,vDs,4,2,1,1,2);
  cout<<vD<<endl;
  cout<<endl;

  cout<<"Test -- scale-shift part with two constants and part of two vectors";
  cout<<endl;
  vD.scaleshift(2,3,vDf,vDs,4,2,1,4,1,1,2);
  cout<<vD<<endl;
  cout<<endl;

  cout<<"Test -- data pointer and operator []"<<endl;
  vD.data()[2]=190;
  cout<<vD[2]<<endl;
  cout<<endl;

  cout<<"Test -- head and tail"<<endl;
  cout<<*(vD.begin())<<endl;
  cout<<*(vD.end()-1)<<endl;
  cout<<endl;

  cout<<"Test -- size"<<endl;
  cout<<vD.size()<<endl;
  cout<<endl;

  cout<<"Test -- availability of vector"<<endl;
  cout<<vD.IsAvailable()<<endl;
  cout<<endl;

  cout<<"Test -- assign with another vector"<<endl;
  vDf=vDs;
  cout<<vDf<<endl;
  cout<<endl;

  cout<<"Test -- assign part with part of another vector"<<endl;
  vDf.assign(vDs,5,2,1,3,2);
  cout<<vDf<<endl;
  cout<<endl;

  cout<<"Test -- assign part with a constant"<<endl;
  vDf.assign(82,7,1,2);
  cout<<vDf<<endl;
  cout<<endl;

  cout<<"Test -- exchange"<<endl;
  vDf.exchange(vDs);
  cout<<vDf<<endl;
  cout<<endl;

  cout<<"Test -- exchange part of vectors"<<endl;
  vDf.exchange(vDs,5,2,1,10,1);
  cout<<vDf<<endl;
  cout<<endl;

  cout<<"Test -- input from stream"<<endl;
  cin>>vD;
  cout<<vD<<endl;
  cout<<endl;

  return 1;
}

