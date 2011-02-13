
#include "operation/basic/unique-parameter-128bit-io.h"
#include "data/basic/console-output.h"
#include "data/basic/console-input.h"
using namespace std;

int main() {
  COut<<"Test -- create"<<Endl;
  UniqueParameter128b up;
  COut<<Endl;

  COut<<"Test -- assign and read"<<Endl;
  copy(up,1.5);
  COut<<up.ld<<"\t\t"<<up.ull[0]<<"\t\t"<<up.ull[1]<<Endl;
  double d[2]={123.445,-82321.76};
  copy(up,d);
  COut<<up.d[0]<<"\t"<<up.d[1]<<"\t\t"<<up.ull[0]<<"\t\t"<<up.ull[1]<<Endl;
  unsigned int u[4]={123,456,97343,232942};
  copy(up,u);
  COut<<up.u[0]<<"\t"<<up.u[1]<<"\t"<<up.u[2]<<"\t"<<up.u[3]<<"\t\t"<<up.ull[0]<<"\t\t"<<up.ull[1]<<Endl;
  int i[4]={-29382,8231,-232193,82932};
  copy(up,i);
  COut<<up.i[0]<<"\t"<<up.i[1]<<"\t"<<up.i[2]<<"\t"<<up.i[3]<<"\t\t"<<up.ull[0]<<"\t\t"<<up.ull[1]<<Endl;
  unsigned long long int ull[2]={23234200,38374729};
  copy(up,ull);
  COut<<up.ull[0]<<"\t\t"<<up.ull[1]<<Endl;
  double* dptr[4];
  double da,db,dc,dd;
  dptr[0]=&da; dptr[1]=&db; dptr[2]=&dc;  dptr[3]=&dd;
  copy(up,dptr);
  COut<<up.ptr[0]<<"\t"<<up.ptr[1]<<"\t"<<up.ptr[2]<<"\t"<<up.ptr[3]<<"\t\t"<<up.ull[0]<<"\t\t"<<up.ull[1]<<Endl;
  COut<<Endl;

  COut<<"Test -- default access"<<Endl;
  UniqueParameter128b up2;
  copy(up2,up);
  COut<<up2<<Endl;
  COut<<Endl;

  COut<<"Test -- assgin between array"<<Endl;
  UniqueParameter128b *uv1=new UniqueParameter128b[10];
  UniqueParameter128b *uv2=new UniqueParameter128b[8];
  for(unsigned int i=0;i<10;++i)
  for(unsigned int k=0;k<4;++k) uv1[i].u[k]=i*4+k;
  ccopy(uv2,uv1,8);
  for(unsigned int i=0;i<8;++i) {
    for(unsigned int k=0;k<4;++k) COut<<uv2[i].u[k]<<"  ";
    COut<<Endl;
  }
  COut<<"======================="<<Endl;
  for(unsigned int i=0;i<4;++i) uv1[9].u[i]=0;
  Vector<UniqueParameter128b> uv2m;
  refer(uv2m,uv2,8);
  copy(uv2m,uv1[9]);
  for(unsigned int i=0;i<8;++i) {
    for(unsigned int k=0;k<4;++k) COut<<uv2[i].u[k]<<"  ";
    COut<<Endl;
  }
  COut<<"======================="<<Endl;
  dcopy(uv2,uv1,2,0,1,1,2);
  for(unsigned int i=0;i<8;++i) {
    for(unsigned int k=0;k<4;++k) COut<<uv2[i].u[k]<<"  ";
    COut<<Endl;
  }
  delete[] uv2;
  delete[] uv1;
  COut<<Endl;

  COut<<"Test -- read from istream"<<Endl;
  CIn>>up;
  COut<<up<<Endl;
  COut<<"\t"<<up.d[0]<<"\t"<<up.d[1]<<Endl;
  COut<<"\t"<<up.u[0]<<"\t"<<up.u[1]<<"\t"<<up.u[2]<<"\t"<<up.u[3]<<Endl;
  COut<<"\t"<<up.i[0]<<"\t"<<up.i[1]<<"\t"<<up.i[2]<<"\t"<<up.i[3]<<Endl;
  COut<<"\t"<<up.ull[0]<<"\t"<<up.ull[1]<<Endl;
  COut<<"\t"<<up.ptr[0]<<"\t"<<up.ptr[1]<<"\t"<<up.ptr[2]<<"\t"<<up.ptr[3]<<Endl;
  CIn>>up;
  COut<<up<<Endl;
  COut<<"\t"<<up.d[0]<<"\t"<<up.d[1]<<Endl;
  COut<<"\t"<<up.u[0]<<"\t"<<up.u[1]<<"\t"<<up.u[2]<<"\t"<<up.u[3]<<Endl;
  COut<<"\t"<<up.i[0]<<"\t"<<up.i[1]<<"\t"<<up.i[2]<<"\t"<<up.i[3]<<Endl;
  COut<<"\t"<<up.ull[0]<<"\t"<<up.ull[1]<<Endl;
  COut<<"\t"<<up.ptr[0]<<"\t"<<up.ptr[1]<<"\t"<<up.ptr[2]<<"\t"<<up.ptr[3]<<Endl;
  CIn>>up;
  COut<<up<<Endl;
  COut<<"\t"<<up.d[0]<<"\t"<<up.d[1]<<Endl;
  COut<<"\t"<<up.u[0]<<"\t"<<up.u[1]<<"\t"<<up.u[2]<<"\t"<<up.u[3]<<Endl;
  COut<<"\t"<<up.i[0]<<"\t"<<up.i[1]<<"\t"<<up.i[2]<<"\t"<<up.i[3]<<Endl;
  COut<<"\t"<<up.ull[0]<<"\t"<<up.ull[1]<<Endl;
  COut<<"\t"<<up.ptr[0]<<"\t"<<up.ptr[1]<<"\t"<<up.ptr[2]<<"\t"<<up.ptr[3]<<Endl;
  CIn>>up;
  COut<<up<<Endl;
  COut<<"\t"<<up.d[0]<<"\t"<<up.d[1]<<Endl;
  COut<<"\t"<<up.u[0]<<"\t"<<up.u[1]<<"\t"<<up.u[2]<<"\t"<<up.u[3]<<Endl;
  COut<<"\t"<<up.i[0]<<"\t"<<up.i[1]<<"\t"<<up.i[2]<<"\t"<<up.i[3]<<Endl;
  COut<<"\t"<<up.ull[0]<<"\t"<<up.ull[1]<<Endl;
  COut<<"\t"<<up.ptr[0]<<"\t"<<up.ptr[1]<<"\t"<<up.ptr[2]<<"\t"<<up.ptr[3]<<Endl;
  CIn>>up;
  COut<<up<<Endl;
  COut<<"\t"<<up.d[0]<<"\t"<<up.d[1]<<Endl;
  COut<<"\t"<<up.u[0]<<"\t"<<up.u[1]<<"\t"<<up.u[2]<<"\t"<<up.u[3]<<Endl;
  COut<<"\t"<<up.i[0]<<"\t"<<up.i[1]<<"\t"<<up.i[2]<<"\t"<<up.i[3]<<Endl;
  COut<<"\t"<<up.ull[0]<<"\t"<<up.ull[1]<<Endl;
  COut<<"\t"<<up.ptr[0]<<"\t"<<up.ptr[1]<<"\t"<<up.ptr[2]<<"\t"<<up.ptr[3]<<Endl;
  CIn>>up;
  COut<<up<<Endl;
  COut<<"\t"<<up.d[0]<<"\t"<<up.d[1]<<Endl;
  COut<<"\t"<<up.u[0]<<"\t"<<up.u[1]<<"\t"<<up.u[2]<<"\t"<<up.u[3]<<Endl;
  COut<<"\t"<<up.i[0]<<"\t"<<up.i[1]<<"\t"<<up.i[2]<<"\t"<<up.i[3]<<Endl;
  COut<<"\t"<<up.ull[0]<<"\t"<<up.ull[1]<<Endl;
  COut<<"\t"<<up.ptr[0]<<"\t"<<up.ptr[1]<<"\t"<<up.ptr[2]<<"\t"<<up.ptr[3]<<Endl;
  COut<<Endl;

  return 1;
}

