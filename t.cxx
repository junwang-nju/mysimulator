
#include "var-vector.h"
#include "fix-vector.h"
#include "vector-op.h"
#include "btree.h"
#include "hash_func.h"
#include "param-list.h"
#include "property.h"
#include "particle.h"
#include "distance-storage.h"
#include "distance-evaluation.h"
#include "interaction-parpar-lj612.h"
#include "id-list.h"
#include "interaction-4list.h"
#include "interaction-parpar-lj1012.h"
#include "interaction-parpar-harmonic.h"
#include "interaction-parpar-lj612cut.h"
#include <iostream>
using namespace std;

class A{
  public:
    static const int aaa=10;
};

int main() {
  cout<<varVector<double>::TypeTag<<endl;
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
  v1+=pair<const double&,const varVector<double>&>(5.,v2);
  for(int i=0;i<10;++i)
    cout<<v1[i]<<"  ";
  cout<<endl;
  v1=5.;
  v1+=tr1::tuple<const double&,const varVector<double>&,
                 const varVector<double>&>(5.,v2,v2);
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

  cout<<dot(v1,fv1)<<endl;

  fixVector<int,5> iv;
  for(int i=0;i<5;++i)  iv[i]=i+8;
  cout<<hash_rs((char*)(iv.data()),5*4)<<endl;
  cout<<hash_js((char*)(iv.data()),5*4)<<endl;
  cout<<hash_pjw((char*)(iv.data()),5*4)<<endl;
  cout<<hash_elf((char*)(iv.data()),5*4)<<endl;
  cout<<hash_bkdr((char*)(iv.data()),5*4)<<endl;
  cout<<hash_sdbm((char*)(iv.data()),5*4)<<endl;
  cout<<hash_djb((char*)(iv.data()),5*4)<<endl;
  cout<<hash_dek((char*)(iv.data()),5*4)<<endl;
  cout<<hash_bp((char*)(iv.data()),5*4)<<endl;
  cout<<hash_fnv((char*)(iv.data()),5*4)<<endl;
  cout<<hash_ap((char*)(iv.data()),5*4)<<endl;

  ParamList PL;
  PL.KeyList.allocate(5);
  for(int i=0;i<3;++i)  PL.KeyList[i].Index.allocate(2);
  PL.KeyList[0].Index[0]=0;   PL.KeyList[0].Index[1]=1;
  PL.KeyList[1].Index[0]=1;   PL.KeyList[1].Index[1]=2;
  PL.KeyList[2].Index[0]=2;   PL.KeyList[2].Index[1]=3;
  for(int i=3;i<5;++i)  PL.KeyList[i].Index.allocate(3);
  PL.KeyList[3].Index[0]=0;PL.KeyList[3].Index[1]=1;PL.KeyList[3].Index[2]=2;
  PL.KeyList[4].Index[0]=1;PL.KeyList[4].Index[1]=2;PL.KeyList[4].Index[2]=3;
  for(int i=0;i<5;++i)  PL.KeyList[i].BuildHash();
  PL.ValueList.allocate(5);
  for(int i=0;i<5;i++) PL.ValueList[i].allocate(2);
  for(int i=0;i<5;++i) {
    PL.ValueList[i][0]=i;
    PL.ValueList[i][1]=i+2;
  }
  PL.UpdateHashTree();
  const varVector<double>* vo=PL.get(PL.KeyList[2].Index);
  cout<<(*vo)[0]<<endl;
  cout<<(*vo)[1]<<endl;

  Property Pa,Pb;
  allocate_as_Particle(Pa,3);
  allocate_as_Particle(Pb,3);
  Pa.Coordinate[0]=0;
  Pa.Coordinate[1]=0;
  Pa.Coordinate[2]=0;
  Pa.MonomerKindID=0;
  Pa.Index=0;
  Pb.Coordinate[0]=0;
  Pb.Coordinate[1]=0;
  Pb.Coordinate[2]=3;
  Pb.MonomerKindID=0;
  Pb.Index=2;
  FreeSpace FS;
  DistanceEvalwStorage<3> DEval;
  DEval.allocate_storage(3);
  
  ParamList prm;
  prm.KeyList.allocate(3);
  for(uint i=0;i<3U;++i)
    prm.KeyList[i].Index.allocate(2);
  prm.KeyList[0].Index[0]=0;  prm.KeyList[0].Index[1]=0;
  prm.KeyList[1].Index[0]=0;  prm.KeyList[1].Index[1]=1;
  prm.KeyList[2].Index[0]=1;  prm.KeyList[2].Index[1]=1;
  for(uint i=0;i<3U;++i)
    prm.KeyList[i].BuildHash();
  prm.ValueList.allocate(3);
  for(uint i=0;i<3U;++i)
    prm.ValueList[i].allocate(4);
  varVector<double> vprm;
  vprm.allocate(4);
  vprm[0]=3.;
  vprm[1]=1.;
  vprm[2]=9.;
  vprm[3]=12.;
  prm.ValueList[0]=vprm;
  prm.ValueList[1]=vprm;
  prm.ValueList[1][0]=2;
  prm.ValueList[1][2]=4;
  prm.ValueList[2]=vprm;
  prm.ValueList[2][0]=4;
  prm.ValueList[2][2]=16;
  prm.UpdateHashTree();

  double Energy=0.;
  varVector<Property*> P(2);
  P[0]=&Pa;
  P[1]=&Pb;
  E_ParPar_LJ612(P,prm,DEval,FS,Energy);
  cout<<Energy<<endl;

  varVector<Property> PropSet(3);
  allocate_as_Particle(PropSet[0],3);
  allocate_as_Particle(PropSet[1],3);
  allocate_as_Particle(PropSet[2],3);
  PropSet[0].Coordinate[0]=0;
  PropSet[0].Coordinate[1]=0;
  PropSet[0].Coordinate[2]=0;
  PropSet[0].Index=0;
  PropSet[2].Coordinate[0]=0;
  PropSet[2].Coordinate[1]=0;
  PropSet[2].Coordinate[2]=3;
  PropSet[2].Index=2;
  IDList<DistanceEvalwStorage<3>,FreeSpace> idl;
  idl.allocate(1,2);
  idl.List[0][0]=0;
  idl.List[0][1]=2;
  idl.efunc=E_ParPar_LJ612;
  E_List(PropSet,prm,idl,DEval,FS,Energy);
  cout<<Energy<<endl;

  return 1;
}

