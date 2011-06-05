
#include "vector/allocate.h"
#include "vector/copy.h"
#include "vector/compare.h"
#include "vector/fill.h"
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
  for(unsigned int i=0;i<Vd.size;i++) cout<<"\t"<<i<<"\t"<<Vd[i]<<endl;

  cout<<endl;

  return 0;
}

