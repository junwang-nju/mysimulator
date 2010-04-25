
#include "var-periodic-box.h"
#include <iostream>
using namespace std;

int main() {
  varPeriodicBox vPB;
  cout<<"Test -- allocate"<<endl;
  vPB.allocate(4);
  cout<<endl;

  cout<<"Test -- set through vector for box and constant for flag"<<endl;
  varVector<double> vb(4),v(4);
  vb[0]=1;
  vb[1]=1;
  vb[2]=2;
  vb[3]=3;
  vPB.Set(vb,PeriodicON);
  cout<<endl;

  cout<<"Test -- set through vectors for box and flag"<<endl;
  varVector<unsigned int> vf(4);
  vf=PeriodicON;  vf[1]=PeriodicOFF;
  vPB.Set(vb,vf);
  cout<<endl;

  cout<<"Test -- shift to main region"<<endl;
  v=5.4;
  vPB.shift2main(v);
  cout<<v<<endl;
  cout<<endl;

  cout<<"Test -- calculate displacement related to periodic box"<<endl;
  varVector<double> vm(4),vn(4);
  vm=1; vm[2]=15;
  vn=7.83; vn[3]=9.45;
  DisplacementFunc(vm,vn,v,vPB);
  cout<<v<<endl;
  cout<<endl;

  cout<<"Test -- type id"<<endl;
  cout<<vPB.TypeID<<endl;
  cout<<endl;

  cout<<"Test -- assign through another variable periodic box"<<endl;
  varPeriodicBox vPB2;
  vPB2.allocate(4);
  vPB2=vPB;
  cout<<vPB2.box()<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  vPB.clear();
  cout<<vPB.box().IsAvailable()<<endl;
  cout<<endl;

  return 1;
}

