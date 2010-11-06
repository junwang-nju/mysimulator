
#include "unique-parameter-128bit.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- create"<<endl;
  UniqueParameter128b up;
  cout<<endl;

  cout<<"Test -- assign and read"<<endl;
  copy(up,1.5);
  cout<<up.ld<<"\t\t"<<up.ull[0]<<"\t\t"<<up.ull[1]<<endl;
  double d[2]={123.445,-82321.76};
  copy(up,d);
  cout<<up.d[0]<<"\t"<<up.d[1]<<"\t\t"<<up.ull[0]<<"\t\t"<<up.ull[1]<<endl;
  unsigned int u[4]={123,456,97343,232942};
  copy(up,u);
  cout<<up.u[0]<<"\t"<<up.u[1]<<"\t"<<up.u[2]<<"\t"<<up.u[3]<<"\t\t"<<up.ull[0]<<"\t\t"<<up.ull[1]<<endl;
  int i[4]={-29382,8231,-232193,82932};
  copy(up,i);
  cout<<up.i[0]<<"\t"<<up.i[1]<<"\t"<<up.i[2]<<"\t"<<up.i[3]<<"\t\t"<<up.ull[0]<<"\t\t"<<up.ull[1]<<endl;
  unsigned long long int ull[2]={23234200,38374729};
  copy(up,ull);
  cout<<up.ull[0]<<"\t\t"<<up.ull[1]<<endl;
  double* dptr[4];
  double da,db,dc,dd;
  dptr[0]=&da; dptr[1]=&db; dptr[2]=&dc;  dptr[3]=&dd;
  copy(up,dptr);
  cout<<up.ptr[0]<<"\t"<<up.ptr[1]<<"\t"<<up.ptr[2]<<"\t"<<up.ptr[3]<<"\t\t"<<up.ull[0]<<"\t\t"<<up.ull[1]<<endl;
  cout<<endl;

  cout<<"Test -- default access"<<endl;
  UniqueParameter128b up2;
  copy(up2,up);
  cout<<up2<<endl;
  cout<<endl;

  cout<<"Test -- assgin between array"<<endl;
  UniqueParameter128b *uv1=new UniqueParameter128b[10];
  UniqueParameter128b *uv2=new UniqueParameter128b[8];
  for(unsigned int i=0;i<10;++i)
  for(unsigned int k=0;k<4;++k) uv1[i].u[k]=i*4+k;
  ccopy(uv2,uv1,8);
  for(unsigned int i=0;i<8;++i) {
    for(unsigned int k=0;k<4;++k) cout<<uv2[i].u[k]<<"  ";
    cout<<endl;
  }
  for(unsigned int i=0;i<4;++i) uv1[9].u[i]=0;
  Vector<UniqueParameter128b> uv2m;
  refer(uv2m,uv2,8);
  copy(uv2m,uv1[9]);
  for(unsigned int i=0;i<8;++i) {
    for(unsigned int k=0;k<4;++k) cout<<uv2[i].u[k]<<"  ";
    cout<<endl;
  }
  dcopy(uv2,uv1,2,0,1,1,2);
  for(unsigned int i=0;i<8;++i) {
    for(unsigned int k=0;k<4;++k) cout<<uv2[i].u[k]<<"  ";
    cout<<endl;
  }
  delete[] uv2;
  delete[] uv1;
  cout<<endl;

  cout<<"Test -- read from istream"<<endl;
  cin>>up;
  cout<<up<<endl;
  cout<<"\t"<<up.d[0]<<"\t"<<up.d[1]<<endl;
  cout<<"\t"<<up.u[0]<<"\t"<<up.u[1]<<"\t"<<up.u[2]<<"\t"<<up.u[3]<<endl;
  cout<<"\t"<<up.i[0]<<"\t"<<up.i[1]<<"\t"<<up.i[2]<<"\t"<<up.i[3]<<endl;
  cout<<"\t"<<up.ull[0]<<"\t"<<up.ull[1]<<endl;
  cout<<"\t"<<up.ptr[0]<<"\t"<<up.ptr[1]<<"\t"<<up.ptr[2]<<"\t"<<up.ptr[3]<<endl;
  cin>>up;
  cout<<up<<endl;
  cout<<"\t"<<up.d[0]<<"\t"<<up.d[1]<<endl;
  cout<<"\t"<<up.u[0]<<"\t"<<up.u[1]<<"\t"<<up.u[2]<<"\t"<<up.u[3]<<endl;
  cout<<"\t"<<up.i[0]<<"\t"<<up.i[1]<<"\t"<<up.i[2]<<"\t"<<up.i[3]<<endl;
  cout<<"\t"<<up.ull[0]<<"\t"<<up.ull[1]<<endl;
  cout<<"\t"<<up.ptr[0]<<"\t"<<up.ptr[1]<<"\t"<<up.ptr[2]<<"\t"<<up.ptr[3]<<endl;
  cin>>up;
  cout<<up<<endl;
  cout<<"\t"<<up.d[0]<<"\t"<<up.d[1]<<endl;
  cout<<"\t"<<up.u[0]<<"\t"<<up.u[1]<<"\t"<<up.u[2]<<"\t"<<up.u[3]<<endl;
  cout<<"\t"<<up.i[0]<<"\t"<<up.i[1]<<"\t"<<up.i[2]<<"\t"<<up.i[3]<<endl;
  cout<<"\t"<<up.ull[0]<<"\t"<<up.ull[1]<<endl;
  cout<<"\t"<<up.ptr[0]<<"\t"<<up.ptr[1]<<"\t"<<up.ptr[2]<<"\t"<<up.ptr[3]<<endl;
  cin>>up;
  cout<<up<<endl;
  cout<<"\t"<<up.d[0]<<"\t"<<up.d[1]<<endl;
  cout<<"\t"<<up.u[0]<<"\t"<<up.u[1]<<"\t"<<up.u[2]<<"\t"<<up.u[3]<<endl;
  cout<<"\t"<<up.i[0]<<"\t"<<up.i[1]<<"\t"<<up.i[2]<<"\t"<<up.i[3]<<endl;
  cout<<"\t"<<up.ull[0]<<"\t"<<up.ull[1]<<endl;
  cout<<"\t"<<up.ptr[0]<<"\t"<<up.ptr[1]<<"\t"<<up.ptr[2]<<"\t"<<up.ptr[3]<<endl;
  cin>>up;
  cout<<up<<endl;
  cout<<"\t"<<up.d[0]<<"\t"<<up.d[1]<<endl;
  cout<<"\t"<<up.u[0]<<"\t"<<up.u[1]<<"\t"<<up.u[2]<<"\t"<<up.u[3]<<endl;
  cout<<"\t"<<up.i[0]<<"\t"<<up.i[1]<<"\t"<<up.i[2]<<"\t"<<up.i[3]<<endl;
  cout<<"\t"<<up.ull[0]<<"\t"<<up.ull[1]<<endl;
  cout<<"\t"<<up.ptr[0]<<"\t"<<up.ptr[1]<<"\t"<<up.ptr[2]<<"\t"<<up.ptr[3]<<endl;
  cin>>up;
  cout<<up<<endl;
  cout<<"\t"<<up.d[0]<<"\t"<<up.d[1]<<endl;
  cout<<"\t"<<up.u[0]<<"\t"<<up.u[1]<<"\t"<<up.u[2]<<"\t"<<up.u[3]<<endl;
  cout<<"\t"<<up.i[0]<<"\t"<<up.i[1]<<"\t"<<up.i[2]<<"\t"<<up.i[3]<<endl;
  cout<<"\t"<<up.ull[0]<<"\t"<<up.ull[1]<<endl;
  cout<<"\t"<<up.ptr[0]<<"\t"<<up.ptr[1]<<"\t"<<up.ptr[2]<<"\t"<<up.ptr[3]<<endl;
  cout<<endl;

  return 1;
}

