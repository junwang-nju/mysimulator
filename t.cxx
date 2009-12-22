
#include "var-vector.h"
#include "fix-vector.h"
#include "vector-op.h"
#include "btree.h"
#include "hash-func.h"
#include "param-list.h"
#include "property-list.h"
#include "property-list-op.h"
#include "particle.h"
#include "distance-storage.h"
#include "distance-evaluation.h"
#include "interaction-parpar-lj612.h"
#include "interaction-list.h"
#include "interaction-list-op.h"
#include "interaction-4list.h"
#include "interaction-parpar-lj1012.h"
#include "interaction-parpar-harmonic.h"
#include "interaction-parpar-lj612cut.h"
#include "interaction-4listset.h"
#include "monomer-propagator.h"
#include "propagator-particle-conste-vverlet.h"
#include "propagator-conste-vverlet.h"
#include "propagator.h"
#include "propagator-particle-berendsen-vverlet.h"
#include "propagator-berendsen-vverlet.h"
#include "propagator-particle-langevin-vverlet.h"
#include "propagator-langevin-vverlet.h"
#include "random-generator.h"
#include "interaction-parpar-coulomb.h"
#include "interaction-parpar-coulomb-wde.h"
#include "interaction-parpar-quad-harm.h"
/*
#include "minimizer-base.h"
#include "minimizer-steep.h"
#include "minimizer-conjg.h"
*/

#include "vector-base.h"
#include "ref-vector.h"
#include <iostream>
using namespace std;

class A{
  public:
    static const int aaa=10;
};

void OutputFunc(
    ostream& os, const Propagator<DistanceEvalwStorage<3>,FreeSpace>& Pg,
    const VectorBase<refVector<double> >& Coordinate,
    const VectorBase<refVector<double> >& Velocity,
    const VectorBase<refVector<double> >& Gradient,
    const ParamList&,
    VectorBase<IDList<DistanceEvalwStorage<3>,FreeSpace> >&,
    DistanceEvalwStorage<3>&, const FreeSpace&) {
  os<<Pg.CmnGbParam[BasicCommon][NowTime]<<"\t"<<Coordinate[0]<<endl;
}


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
  fv2=fv1.exchange(fv2);

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

  PropertyList<> PaCoordinate,PbCoordinate;
  fixVector<uint,1> pOff,pSize;
  pOff[0]=0;  pSize[0]=3;
  PaCoordinate.allocate(1);
  PbCoordinate.allocate(1);
  PaCoordinate.BuildStructure(pOff,pSize);
  PbCoordinate.BuildStructure(pOff,pSize);
  PaCoordinate[0]=0.;
  PbCoordinate[0]=0.;
  PbCoordinate[0][2]=3.;
  PropertyList<varVector,refVector,uint> PaInfo,PbInfo;
  pOff[0]=0;  pSize[0]=4;
  PaInfo.allocate(1);
  PbInfo.allocate(1);
  PaInfo.BuildStructure(pOff,pSize);
  PbInfo.BuildStructure(pOff,pSize);

  FreeSpace FS;
  DistanceEvalwStorage<3> DEval;
  DEval.allocate_storage(3);
  
  ParamList prm;
  prm.KeyList.allocate(3);
  for(uint i=0;i<3U;++i)
    prm.KeyList[i].Index.allocate(3);
  for(uint i=0;i<3U;++i)
    prm.KeyList[i].Index[0]=ParticleParticle_LJ612;
  prm.KeyList[0].Index[1]=0;  prm.KeyList[0].Index[2]=0;
  prm.KeyList[1].Index[1]=0;  prm.KeyList[1].Index[2]=1;
  prm.KeyList[2].Index[1]=1;  prm.KeyList[2].Index[2]=1;
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

  varVector<refVector<double>*> PCoordinate(2);
  fixVector<uint,2> PIdx,PKIdx;
  PIdx[0]=0;  PIdx[1]=2;
  PKIdx[0]=0; PKIdx[1]=0;
  PCoordinate[0]=&PaCoordinate[0];
  PCoordinate[1]=&PbCoordinate[0];
  E_ParPar_LJ612(PCoordinate,PIdx,PKIdx,prm,DEval,FS,Energy);
  cout<<Energy<<endl;

  PropertyList<> PropSetCoordinate,PropSetGradient;
  fixVector<uint,3> psOff,psSize;
  psOff[0]=0;   psSize[0]=3;
  psOff[1]=3;   psSize[1]=3;
  psOff[2]=6;   psSize[2]=3;
  PropSetCoordinate.allocate(3);
  PropSetGradient.allocate(3);
  PropSetCoordinate.BuildStructure(psOff,psSize);
  PropSetGradient.BuildStructure(psOff,psSize);
  for(uint i=0;i<3;++i)
    PropSetCoordinate[i]=0.;
  PropSetCoordinate[2][2]=3.;
  fixVector<uint,3> PropSetIdx, PropSetKIdx,PropSetMerType;
  for(uint i=0;i<3;++i) {
    PropSetIdx[i]=i;
    PropSetKIdx[i]=0;
    PropSetMerType[i]=Particle;
  }

  IDList<DistanceEvalwStorage<3>,FreeSpace> idl;
  idl.allocate(1,2);
  idl.List[0][0]=0;
  idl.List[0][1]=2;
  idl.KindIdx[0][0]=0;
  idl.KindIdx[0][1]=0;
  for(uint i=0;i<1;i++)
  for(uint k=0;k<2;++k)
    idl.Coordinate[i][k]=&PropSetCoordinate[idl.List[i][k]];
  SetInteraction(idl,ParticleParticle_LJ612);
  E_List(idl,prm,DEval,FS,Energy);
  cout<<Energy<<endl;

  PropertyList<> PSCoordinate,PSVelocity,PSGradient,PSMass,PSIvMass,PSDMask;
  fixVector<uint,2> PSOff,PSSize;
  PSOff[0]=0;         PSSize[0]=3;
  PSOff[1]=3;         PSSize[1]=3;
  PSCoordinate.allocate(2);
  PSVelocity.allocate(2);
  PSGradient.allocate(2);
  PSMass.allocate(2);
  PSIvMass.allocate(2);
  PSDMask.allocate(2);
  PSCoordinate.BuildStructure(PSOff,PSSize);
  PSVelocity.BuildStructure(PSOff,PSSize);
  PSGradient.BuildStructure(PSOff,PSSize);
  PSMass.BuildStructure(PSOff,PSSize);
  PSIvMass.BuildStructure(PSOff,PSSize);
  PSDMask.BuildStructure(PSOff,PSSize);
  PSCoordinate[0]=0.;
  PSCoordinate[1]=0.;     PSCoordinate[1][0]=1.;
  PSVelocity[0]=0.;
  PSVelocity[1]=0.;
  PSMass[0]=1.;
  PSMass[1]=1.;
  PSIvMass[0]=1.;
  PSIvMass[1]=1.;
  PSDMask[0]=1.;
  PSDMask[1]=1.;
  fixVector<uint,2> PSIdx,PSKIdx,PSMerType;
  PSIdx[0]=0;   PSIdx[1]=1;
  PSKIdx[0]=0;  PSKIdx[1]=1;
  PSMerType[0]=Particle;
  PSMerType[1]=Particle;

  varVector<IDList<DistanceEvalwStorage<3>,FreeSpace> > IDLS(1);
  IDLS[0].allocate(1,2);
  IDLS[0].List[0][0]=0;
  IDLS[0].List[0][1]=1;
  for(uint i=0;i<1;i++)
  for(uint k=0;k<2;++k) {
    IDLS[0].KindIdx[i][k]=PSKIdx[IDLS[0].List[i][k]];
    IDLS[0].Coordinate[i][k]=&PSCoordinate[IDLS[0].List[i][k]];
    IDLS[0].Gradient[i][k]=&PSGradient[IDLS[0].List[i][k]];
  }
  SetInteraction(IDLS[0],ParticleParticle_Harmonic);
  Energy=0.;

  ParamList HPList;
  HPList.KeyList.allocate(4);
  for(uint i=0;i<4U;++i)  HPList.KeyList[i].Index.allocate(3);
  for(uint i=0;i<4U;++i)  HPList.KeyList[i].Index[0]=ParticleParticle_Harmonic;
  HPList.KeyList[0].Index[1]=0;     HPList.KeyList[0].Index[2]=0;
  HPList.KeyList[1].Index[1]=0;     HPList.KeyList[1].Index[2]=1;
  HPList.KeyList[2].Index[1]=1;     HPList.KeyList[2].Index[2]=0;
  HPList.KeyList[3].Index[1]=1;     HPList.KeyList[3].Index[2]=1;
  for(uint i=0;i<4U;++i)    HPList.KeyList[i].BuildHash();
  HPList.ValueList.allocate(4);
  for(uint i=0;i<4U;++i)    HPList.ValueList[i].allocate(3);
  HPList.ValueList[0][0]=1.;  HPList.ValueList[0][1]=100.;
  HPList.ValueList[1][0]=2.;  HPList.ValueList[1][1]=1000.;
  HPList.ValueList[2][0]=2.;  HPList.ValueList[2][1]=1000.;
  HPList.ValueList[3][0]=3.;  HPList.ValueList[3][1]=10.;
  for(uint i=0;i<4U;++i)    HPList.ValueList[i][2]=2*HPList.ValueList[i][1];
  HPList.UpdateHashTree();

  DistanceEvalwStorage<3> DEval2;
  DEval2.allocate_storage(2);

  Energy=0.;
  EG_ListSet(IDLS,HPList,DEval2,FS,Energy);
  cout<<Energy<<endl;
  cout<<PSGradient[0]<<endl;

  PropertyList<varVector,refVector,uint> PSSizeInf;
  PSSizeInf.allocate(2);
  PSOff[0]=0; PSSize[0]=1;
  PSOff[1]=1; PSSize[1]=1;
  PSSizeInf.BuildStructure(PSOff,PSSize);
  MonomerPropagator PgFmt;
  SetAsPEV(PgFmt);
  PgFmt.Alloc(PgFmt.runParam,PSSizeInf[0]);

  Propagator<DistanceEvalwStorage<3>,FreeSpace> PgS;
  SetAsEV(PgS,PSMerType);
  double dt=0.001;
  PgS.CmnGbSetFunc[SetCmnTimeStep](PgS.CmnGbParam,&dt,1);

  PgFmt.Sync(PSIvMass[0],PgS.GbParam,PgS.CmnGbParam,PgFmt.runParam);
  
  PgS.AllocAll(PSSizeInf);
  
  double tt=0.01,st=0.,ot=0.001;
  PgS.CmnGbSetFunc[SetCmnTotalTime](PgS.CmnGbParam,&tt,1);
  PgS.CmnGbSetFunc[SetCmnStartTime](PgS.CmnGbParam,&st,1);
  PgS.CmnGbSetFunc[SetCmnOutputInterval](PgS.CmnGbParam,&ot,1);
  PgS.SyncAll(PSIvMass,PSDMask);
  PgS.OutFunc=OutputFunc;
  PgS.Run(PSCoordinate,PSVelocity,PSGradient,PSMass,HPList,IDLS,DEval2,FS,cout);


  /// the test for random generator is commented to speed the test
  /*
  fixVector<uint,100000> hist;
  hist=0U;
  UniformDbRNG urng;
  urng.SetWithSeed(123337961);
  for(uint i=0;i<100000000;++i)  hist[static_cast<uint>(urng()*100000)]++;
  //for(uint i=0;i<100000;++i)  cout<<i*0.001<<"\t"<<hist[i]<<endl;
  fixVector<uint,400> hhist;
  hhist=0U;
  for(int i=0;i<100000;++i)   hhist[hist[i]-800]++;
  for(int i=0;i<400;++i)   cout<<i-200<<"\t"<<hhist[i]<<endl;

  cout<<endl;
  GaussianRNG grng;
  fixVector<uint,20000> histg;
  histg=0U;
  grng.SetWithSeed(123337961);
  for(uint i=0;i<100000000;++i) histg[static_cast<uint>((grng()+10)*1000)]++;
  for(uint i=0;i<20000;++i)
    cout<<(i-10000.)*0.001<<"\t"<<histg[i]<<endl;
  */

  GaussianRNG grng;
  grng.SetWithSeed(123337961);

  PSCoordinate[0]=0.;
  PSCoordinate[1]=0.; PSCoordinate[1][0]=1.;
  PSVelocity[0]=0.;
  PSVelocity[1]=0.;

  Propagator<DistanceEvalwStorage<3>,FreeSpace> PgL;
  SetAsLV(PgL,PSMerType);
  PgL.CmnGbSetFunc[SetCmnTimeStep](PgL.CmnGbParam,&dt,1);
  PSSizeInf[0][0]=3;  PSSizeInf[1][0]=3;
  PgL.AllocAll(PSSizeInf);

  PgL.CmnGbSetFunc[SetCmnTotalTime](PgL.CmnGbParam,&tt,1);
  PgL.CmnGbSetFunc[SetCmnStartTime](PgL.CmnGbParam,&st,1);
  PgL.CmnGbSetFunc[SetCmnOutputInterval](PgL.CmnGbParam,&ot,1);
  double Temp=1.,Visco=1., hRadius=1.;
  PgL.GbSetFunc[SetTemperatureLV](PgL.GbParam,&Temp,1);
  PgL.GbSetFunc[SetViscosityLV](PgL.GbParam,&Visco,1);
  PgL.GbSetFunc[SetGRNGPointerLV](
      PgL.GbParam,reinterpret_cast<double*>(&grng),1);
  for(uint i=0;i<PSCoordinate.size();++i)
    PgL.UnitMove[i].SetFunc[SetHydrodynamicRadiusPLV](
        PgL.UnitMove[i].runParam,&hRadius,1);
  PgL.SyncAll(PSIvMass,PSDMask);
  PgL.OutFunc=OutputFunc;
  DEval2.Update();
  Energy=0;
  PSGradient[0]=0.;
  PSGradient[1]=0.;
  EG_ListSet(IDLS,HPList,DEval2,FS,Energy);
  for(uint i=0;i<PSCoordinate.size();++i) {
    cout<<i<<"\t";
    cout<<PgL.UnitMove[i].runParam[BasicPLV][RandomVelocitySizePLV]<<endl;
  }
  PgL.Run(PSCoordinate,PSVelocity,PSGradient,PSMass,
          HPList,IDLS,DEval2,FS,cout);

  PropertyList<> PSMCoordinate,PSMVelocity,PSMGradient,PSMMass,PSMIvMass,
                 PSMDMask;
  PropertyList<varVector,refVector,uint>  PSMMask,PSMSizeInf;
  fixVector<uint,2> PSMIdx,PSMKIdx,PSMMerType;
  fixVector<uint,2> PSMOff, PSMSize;
  PSMOff[0]=0;    PSMSize[0]=3;
  PSMOff[1]=3;    PSMSize[1]=3;
  PSMCoordinate.allocate(2);  PSMCoordinate.BuildStructure(PSMOff,PSMSize);
  PSMVelocity.allocate(2);    PSMVelocity.BuildStructure(PSMOff,PSMSize);
  PSMGradient.allocate(2);    PSMGradient.BuildStructure(PSMOff,PSMSize);
  PSMMass.allocate(2);        PSMMass.BuildStructure(PSMOff,PSMSize);
  PSMIvMass.allocate(2);      PSMIvMass.BuildStructure(PSMOff,PSMSize);
  PSMDMask.allocate(2);       PSMDMask.BuildStructure(PSMOff,PSMSize);
  PSMMask.allocate(2);        PSMMask.BuildStructure(PSMOff,PSMSize);
  PSMOff[0]=0;    PSMSize[0]=1;
  PSMOff[1]=1;    PSMSize[1]=1;
  PSMSizeInf.allocate(2);     PSMSizeInf.BuildStructure(PSMOff,PSMSize);
  PSMMerType=Particle;
  //PSM.gAllocate(PSMType,PSMFlag,3);
  PSMCoordinate[0]=0.;
  PSMCoordinate[1]=0.;   PSMCoordinate[1][0]=1.;
  for(uint i=0;i<2U;++i)  Activate(PSMMask[i],PSMDMask[i]);
  PSMIdx[0]=0;
  PSMIdx[1]=1;
  PSMKIdx[0]=0;
  PSMKIdx[1]=1;

  cout<<PSMCoordinate.PropertyData<<endl;

  /*
  fixVector<double,6> Drc;
  Drc=0.;
  Drc[0]=-1.;
  Drc[4]=1.;

  cout<<MinimalStep4(PSM.gDProperty[gCoordinate],Drc,PSM.gIProperty[gMask])<<endl;

  ParamList MPList;
  MPList.KeyList.allocate(4);
  for(uint i=0;i<4U;++i)  MPList.KeyList[i].Index.allocate(3);
  for(uint i=0;i<4U;++i)  MPList.KeyList[i].Index[0]=ParticleParticle_Harmonic;
  MPList.KeyList[0].Index[1]=0;     MPList.KeyList[0].Index[2]=0;
  MPList.KeyList[1].Index[1]=0;     MPList.KeyList[1].Index[2]=1;
  MPList.KeyList[2].Index[1]=1;     MPList.KeyList[2].Index[2]=0;
  MPList.KeyList[3].Index[1]=1;     MPList.KeyList[3].Index[2]=1;
  for(uint i=0;i<4U;++i)    MPList.KeyList[i].BuildHash();
  MPList.ValueList.allocate(4);
  for(uint i=0;i<4U;++i)    MPList.ValueList[i].allocate(3);
  MPList.ValueList[0][0]=1.;  MPList.ValueList[0][1]=100.;
  MPList.ValueList[1][0]=2.;  MPList.ValueList[1][1]=1000.;
  MPList.ValueList[2][0]=2.;  MPList.ValueList[2][1]=1000.;
  MPList.ValueList[3][0]=3.;  MPList.ValueList[3][1]=10.;
  for(uint i=0;i<4U;++i)    MPList.ValueList[i][2]=2*MPList.ValueList[i][1];
  MPList.UpdateHashTree();

  varVector<IDList<DistanceEvalwStorage<3>,FreeSpace> > MIDLS(1);
  MIDLS[0].set_interaction(ParticleParticle_Harmonic);
  MIDLS[0].allocate(1,2);
  MIDLS[0].List[0][0]=0;
  MIDLS[0].List[0][0]=1;

  Energy=0.;
  PSM.gDProperty[gGradient]=0.;
  DEval2.Update();
  EG_ListSet(PSM,MPList,MIDLS,DEval2,FS,Energy);
  cout<<PSM[0].Gradient<<endl;
  cout<<Energy<<endl;

  MinimizerKern<DistanceEvalwStorage<3>,FreeSpace>  tMK;

  tMK.Import(PSM,DEval2,MPList,MIDLS,FS,Energy);

  cout<<tMK.MinSys.size()<<endl;
  cout<<tMK.MinSys[0].Coordinate.size()<<endl;
  cout<<tMK.MinSys[1].Gradient.size()<<endl;
  cout<<tMK.MinE<<endl;
  cout<<tMK.runParamPtr<<endl;
  cout<<tMK.runGeoPtr<<endl;
  cout<<tMK.runDEvalPtr<<endl;
  cout<<tMK.runIDLSPtr<<endl;

  CoarseMinimizerKern<DistanceEvalwStorage<3>,FreeSpace>  CMK;

  cout<<CMK.DefaultMaxIter<<endl;

  CMK.SetStep(0.01);
  cout<<CMK.Step<<endl;

  CMK.Import(PSM,DEval2,MPList,MIDLS,FS,Energy);

  CMK.MinimizeAlongLine(Drc);
  cout<<CMK.MinSys[0].Coordinate<<endl;
  cout<<CMK.MinSys[1].Coordinate<<endl;
  cout<<CMK.MinE<<endl;

  SteepestDescentMin<DistanceEvalwStorage<3>,FreeSpace> SDM;
  SDM.Import(PSM,DEval2,MPList,MIDLS,FS,Energy);
  SDM.Go();
  cout<<SDM.MinSys[0].Coordinate<<endl;
  cout<<SDM.MinSys[1].Coordinate<<endl;
  cout<<SDM.MinE<<endl;
  cout<<SDM.MinGCount<<endl;

  ConjGradientMin<DistanceEvalwStorage<3>,FreeSpace>  CGM;
  CGM.Import(PSM,DEval2,MPList,MIDLS,FS,Energy);
  CGM.Go();
  cout<<CGM.MinSys[0].Coordinate<<endl;
  cout<<CGM.MinSys[1].Coordinate<<endl;
  cout<<CGM.MinE<<endl;
  cout<<CGM.MinGCount<<endl;
  */

  return 1;
}

