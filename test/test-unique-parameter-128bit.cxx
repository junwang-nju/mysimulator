
#include "unique-parameter-128bit.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- create"<<endl;
  UniqueParameter128b up;
  cout<<endl;

  cout<<"Test -- assign and read"<<endl;
  up=1.5;
  cout<<up.ld<<"\t\t"<<up.ull[0]<<"\t\t"<<up.ull[1]<<endl;
  double d[2]={123.445,-82321.76};
  up=d;
  cout<<up.d[0]<<"\t"<<up.d[1]<<"\t\t"<<up.ull[0]<<"\t\t"<<up.ull[1]<<endl;
  unsigned int u[4]={123,456,97343,232942};
  up=u;
  cout<<up.u[0]<<"\t"<<up.u[1]<<"\t"<<up.u[2]<<"\t"<<up.u[3]<<"\t\t"<<up.ull[0]<<"\t\t"<<up.ull[1]<<endl;
  int i[4]={-29382,8231,-232193,82932};
  up=i;
  cout<<up.i[0]<<"\t"<<up.i[1]<<"\t"<<up.i[2]<<"\t"<<up.i[3]<<"\t\t"<<up.ull[0]<<"\t\t"<<up.ull[1]<<endl;
  unsigned long long int ull[2]={23234200,38374729};
  up=ull;
  cout<<up.ull[0]<<"\t\t"<<up.ull[1]<<endl;
  double* dptr[4];
  double da,db,dc,dd;
  dptr[0]=&da; dptr[1]=&db; dptr[2]=&dc;  dptr[3]=&dd;
  up=dptr;
  cout<<up.ptr[0]<<"\t"<<up.ptr[1]<<"\t"<<up.ptr[2]<<"\t"<<up.ptr[3]<<"\t\t"<<up.ull[0]<<"\t\t"<<up.ull[1]<<endl;
  cout<<endl;

  cout<<"Test -- default access"<<endl;
  UniqueParameter128b up2;
  up2=up;
  cout<<up2<<endl;
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

