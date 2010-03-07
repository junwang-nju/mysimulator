
#include "random-generator-interface.h"
#include "random-generator-mt-sfmt.h"
#include "fix-vector.h"
#include <iostream>
#include <sstream>
using namespace std;

int main() {

  RandGenerator<SFMT<>,double> rg;

  cout<<"Test -- init with a seed"<<endl;
  rg.Init(122378);
  rg.SetWithSeed(2487297);
  cout<<endl;

  cout<<"Test -- create a object with a seed"<<endl;
  RandGenerator<SFMT<216091>,double> rg2(2721001);
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

  cout<<"Test -- generate a 64-bit unsigned int"<<endl;
  cout<<"Run generator for 32-bit int to enable data align"<<endl;
  rg.GenRandUint32();
  cout<<rg.GenRandUint64()<<endl;
  cout<<endl;

  cout<<"Test -- generate a double in [0,1]"<<endl;
  cout<<rg.GenRand_Close0Close1()<<endl;
  cout<<endl;

  cout<<"Test -- generate a double in [0,1)"<<endl;
  cout<<rg.GenRand_Close0Open1()<<endl;
  cout<<endl;

  cout<<"Test -- generate a double in (0,1)"<<endl;
  cout<<rg.GenRand_Open0Open1()<<endl;
  cout<<endl;

  cout<<"Test -- generate a 53-bit double in [0,1)"<<endl;
  cout<<rg.GenRand53Mix_Close0Open1()<<endl;
  cout<<endl;

  cout<<"Test -- generate a 53-bit double in [0,1) with slow method"<<endl;
  cout<<rg.GenRand53Mix_Close0Open1_Slow()<<endl;
  cout<<endl;

  cout<<"Test -- generate a 63-bit double in [0,1)"<<endl;
  cout<<"Run generator for 32-bit int to enable data align"<<endl;
  rg.GenRandUint32();
  cout<<rg.GenRand63Mix_Close0Open1()<<endl;
  cout<<endl;

  cout<<"Test -- generate a 63-bit double in [0,1) with slow method"<<endl;
  cout<<rg.GenRand63Mix_Close0Open1_Slow()<<endl;
  cout<<endl;

  cout<<"Test -- default function"<<endl;
  cout<<rg()<<endl;
  double d;
  unsigned int ui;
  unsigned long long int ulli;
  long double ld;
  cout<<rg.Default(d)<<endl;
  cout<<rg.Default(ld)<<endl;
  cout<<rg.Default(ui)<<endl;
  cout<<"Run generator for 32-bit int to enable data align"<<endl;
  rg.GenRandUint32();
  cout<<rg.Default(ulli)<<endl;
  cout<<endl;

  cout<<"Test -- fill array"<<endl;
  fixVector<unsigned int,901> dv;
  refVector<unsigned int> rv;
  dv=100;
  BuildRationalVector(rg,dv,rv);
  cout<<rv.data()-dv.data()<<endl;
  cout<<"Run generator for 32-bit int to enable data align"<<endl;
  while(!rg.IsReadyFill())  rg.GenRandUint32();
  rg.FillArrayUint32(rv.data(),800);
  cout<<dv<<endl;
  while(!rg.IsReadyFill())  rg.GenRandUint32();
  rg.FillArrayUint32(rv);
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

  /*
  cout<<"Test -- degree of uniformness"<<endl;
  fixVector<unsigned int,10000> hist;
  hist=0u;
  for(unsigned int i=0;i<10000000;++i)
    hist[static_cast<unsigned int>(rg()*10000)]++;
  fixVector<unsigned int,2000> hhist;
  hhist=0U;
  for(unsigned int i=0;i<100000;++i)
    hhist[hist[i]]++;
  cout<<"(The data has been checked, but is not output here.)"<<endl;
  cout<<endl;
  */

  return 1;
}

