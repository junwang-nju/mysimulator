
#include "unique-parameter/64bit/copy.h"
#include "unique-parameter/64bit/fill.h"
#include "unique-parameter/64bit/io.h"
#include "unique-parameter/128bit/interface.h"
#include "io/console.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  UniqueParameter64Bit U,U1;
  U.value<double>()=-8.90232;
  cout<<"Assign a double Value to UniqueParameter64Bit:\t"<<U.value<double>()<<endl;
  cout<<"Access through float form:\t"<<U.value<float>()<<endl;
  cout<<"Access through long long form:\t"<<U.value<long long>()<<endl;
  cout<<"Access through unsigned long long form:\t"<<U.value<unsigned long long>()<<endl;
  cout<<"Access through int form:\t"<<U.value<int>()<<endl;
  cout<<"Access through unsigned int form:\t"<<U.value<unsigned int>()<<endl;
  cout<<"Access through short form:\t"<<U.value<short>()<<endl;
  cout<<"Access through unsigned short form:\t"<<U.value<unsigned short>()<<endl;
  cout<<"Access through char form:\t"<<U.value<char>()<<endl;
  cout<<"Access through unsigned char form:\t"<<U.value<unsigned char>()<<endl;
  cout<<"Access through pointer form:\t"<<U.pointer<double>()<<endl;
  cout<<"Validity of UniqueParameter64Bit:\t"<<IsValid(U)<<endl;
  release(U);
  cout<<"Release does nothing!\t"<<U.value<double>()<<endl;

  cout<<endl;
  copy(U1,U);
  cout<<"UniqueParameter64Bit Copied from UniqueParameter64Bit:\t"<<U1.value<unsigned long long>()<<endl;
  copy(U,109.78236);
  cout<<"UniqueParameter64Bit Copied from double:\t"<<U.value<unsigned long long>()<<endl;
  double d;
  copy(d,U);
  cout<<"double Copied from UniqueParameter64Bit:\t"<<d<<endl;
  copy(U,&d);
  cout<<"UniqueParameter64Bit Copied from a double pointer:\t"<<U.pointer<double>()<<endl;
  unsigned long long *up;
  copy(up,U);
  cout<<"unsigned long long Copied from pointer of UniqueParameter64Bit:\t"<<(*up)<<endl;
  Vector<UniqueParameter64Bit> vU(5),vU1(6);
  for(unsigned int i=0;i<vU.size;i++) copy(vU[i],i*(-234879.12));
  copy(vU1,vU);
  cout<<"UniqueParameter64Bit Vector Copied from UniqueParameter64Bit Vector:"<<endl;
  for(unsigned int i=0;i<vU1.size;i++)  cout<<"\t"<<i<<"\t"<<vU1[i].value<double>()<<endl;
  Vector<double> vD(4);
  for(unsigned int i=0;i<vD.size;++i) vD[i]=i+901.89;
  copy(vU,vD);
  cout<<"UniqueParameter64Bit Vector Copied from double Vector:"<<endl;
  for(unsigned int i=0;i<vU.size;i++)  cout<<"\t"<<i<<"\t"<<vU[i].value<double>()<<endl;
  Vector<unsigned long long> vL(8);
  for(unsigned int i=0;i<vL.size;++i) vL[i]=i*i*89L;
  copy(vU,vL);
  cout<<"UniqueParameter64Bit Vector Copied from unsigned long long Vector:"<<endl;
  for(unsigned int i=0;i<vU.size;i++)  cout<<"\t"<<i<<"\t"<<vU[i].value<unsigned long long>()<<endl;
  Vector<int> vI(12);
  for(unsigned int i=0;i<vI.size;i++) vI[i]=(i+1)*(i+3)*731;
  copy(vU,vI);
  cout<<"UniqueParameter64Bit Vector Copied from int Vector:"<<endl;
  for(unsigned int i=0;i<vU.size;i++)  cout<<"\t"<<i<<"\t"<<vU[i].value<int>()<<endl;
  Vector<float> vF(7);
  for(unsigned int i=0;i<vF.size;i++) vF[i]=(i+3.5)*7.3;
  copy(vU,vF);
  cout<<"UniqueParameter64Bit Vector Copied from float Vector:"<<endl;
  for(unsigned int i=0;i<vU.size;i++)  cout<<"\t"<<i<<"\t"<<vU[i].value<float>()<<endl;
  for(unsigned int i=0;i<vU.size;i++) vU[i].value<double>()=i+5.6788;
  copy(vD,vU);
  cout<<"Copy UniqueParameter64Bit Vector to double Vector:"<<endl;
  for(unsigned int i=0;i<vD.size;i++)  cout<<"\t"<<i<<"\t"<<vD[i]<<endl;
  for(unsigned int i=0;i<vU.size;i++) vU[i].value<unsigned long long>()=i+56788;
  copy(vL,vU);
  cout<<"Copy UniqueParameter64Bit Vector to unsigned long long Vector:"<<endl;
  for(unsigned int i=0;i<vL.size;i++)  cout<<"\t"<<i<<"\t"<<vL[i]<<endl;
  for(unsigned int i=0;i<vU.size;i++) vU[i].value<float>()=i+56.788f;
  copy(vF,vU);
  cout<<"Copy UniqueParameter64Bit Vector to float Vector:"<<endl;
  for(unsigned int i=0;i<vF.size;i++)  cout<<"\t"<<i<<"\t"<<vF[i]<<endl;
  for(unsigned int i=0;i<vU.size;i++) vU[i].value<int>()=i-5688;
  copy(vI,vU);
  cout<<"Copy UniqueParameter64Bit Vector to float Vector:"<<endl;
  for(unsigned int i=0;i<vI.size;i++)  cout<<"\t"<<i<<"\t"<<vI[i]<<endl;

  cout<<endl;
  fill(U,1.89034);
  cout<<"Fill UniqueParameter64Bit with double:"<<endl;
  cout<<"\t"<<U.d<<endl;
  fill(U,1.23224f);
  cout<<"Fill UniqueParameter64Bit with float:"<<endl;
  cout<<"\t"<<U.f[0]<<"\t"<<U.f[1]<<endl;
  fill(U,23424ULL);
  cout<<"Fill UniqueParameter64Bit with unsigned long long:"<<endl;
  cout<<"\t"<<U.ull<<endl;
  fill(U,-23424LL);
  cout<<"Fill UniqueParameter64Bit with long long:"<<endl;
  cout<<"\t"<<U.ll<<endl;
  fill(U,1231);
  cout<<"Fill UniqueParameter64Bit with int:"<<endl;
  cout<<"\t"<<U.i[0]<<"\t"<<U.i[1]<<endl;
  fill(U,2321231U);
  cout<<"Fill UniqueParameter64Bit with unsigned int:"<<endl;
  cout<<"\t"<<U.u[0]<<"\t"<<U.u[1]<<endl;
  fill(U,static_cast<short>(219));
  cout<<"Fill UniqueParameter64Bit with short:"<<endl;
  cout<<"\t"<<U.s[0]<<"\t"<<U.s[1]<<"\t"<<U.s[2]<<"\t"<<U.s[3]<<endl;
  fill(U,'A');
  cout<<"Fill UniqueParameter64Bit with char:"<<endl;
  cout<<"\t"<<U.c[0]<<"\t"<<U.c[1]<<"\t"<<U.c[2]<<"\t"<<U.c[3]<<"\t"<<U.c[4]<<"\t"<<U.c[5]<<"\t"<<U.c[6]<<"\t"<<U.c[7]<<endl;
  fill(U,1.23224f,-2372e10f);
  cout<<"Fill UniqueParameter64Bit with float:"<<endl;
  cout<<"\t"<<U.f[0]<<"\t"<<U.f[1]<<endl;
  fill(U,1231,-23772);
  cout<<"Fill UniqueParameter64Bit with int:"<<endl;
  cout<<"\t"<<U.i[0]<<"\t"<<U.i[1]<<endl;
  fill(U,static_cast<short>(219),static_cast<short>(-90),static_cast<short>(34),static_cast<short>(-121));
  cout<<"Fill UniqueParameter64Bit with short:"<<endl;
  cout<<"\t"<<U.s[0]<<"\t"<<U.s[1]<<"\t"<<U.s[2]<<"\t"<<U.s[3]<<endl;
  fill(U,'A','C','V','R','Y','G','Q','W');
  cout<<"Fill UniqueParameter64Bit with char:"<<endl;
  cout<<"\t"<<U.c[0]<<"\t"<<U.c[1]<<"\t"<<U.c[2]<<"\t"<<U.c[3]<<"\t"<<U.c[4]<<"\t"<<U.c[5]<<"\t"<<U.c[6]<<"\t"<<U.c[7]<<endl;
  fill(vU,102872123ULL);
  cout<<"Fill UniqueParameter64Bit Vector with unsigned long long:"<<endl;
  for(unsigned int i=0;i<vU.size;i++)   cout<<"\t"<<vU[i].value<unsigned long long>()<<endl;
  fill(vU,-9823.23e-5);
  cout<<"Fill UniqueParameter64Bit Vector with double:"<<endl;
  for(unsigned int i=0;i<vU.size;i++)   cout<<"\t"<<vU[i].value<double>()<<endl;
  fill(vU,U);
  cout<<"Fill UniqueParameter64Bit Vector with UniqueParameter64Bit:"<<endl;
  for(unsigned int i=0;i<vU.size;i++)   cout<<"\t"<<vU[i].value<unsigned long long>()<<endl;
  fill(vU,-9823.23e-10f);
  cout<<"Fill UniqueParameter64Bit Vector with float:"<<endl;
  for(unsigned int i=0;i<vU.size;i++)   cout<<"\t"<<vU[i].f[0]<<"\t"<<vU[i].f[1]<<endl;
  fill(vU,-24879);
  cout<<"Fill UniqueParameter64Bit Vector with int:"<<endl;
  for(unsigned int i=0;i<vU.size;i++)   cout<<"\t"<<vU[i].i[0]<<"\t"<<vU[i].i[1]<<endl;
  fill(vU,static_cast<short>(-8917));
  cout<<"Fill UniqueParameter64Bit Vector with short:"<<endl;
  for(unsigned int i=0;i<vU.size;i++)   cout<<"\t"<<vU[i].s[0]<<"\t"<<vU[i].s[1]<<"\t"<<vU[i].s[2]<<"\t"<<vU[i].s[3]<<endl;
  fill(vU,'W');
  cout<<"Fill UniqueParameter64Bit Vector with char:"<<endl;
  for(unsigned int i=0;i<vU.size;i++) {
    for(unsigned int j=0;j<8;j++) cout<<"\t"<<vU[i].c[j];
    cout<<endl;
  }

  cout<<endl;
  COut<<U<<Endl;
  CIn>>U;
  COut<<U.value<double>()<<Endl;
  CIn>>U;
  cout<<U.i[0]<<"\t"<<U.i[1]<<endl;

  UniqueParameter128Bit UL,UL1;
  return 0;
}

