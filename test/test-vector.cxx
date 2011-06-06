
#include "vector/allocate.h"
#include "vector/copy.h"
#include "vector/compare.h"
#include "vector/fill.h"
#include "vector/exchange.h"
#include "vector/swap.h"
#include "vector/norm.h"
#include "vector/scale.h"
#include "vector/shift.h"
#include "vector/sum.h"
#include "vector/cross-product.h"
#include "vector/io.h"
#include "io/console.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {

  cout<<endl;
  Vector<int> Vi,Vi2;
  cout<<"Before Allocation: Size = "<<Vi.size<<endl;
  allocate(Vi,5);
  cout<<"After Allocation: Size = "<<Vi.size<<endl;
  cout<<"Before Imprint: Size = "<<Vi2.size<<endl;
  imprint(Vi2,Vi);
  cout<<"After Imprint: Size = "<<Vi2.size<<endl;
  Vector<Vector<int> > Vvi;
  cout<<"Before Allocation of complex structure: Size = "<<Vvi.size<<endl;
  allocate(Vvi,10);
  cout<<"After Allocation of complex structure: Size = "<<Vvi.size<<endl;
  Vector<double> Vd(10);
  cout<<"Allocate during Initiation: Size = "<<Vd.size<<endl;

  cout<<endl;
  Vector<float> Vf;
  cout<<"Validity of Allocated Vector is "<<IsValid(Vi)<<endl;
  cout<<"Validity of un-Allocated Vector is "<<IsValid(Vf)<<endl;

  cout<<endl;
  cout<<"State of complex Vector before release is: "<<Vvi.state<<endl;
  release(Vvi);
  cout<<"State of complex Vector after release is: "<<Vvi.state<<endl;

  cout<<endl;
  for(unsigned int i=0;i<5;++i) Vi[i]=i+5;
  cout<<"5th Element of Vi is "<<Vi[4]<<endl;
  cout<<"pointer of Vector Vi is "<<Vi()<<endl;

  cout<<endl;
  int ArrI[10];
  Vi.getSubvec(ArrI,6);
  cout<<"Vector pointing to Array: Size is "<<Vi.size<<endl;
  cout<<"Vector pointing to Array: State is "<<Vi.state<<endl;
  Vi.getSubvec(Vi2);
  cout<<"Vector pointing to Vector: Size is "<<Vi.size<<endl;
  cout<<"Vector pointing to Vector: State is "<<Vi.state<<endl;

  cout<<endl;
  Vector<long double> Vld(4),Vld2(6);
  for(unsigned int i=0;i<Vld.size;i++)    Vld[i]=0;
  for(unsigned int i=0;i<Vld2.size;i++)   Vld2[i]=34.4567;
  cout<<"Copy long double Vector: Content Before Copy as"<<endl;
  for(unsigned int i=0;i<Vld.size;i++) cout<<"\t"<<i<<"\t"<<Vld[i]<<endl;
  copy(Vld,Vld2);
  cout<<"Copy long double Vector: Content After Copy as"<<endl;
  for(unsigned int i=0;i<Vld.size;i++) cout<<"\t"<<i<<"\t"<<Vld[i]<<endl;
  Vector<double> Vd2(8);
  for(unsigned int i=0;i<Vd.size;i++)   Vd[i]=1.;
  for(unsigned int i=0;i<Vd2.size;i++)  Vd2[i]=i*1.5;
  cout<<"Copy double Vector: Content Before Copy as"<<endl;
  for(unsigned int i=0;i<Vd.size;i++) cout<<"\t"<<i<<"\t"<<Vd[i]<<endl;
  copy(Vd,Vd2);
  cout<<"Copy double Vector: Content After Copy as"<<endl;
  for(unsigned int i=0;i<Vd.size;i++) cout<<"\t"<<i<<"\t"<<Vd[i]<<endl;
  allocate(Vi,7);
  for(unsigned int i=0;i<Vi.size;i++)   Vi[i]=0;
  for(unsigned int i=0;i<Vi2.size;i++)  Vi2[i]=i+4;
  cout<<"Copy int Vector: Content Before Copy as"<<endl;
  for(unsigned int i=0;i<Vi.size;i++) cout<<"\t"<<i<<"\t"<<Vi[i]<<endl;
  copy(Vi,Vi2);
  cout<<"Copy int Vector: Content After Copy as"<<endl;
  for(unsigned int i=0;i<Vi.size;i++) cout<<"\t"<<i<<"\t"<<Vi[i]<<endl;
  Vector<long long> Vl,Vl2;
  allocate(Vl,8);
  allocate(Vl2,12);
  for(unsigned int i=0;i<Vl.size;++i) Vl[i]=0;
  for(unsigned int i=0;i<Vl2.size;++i)  Vl2[i]=i*3;
  cout<<"Copy long long Vector: Content Before Copy as"<<endl;
  for(unsigned int i=0;i<Vl.size;i++) cout<<"\t"<<i<<"\t"<<Vl[i]<<endl;
  copy(Vl,Vl2);
  cout<<"Copy long long Vector: Content After Copy as"<<endl;
  for(unsigned int i=0;i<Vl.size;i++) cout<<"\t"<<i<<"\t"<<Vl[i]<<endl;
  Vector<float> Vf2;
  allocate(Vf,8);
  allocate(Vf2,5);
  for(unsigned int i=0;i<Vf.size;++i) Vf[i]=0;
  for(unsigned int i=0;i<Vf2.size;++i)  Vf2[i]=i*3.5;
  cout<<"Copy float Vector: Content Before Copy as"<<endl;
  for(unsigned int i=0;i<Vf.size;i++) cout<<"\t"<<i<<"\t"<<Vf[i]<<endl;
  copy(Vf,Vf2);
  cout<<"Copy float Vector: Content After Copy as"<<endl;
  for(unsigned int i=0;i<Vf.size;i++) cout<<"\t"<<i<<"\t"<<Vf[i]<<endl;
  Vector<short> Vs(5), Vs2(7);
  for(unsigned int i=0;i<Vs.size;++i) Vs[i]=0;
  for(unsigned int i=0;i<Vs2.size;++i)  Vs2[i]=i*7-5;
  cout<<"Copy short Vector: Content Before Copy as"<<endl;
  for(unsigned int i=0;i<Vs.size;i++) cout<<"\t"<<i<<"\t"<<Vs[i]<<endl;
  copy(Vs,Vs2);
  cout<<"Copy short Vector: Content After Copy as"<<endl;
  for(unsigned int i=0;i<Vs.size;i++) cout<<"\t"<<i<<"\t"<<Vs[i]<<endl;
  Vector<char> Vc(5), Vc2(7);
  for(unsigned int i=0;i<Vc.size;++i) Vc[i]=0;
  for(unsigned int i=0;i<Vc2.size;++i)  Vc2[i]=i-5;
  cout<<"Copy char Vector: Content Before Copy as"<<endl;
  for(unsigned int i=0;i<Vc.size;i++) cout<<"\t"<<i<<"\t"<<Vc[i]<<endl;
  copy(Vc,Vc2);
  cout<<"Copy char Vector: Content After Copy as"<<endl;
  for(unsigned int i=0;i<Vc.size;i++) cout<<"\t"<<i<<"\t"<<Vc[i]<<endl;
  Vector<Vector<int> > Vvi2;
  allocate(Vvi,5);
  for(unsigned int i=0;i<Vvi.size;i++) allocate(Vvi[i],3+i);
  imprint(Vvi2,Vvi);
  for(unsigned int i=0;i<Vvi.size;i++)
  for(unsigned int j=0;j<Vvi[i].size;j++)
    Vvi[i][j]=0;
  for(unsigned int i=0;i<Vvi.size;i++)
  for(unsigned int j=0;j<Vvi[i].size;j++)
    Vvi2[i][j]=i+j;
  cout<<"Copy complex Vector: Content Before Copy as"<<endl;
  for(unsigned int i=0;i<Vvi.size;i++)
  for(unsigned int j=0;j<Vvi[i].size;j++)
    cout<<"\t"<<i<<"\t"<<j<<"\t"<<Vvi[i][j]<<endl;
  copy(Vvi,Vvi2);
  cout<<"Copy complex Vector: Content After Copy as"<<endl;
  for(unsigned int i=0;i<Vvi.size;i++)
  for(unsigned int j=0;j<Vvi[i].size;j++)
    cout<<"\t"<<i<<"\t"<<j<<"\t"<<Vvi[i][j]<<endl;

  cout<<endl;
  cout<<"Compare two same vectors: "<<IsSameStructure(Vvi,Vvi2)<<endl;
  cout<<"Compare two different-size vectors: "<<IsSameStructure(Vf,Vf2)<<endl;
  cout<<"Compare two different vectors with same size: "<<IsSameStructure(Vf,Vd2)<<endl;

  cout<<endl;
  fill(Vd,2.1);
  cout<<"Fill double Vector:"<<endl;
  for(unsigned int i=0;i<Vd.size;i++) cout<<"\t"<<i<<"\t"<<Vd[i]<<endl;
  fill(Vf,-2.5f);
  cout<<"Fill float Vector:"<<endl;
  for(unsigned int i=0;i<Vf.size;i++) cout<<"\t"<<i<<"\t"<<Vf[i]<<endl;
  fill(Vl,2345);
  cout<<"Fill long long Vector:"<<endl;
  for(unsigned int i=0;i<Vl.size;i++) cout<<"\t"<<i<<"\t"<<Vl[i]<<endl;
  fill(Vi,-29);
  cout<<"Fill int Vector:"<<endl;
  for(unsigned int i=0;i<Vi.size;i++) cout<<"\t"<<i<<"\t"<<Vi[i]<<endl;
  fill(Vs,static_cast<short>(107));
  cout<<"Fill short Vector:"<<endl;
  for(unsigned int i=0;i<Vs.size;i++) cout<<"\t"<<i<<"\t"<<Vs[i]<<endl;
  fill(Vc,'P');
  cout<<"Fill char Vector:"<<endl;
  for(unsigned int i=0;i<Vc.size;i++) cout<<"\t"<<i<<"\t"<<Vc[i]<<endl;
  fill(Vvi,15);
  cout<<"Fill complex Vector:"<<endl;
  for(unsigned int i=0;i<Vvi.size;i++)
  for(unsigned int j=0;j<Vvi[i].size;j++)
    cout<<"\t"<<i<<"\t"<<j<<"\t"<<Vvi[i][j]<<endl;
  fill(Vld,34.2f);
  cout<<"Fill long double vector with float:"<<endl;
  for(unsigned int i=0;i<Vld.size;i++) cout<<"\t"<<i<<"\t"<<Vld[i]<<endl;

  cout<<endl;
  exchange(Vld,Vld2);
  cout<<"Exchange long double Vector:"<<endl;
  for(unsigned int i=0;i<Vld.size;i++)    cout<<"\t"<<i<<"\t"<<Vld[i]<<endl;
  cout<<"\t============================="<<endl;
  for(unsigned int i=0;i<Vld2.size;i++)   cout<<"\t"<<i<<"\t"<<Vld2[i]<<endl;
  exchange(Vd,Vd2);
  cout<<"Exchange double Vector:"<<endl;
  for(unsigned int i=0;i<Vd.size;i++)   cout<<"\t"<<i<<"\t"<<Vd[i]<<endl;
  cout<<"\t============================="<<endl;
  for(unsigned int i=0;i<Vd2.size;i++)  cout<<"\t"<<i<<"\t"<<Vd2[i]<<endl;
  exchange(Vf,Vf2);
  cout<<"Exchange float Vector:"<<endl;
  for(unsigned int i=0;i<Vf.size;i++)   cout<<"\t"<<i<<"\t"<<Vf[i]<<endl;
  cout<<"\t============================="<<endl;
  for(unsigned int i=0;i<Vf2.size;i++)  cout<<"\t"<<i<<"\t"<<Vf2[i]<<endl;
  exchange(Vi,Vi2);
  cout<<"Exchange int Vector:"<<endl;
  for(unsigned int i=0;i<Vi.size;i++)   cout<<"\t"<<i<<"\t"<<Vi[i]<<endl;
  cout<<"\t============================="<<endl;
  for(unsigned int i=0;i<Vi2.size;i++)  cout<<"\t"<<i<<"\t"<<Vi2[i]<<endl;
  exchange(Vl,Vl2);
  cout<<"Exchange long long Vector:"<<endl;
  for(unsigned int i=0;i<Vl.size;i++)   cout<<"\t"<<i<<"\t"<<Vl[i]<<endl;
  cout<<"\t============================="<<endl;
  for(unsigned int i=0;i<Vl2.size;i++)  cout<<"\t"<<i<<"\t"<<Vl2[i]<<endl;
  exchange(Vs,Vs2);
  cout<<"Exchange short Vector:"<<endl;
  for(unsigned int i=0;i<Vs.size;i++)   cout<<"\t"<<i<<"\t"<<Vs[i]<<endl;
  cout<<"\t============================="<<endl;
  for(unsigned int i=0;i<Vs2.size;i++)  cout<<"\t"<<i<<"\t"<<Vs2[i]<<endl;
  exchange(Vc,Vc2);
  cout<<"Exchange char Vector:"<<endl;
  for(unsigned int i=0;i<Vc.size;i++)   cout<<"\t"<<i<<"\t"<<Vc[i]<<endl;
  cout<<"\t============================="<<endl;
  for(unsigned int i=0;i<Vc2.size;i++)  cout<<"\t"<<i<<"\t"<<Vc2[i]<<endl;

  cout<<endl;
  cout<<"Size Before Swap:"<<"\t"<<Vld.size<<"\t"<<Vld2.size<<endl;
  swap(Vld,Vld2);
  cout<<"Size After Swap:"<<"\t"<<Vld.size<<"\t"<<Vld2.size<<endl;

  cout<<endl;
  cout<<dot(Vd,Vd2)<<endl;
  cout<<dot(Vf,Vf2)<<endl;
  cout<<dot(Vld,Vc)<<endl;

  cout<<endl;
  cout<<normSQ(Vi)<<endl;
  cout<<norm(Vld)<<endl;
  cout<<norm(Vd)<<endl;
  cout<<norm(Vf)<<endl;

  cout<<endl;
  scale(Vd,2.);
  cout<<"double Vector After Scaling:"<<endl;
  for(unsigned int i=0;i<Vd.size;i++)   cout<<"\t"<<i<<"\t"<<Vd[i]<<endl;
  scale(Vd,0.5f);
  cout<<"double Vector After Scaling with float:"<<endl;
  for(unsigned int i=0;i<Vd.size;i++)   cout<<"\t"<<i<<"\t"<<Vd[i]<<endl;
  scale(Vf,1.0f/3.0f);
  cout<<"float Vector After Scaling:"<<endl;
  for(unsigned int i=0;i<Vf.size;i++)   cout<<"\t"<<i<<"\t"<<Vf[i]<<endl;
  scale(Vf,3);
  cout<<"float Vector After Scaling with int:"<<endl;
  for(unsigned int i=0;i<Vf.size;i++)   cout<<"\t"<<i<<"\t"<<Vf[i]<<endl;
  scale(Vi,'P');
  cout<<"int Vector After Scaling with char:"<<endl;
  for(unsigned int i=0;i<Vi.size;i++)   cout<<"\t"<<i<<"\t"<<Vi[i]<<endl;
  scale(Vd,Vd2);
  cout<<"double Vector After Scaling with double Vector:"<<endl;
  for(unsigned int i=0;i<Vd.size;i++)   cout<<"\t"<<i<<"\t"<<Vd[i]<<endl;
  scale(Vf,Vf2);
  cout<<"float Vector After Scaling with float Vector:"<<endl;
  for(unsigned int i=0;i<Vf.size;i++)   cout<<"\t"<<i<<"\t"<<Vf[i]<<endl;
  scale(Vld,Vc);
  cout<<"long double Vector After Scaling with char Vector:"<<endl;
  for(unsigned int i=0;i<Vld.size;i++)   cout<<"\t"<<i<<"\t"<<Vld[i]<<endl;
  scale(Vd,Vd2,2.5);
  cout<<"double Vector After Scaling with double Vector and double Value:"<<endl;
  for(unsigned int i=0;i<Vd.size;i++)   cout<<"\t"<<i<<"\t"<<Vd[i]<<endl;
  scale(Vf,0.5f,Vf2);
  cout<<"float Vector After Scaling with float Value and float Vector:"<<endl;
  for(unsigned int i=0;i<Vf.size;i++)   cout<<"\t"<<i<<"\t"<<Vf[i]<<endl;
  scale(Vld,Vf,'p');
  cout<<"long double Vector After Scaling with float Vector and char Value:"<<endl;
  for(unsigned int i=0;i<Vld.size;i++)   cout<<"\t"<<i<<"\t"<<Vld[i]<<endl;

  cout<<endl;
  shift(Vd,-1.5,Vd2);
  cout<<"Shift double Vector:"<<endl;
  for(unsigned int i=0;i<Vd.size;i++)   cout<<"\t"<<i<<"\t"<<Vd[i]<<endl;
  shift(Vf,Vf2,2.5f);
  cout<<"Shift float Vector:"<<endl;
  for(unsigned int i=0;i<Vf.size;i++)   cout<<"\t"<<i<<"\t"<<Vf[i]<<endl;
  shift(Vd,5.0);
  cout<<"Shift double Vector with a double Value:"<<endl;
  for(unsigned int i=0;i<Vd.size;i++)   cout<<"\t"<<i<<"\t"<<Vd[i]<<endl;
  shift(Vf,-3.0f);
  cout<<"Shift float Vector with a float Value:"<<endl;
  for(unsigned int i=0;i<Vf.size;i++)   cout<<"\t"<<i<<"\t"<<Vf[i]<<endl;
  shift(Vi,'A');
  cout<<"Shift int Vector with a char Value:"<<endl;
  for(unsigned int i=0;i<Vi.size;++i)   cout<<"\t"<<i<<"\t"<<Vi[i]<<endl;
  Vector<double> Vd3(9);
  fill(Vd3,-1.);
  scaleshift(Vd,-1.0,2.0,Vd2,Vd3);
  cout<<"Scale-Shift Operation for double Vector and Value:"<<endl;
  for(unsigned int i=0;i<Vd.size;i++)   cout<<"\t"<<i<<"\t"<<Vd[i]<<endl;
  Vector<float> Vf3(18);
  fill(Vf3,-1.0f);
  scaleshift(Vf,-1.0f,2.0f,Vf2,Vf3);
  cout<<"Scale-Shift Operation for float Vector and Value:"<<endl;
  for(unsigned int i=0;i<Vf.size;i++)   cout<<"\t"<<i<<"\t"<<Vf[i]<<endl;
  scaleshift(Vd,1,1.5f,Vd2,Vd3);
  cout<<"Scale-Shift Operation for double Vector and various Values:"<<endl;
  for(unsigned int i=0;i<Vd.size;i++)   cout<<"\t"<<i<<"\t"<<Vd[i]<<endl;
  scaleshift(Vf,1,' ',Vf2,Vf3);
  cout<<"Scale-Shift Operation for float Vector and various Values:"<<endl;
  for(unsigned int i=0;i<Vf.size;i++)   cout<<"\t"<<i<<"\t"<<Vf[i]<<endl;
  scaleshift(Vd,-3,Vd2,Vd3);
  cout<<"Scale-Shift Operation for double Vector with simple Shift:"<<endl;
  for(unsigned int i=0;i<Vd.size;i++)   cout<<"\t"<<i<<"\t"<<Vd[i]<<endl;
  scaleshift(Vf,-3,'9',Vi);
  cout<<"Scale-Shift Operation for float Vector with simple Shift:"<<endl;
  for(unsigned int i=0;i<Vf.size;i++)   cout<<"\t"<<i<<"\t"<<Vf[i]<<endl;
  shift(Vd,'8',Vf,Vi);
  cout<<"Shift with Value and two Vectors:"<<endl;
  for(unsigned int i=0;i<Vd.size;i++)   cout<<"\t"<<i<<"\t"<<Vd[i]<<endl;

  cout<<endl;
  cout<<"Sum of double Vector: "<<sum(Vd2)<<endl;
  cout<<"Sum of float Vector: "<<sum(Vf2)<<endl;
  cout<<"Sum of int Vector: "<<sum(Vi2)<<endl;
  cout<<"Sum of absolute value of double Vector: "<<asum(Vd2)<<endl;
  cout<<"Sum of absolute value of float Vector: "<<asum(Vf2)<<endl;
  cout<<"Sum of absolute value of int Vector: "<<asum(Vi2)<<endl;

  cout<<endl;
  Vector<long double> Vld3(8);
  fill(Vld3,-5);
  cross(Vld,Vld2,Vld3,uZero,uOne,uOne,uOne,uOne,uTwo);
  cout<<"Cross-Product of long-double Vectors:"<<endl;
  for(unsigned int i=0;i<Vld.size;i++)    cout<<"\t"<<i<<"\t"<<Vld[i]<<endl;
  cross(Vd,Vd2,Vd3);
  cout<<"Cross-Product of double Vectors:"<<endl;
  for(unsigned int i=0;i<Vd.size;i++)     cout<<"\t"<<i<<"\t"<<Vd[i]<<endl;
  cross(Vf,Vf2,Vf3,uOne);
  cout<<"Cross-Product of float Vectors:"<<endl;
  for(unsigned int i=0;i<Vf.size;i++)     cout<<"\t"<<i<<"\t"<<Vf[i]<<endl;

  cout<<endl;
  COut<<Vd<<Endl;
  COut<<Vc<<Endl;
  allocate(Vf,5);
  CIn>>Vf;
  COut<<Vf<<Endl;

  return 0;
}

