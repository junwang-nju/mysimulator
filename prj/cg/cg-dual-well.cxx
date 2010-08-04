
#include "vector.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
  Vector<double> x;
  allocate(x,200000);
  double d;
  ifstream ifs("1");
  for(unsigned int i=0;i<200000;++i) {
    ifs>>d;
    ifs>>x[i];
    ifs>>d>>d;
  }
  ifs.close();
  double xc;
  double s[2],t[2];
  xc=-0.1;
  s[0]=s[1]=0;
  for(unsigned int i=0;i<200000;++i)
    if(x[i]<xc) s[0]++;
    else        s[1]++;
  t[0]=t[1]=0;
  for(unsigned int i=1;i<200000;++i)
    if((x[i-1]<xc)&&(x[i]>xc))        t[0]++;
    else if((x[i-1]>xc)&&(x[i]<xc))   t[1]++;
  cout<<s[0]<<"\t"<<s[1]<<endl;
  cout<<t[0]<<"\t"<<t[1]<<endl;
  return 0;
}

