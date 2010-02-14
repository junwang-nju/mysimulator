
#include "ref-vector.h"
#include "var-vector.h"
#include "fix-vector.h"
#include <iostream>
using namespace std;

int main() {
  refVector<double> rdV;
  varVector<double> dV(10);
  rdV.refer(dV);
  dV=0;
  dV[2]=3;
  cout<<rdV<<endl;
  fixVector<double,20> fdV;
  rdV.refer(fdV);
  rdV.refer(dV,5,3);
  rdV.refer(dV,2,5);

  refVector<double> rdV2;
  rdV2.refer(rdV,1,3);

  cout<<rdV.RefInfo().content()<<endl;
  cout<<rdV.type()<<endl;

  cout<<"Test -- assign with constant or by element"<<endl;
  vI=3;
  cout<<vI<<endl;
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
  varVector<double> vDs(10);
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
  rdV.clear();
  cout<<rdV.IsAvailable()<<endl;
  cout<<rdV2.IsAvailable()<<endl;
  cout<<dV<<endl;
  rdV.refer(dV);
  rdV.refer(fdV);
  dV.clear();
  cout<<rdV.IsAvailable()<<endl;
  cout<<rdV2.IsAvailable()<<endl;
  dV.allocate(10);
  rdV.refer(dV);
  rdV2.refer(rdV);
  dV.clear();
  cout<<rdV.IsAvailable()<<endl;
  cout<<rdV2.IsAvailable()<<endl;
  return 1;
}

