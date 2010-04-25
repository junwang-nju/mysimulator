
#include "fix-periodic-box.h"
#include "var-vector.h"
#include <iostream>
using namespace std;

int main() {
  fixPeriodicBox<4> fPB;

  cout<<"Test -- set through vector for box and constant for flag"<<endl;
  varVector<double> vb(4),v(4);
  vb[0]=1;
  vb[1]=1;
  vb[2]=2;
  vb[3]=3;
  fPB.Set(vb,PeriodicON);
  cout<<endl;

  cout<<"Test -- set through vectors for box and flag"<<endl;
  varVector<unsigned int> vf(4);
  vf=PeriodicON;  vf[1]=PeriodicOFF;
  fPB.Set(vb,vf);
  cout<<endl;

  cout<<"Test -- shift to main region"<<endl;
  v=5.4;
  fPB.shift2main(v);
  cout<<v<<endl;
  cout<<endl;

  cout<<"Test -- calculate displacement related to periodic box"<<endl;
  varVector<double> vm(4),vn(4);
  vm=1; vm[2]=15;
  vn=7.83; vn[3]=9.45;
  DisplacementFunc(vm,vn,v,fPB);
  cout<<v<<endl;
  cout<<endl;

  cout<<"Test -- type id"<<endl;
  cout<<fPB.TypeID<<endl;
  cout<<endl;

  cout<<"Test -- assign through another variable periodic box"<<endl;
  fixPeriodicBox<3> fPB2;
  fPB2=fPB;
  cout<<fPB2.box()<<endl;
  cout<<endl;

  cout<<"Test -- clear"<<endl;
  fPB.clear();
  cout<<fPB.box().IsAvailable()<<endl;
  cout<<endl;

  return 1;
}

