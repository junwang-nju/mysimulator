
#include "var-vector-double.h"
#include "fix-vector-double.h"
#include <iostream>
using namespace std;

int main() {
  varVector<double> v1;
  varVector<double> v2(1000000);
  v1.allocate(v2);
  v1=5.;
  for(int i=0;i<100;++i)
    v2[i]=i;
  v1*=1.2;
  v1*=v2;
  v1=5.;
  v1.scaleshift(1.2,5,v2,v2);
  v1=5.;
  v1+=pair<const double&,const varDVector&>(5.,v2);
  for(int i=0;i<10;++i)
    cout<<v1[i]<<"  ";
  cout<<endl;
  v1=5.;
  v1+=tr1::tuple<const double&,const varDVector&,const varDVector&>(5.,v2,v2);
  for(int i=0;i<10;++i)
    cout<<v1[i]<<"  ";
  cout<<endl;

  fixVector<double,1000>  fv1,fv2;
  fv1=5.;
  for(int i=0;i<100;++i)
    fv2[i]=i;
  fv1*=1.2;
  fv1+=fv2;
  cout<<fv1[2]<<endl;
  fv1+=1.5;
  cout<<fv1[2]<<endl;
  fv1.shift(1.2,fv2);
  fv1+=tr1::tuple<const double&,const fixVector<double,1000>&,
                  const fixVector<double,1000>&>(5.,fv2,fv2);
  fv2=fv1.swap_content(fv2);
  return 1;
}

