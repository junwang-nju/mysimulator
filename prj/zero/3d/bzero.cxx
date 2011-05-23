
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main() {
  ifstream ifs;
  ifs.open("zz");
  const int N=16;
  double a,b,r,t;
  ifs>>a>>b;
  //ifs>>a>>b;
  cout.precision(20);
  for(int i=1;i<=N;++i) {
    ifs>>a>>b;
    r=sqrt(a*a+b*b);
    t=(b>0?1:-1)*acos(a/r);
    cout<<log(r)<<"\t"<<t<<endl;
  }
  return 1;
}

