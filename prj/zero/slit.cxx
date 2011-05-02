
#include "vector/allocate.h"
#include "vector/fill.h"
#include "vector/io.h"
#include "io/input/file/interface.h"
using namespace mysimulator;

int main() {
  //const int N=12;
  //const int DN=N+N;
  //const int NS=120292;
  //const int N=14;
  //const int DN=N+N;
  //const int NS=881500;
  const int N=16;
  const int DN=N+N;
  const int NS=6416596;
  Vector<Vector<int> > X,Y;
  allocate(X,NS);
  allocate(Y,NS);
  for(int i=0;i<NS;++i) {
    allocate(X[i],N);
    allocate(Y[i],N);
  }
  FileInput fin;
  fin.open("x3");
  for(int i=0;i<NS;++i)
  for(int k=0;k<N;++k)
    fin>>X[i][k]>>Y[i][k];
  fin.close();

  bool fg;
  int x,y,te;
  Vector<long long int> e(N+1);
  fill(e,0);
  //for(int i=0;i<DN;++i)
  for(int k=0;k<=30;++k) {
    for(int z=0;z<NS;++z) {
      fg=true;
      te=0;
      for(int w=0;w<N;++w) {
        y=Y[z][w]+k;
        if((y<0)||(y>30)) { fg=false; break; }
        if(y==0)  ++te;
      }
      if(fg)  e[te]++;
    }
  }
  COut<<e<<Endl;

  return 0;
}

