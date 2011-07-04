
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main() {
  //const int ND=27;
  //const int ND=50;
  //const int ND=113;
  //const int ND=151;
  //const int ND=256;
  const int ND=110;

  ifstream ifs;
  ifs.open("qq");
  int NE[ND];
  int NW[ND];
  int CT[ND];
  double F[10];
  
  for(unsigned int i=0;i<10;++i)  F[i]=0;
  for(unsigned int i=0;i<ND;++i) {
    ifs>>NE[i]>>NW[i]>>CT[i];
    F[NE[i]]+=CT[i]*exp(+(NE[i]+NW[i]*1.6)/0.625);
  }

  for(unsigned int i=0;i<10;++i)
    cout<<i<<"\t"<<-log(F[i])+log(F[9])<<endl;

  return 0;
}
