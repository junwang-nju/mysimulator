
#include "random-generator-mt-dsfmt.h"
#include "random-generator-interface.h"
#include "fix-vector.h"
#include "ref-vector.h"
#include <iostream>
#include <sstream>
using namespace std;

int main() {

  RandGenerator<dSFMT<>,double> rg;

  cout<<"Test -- init with a seed"<<endl;
  rg.Init(122378);
  rg.SetWithSeed(2487297);
  cout<<endl;

  cout<<"Test -- create a object with a seed"<<endl;
  RandGenerator<dSFMT<216091>,double> rg2(2721001);
  cout<<endl;

  cout<<"Test -- init with time"<<endl;
  rg.SetWithTime();
  cout<<endl;

  cout<<"Test -- init with an array"<<endl;
  fixVector<unsigned int,100> fv;
  for(unsigned int i=0;i<fv.size();++i)
    fv[i]=(1+i)*(2+i);
  rg.Init(fv);
  rg.Init(fv.data()+5,31);
  cout<<endl;

  cout<<"Test -- generate a 32-bit unsigned int"<<endl;
  cout<<rg.GenRandUint32()<<endl;
  cout<<endl;

  cout<<"Test -- generate a double in [1,2)"<<endl;
  cout<<rg.GenRand_Close1Open2()<<endl;
  cout<<endl;

  cout<<"Test -- generate a double in [0,1)"<<endl;
  cout<<rg.GenRand_Close0Open1()<<endl;
  cout<<endl;

  cout<<"Test -- generate a double in (0,1]"<<endl;
  cout<<rg.GenRand_Open0Close1()<<endl;
  cout<<endl;

  cout<<"Test -- generate a double in (0,1)"<<endl;
  cout<<rg.GenRand_Open0Open1()<<endl;
  cout<<endl;

  cout<<"Test -- default function"<<endl;
  cout<<rg()<<endl;
  double d;
  unsigned int ui;
  cout<<rg.Default(d)<<endl;
  cout<<rg.Default(ui)<<endl;
  cout<<endl;

  cout<<"Test -- fill array"<<endl;
  fixVector<double,501> dv;
  refVector<double> rv;
  dv=100;
  BuildRationalVector(rg,dv,rv);
  cout<<rv.data()-dv.data()<<endl;
  rg.FillArray_Close1Open2(rv.data(),382);
  cout<<dv<<endl;
  rg.FillArray_Close1Open2(rv);
  cout<<dv<<endl;
  cout<<endl;

  cout<<"Test -- save status"<<endl;
  fixVector<unsigned int,10> v1,v2;
  stringstream ss;
  rg.save(ss);
  for(unsigned int i=0;i<10;++i) v1[i]=rg.GenRandUint32();
  rg.load(ss);
  for(unsigned int i=0;i<10;++i) v2[i]=rg.GenRandUint32();
  for(unsigned int i=0;i<10;++i)
    if(v1[i]!=v2[i])  cout<<i<<"\tNot Equal!"<<endl;
  cout<<endl;

  cout<<"Test -- degree of uniformness"<<endl;
  fixVector<unsigned int,100000> hist;
  hist=0u;
  for(unsigned int i=0;i<100000000;++i)
    hist[static_cast<unsigned int>(rg()*100000)]++;
  fixVector<unsigned int,800> hhist;
  hhist=0U;
  for(unsigned int i=0;i<100000;++i)
    hhist[hist[i]-600]++;
  cout<<"(The data has been checked, but is not output here.)"<<endl;
  cout<<endl;

  return 1;
}

