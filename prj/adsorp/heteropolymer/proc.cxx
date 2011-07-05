
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
  const int ND=281;

  ifstream ifs;
  ifs.open("25a");
  int NE[ND];
  int NW[ND];
  long long int CT[ND];
  long double F[17];
  
  for(unsigned int i=0;i<17;++i)  F[i]=0;
  for(unsigned int i=0;i<ND;++i) {
    ifs>>NE[i]>>NW[i]>>CT[i];
    cout<<NE[i]<<"\t"<<NW[i]<<"\t"<<CT[i]<<endl;
    F[NE[i]]+=CT[i]*expl(+(NE[i]+NW[i]*1.6L)/0.625);
    cout<<F[NE[i]]<<endl;getchar();
  }

  for(unsigned int i=0;i<17;++i)
    cout<<i<<"\t"<<-logl(F[i])<<endl;

  return 0;
}
