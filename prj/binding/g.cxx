
#include <iostream>
#include <cmath>
using namespace std;

double f(double x, int n) {
  return 3*x*x*x*x-2*x*x*x+2*n*x*x+2*n*x-n*n;
}

double df(double x, int n) {
  return 12*x*x*x-6*x*x+4*n*x+2*n;
}

double du(double x, int n) {
  return (x*x+n)/x/(x*x-n);
}

int main() {
  cout.precision(20);
  int n=35;
  double x=1.5,d;
  bool flag;
  do {
    flag=true;
    d=f(x,n)/df(x,n);
    if(fabs(d)<1e-8) flag=false;
    x-=d;
  } while(flag);
  cout<<n<<"\t"<<x<<"\t"<<-1.0/du(x,n)<<endl;
  return 0;
}

