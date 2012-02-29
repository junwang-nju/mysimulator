
#include "system/interface.h"
#include "system/content/with-egv/allocate.h"
#include "system/content/with-egv/refer.h"
#include "system/interaction/use.h"
#include "system/propagate/allocate.h"
#include "system/evaluate/regular.h"
#include "boundary/free/allocate.h"
#include "random/box-muller/allocate.h"
#include "random/mt/allocate.h"
#include "topology/angle/calc.h"
#include "topology/dihedral/calc.h"
#include "dynamics/evolute.h"
#include "dynamics/bind.h"
#include "dynamics/output/energy/link.h"
#include "io/output/file/copy.h"

#include "interaction/func/allocate.h"
#include "pdb/load.h"
#include "pdb/atom/position/io.h"
#include "pdb/contact/analyse.h"
#include "array/2d/allocate.h"
#include "array/2d/fill.h"
#include "array/2d/refer.h"
#include "array/2d/shift.h"
#include "array/2d/norm.h"
#include "array/2d/dot.h"
#include "array/2d/copy.h"
#include "array/2d/scale.h"
#include "array/2d/inverse.h"
#include "array/2d/square-root.h"
#include "array/1d/io.h"
#include "array/2d/io.h"
using namespace mysimulator;

int main() {
  PDBObject PO;
  load(PO,"2CI2");
  /*
  COut<<PO.Model.size<<Endl;
  COut<<PO.Model[0].Molecule.size<<Endl;
  COut<<PO.Model[0].Molecule[0].Residue.size<<Endl;
  COut<<PO.Model[0].Molecule[0].Residue[4].Atom[AtomN]->Loc<<Endl;
  if(PO.Model.size>3)
    COut<<PO.Model[2].Molecule[0].Residue[4].Atom[AtomN]->Loc<<Endl;
  if(PO.Model[0].Molecule.size>1)
    COut<<PO.Model[0].Molecule[1].Residue[4].Atom[AtomN]->Loc<<Endl;
  COut<<Endl;
  */

  Array2D<int> ID;
  allocate(ID,10000,4);
  fill(ID,-1);
  unsigned int n;
  n=PDB2Contact<HeavyAtoms,FirstModel>(PO,ID,5.);

  Array2D<int> IDMap;
  Array1D<unsigned int> size;
  unsigned int N;
  allocate(size,PO.Model[0].Molecule.size);
  for(unsigned int i=0;i<size.size;++i)
    size[i]=PO.Model[0].Molecule[i].Residue.size;
  allocate(IDMap,size);
  N=0;
  for(unsigned int i=0;i<IDMap.NumLines();++i)
    for(unsigned int k=0;k<IDMap[i].size;++k) IDMap[i][k]=N++;

  int l1,r1,l2,r2,m1,m2;
  unsigned int nc;
  nc=0;
  for(unsigned int i=0;i<n;i++) {
    l1=ID[i][0];    r1=ID[i][1];
    l2=ID[i][2];    r2=ID[i][3];
    m1=IDMap[l1][r1];
    m2=IDMap[l2][r2];
    if((l1==l2)&&(r1+4>r2)) {}
    else  nc++;
  }

  typedef Array1D<int> IDType;
  typedef Array1D<Unique64Bit> ParamType;

  Array2D<double> X;
  Array1D<IDType> mID;
  Array1D<ParamType> Param;
  FreeSpace FS;
  System<double,Array1D<IDType>,Array1D<ParamType>,FreeSpace,Array2D,
         SysContentWithEGV> S;
  BoxMuller<MersenneTwister<dSFMT,19937> > GR;

  allocate(X,N,3);
  N=0;
  for(unsigned int i=0;i<size.size;++i)
  for(unsigned int k=0;k<size[i];++k) {
    X[N][0]=PO.Model[0].Molecule[i].Residue[k].Atom[AtomCA]->Loc.X;
    X[N][1]=PO.Model[0].Molecule[i].Residue[k].Atom[AtomCA]->Loc.Y;
    X[N][2]=PO.Model[0].Molecule[i].Residue[k].Atom[AtomCA]->Loc.Z;
    ++N;
  }

  allocate(FS,3);

  allocate(mID,N-1+N-2+N-3+nc);
  for(unsigned int i=0;i<N-1;++i)   allocate(mID[i],2);
  for(unsigned int i=0;i<N-2;++i)   allocate(mID[i+N-1],3);
  for(unsigned int i=0;i<N-3;++i)   allocate(mID[i+N-1+N-2],4);
  for(unsigned int i=0;i<nc;++i)    allocate(mID[i+N-1+N-2+N-3],2);
  for(unsigned int i=0;i<N-1;++i) {
    mID[i][0]=i;  mID[i][1]=i+1;
  }
  for(unsigned int i=0,j=N-1;i<N-2;++i,++j) {
    mID[j][0]=i;  mID[j][1]=i+1;  mID[j][2]=i+2;
  }
  for(unsigned int i=0,j=N-1+N-2;i<N-3;++i,++j) {
    mID[j][0]=i;  mID[j][1]=i+1;  mID[j][2]=i+2;  mID[j][3]=i+3;
  }
  nc=N-1+N-2+N-3;
  for(unsigned int i=0;i<n;i++) {
    l1=ID[i][0];    r1=ID[i][1];
    l2=ID[i][2];    r2=ID[i][3];
    m1=IDMap[l1][r1];
    m2=IDMap[l2][r2];
    if((l1==l2)&&(r1+4>r2)) {}
    else {
      mID[nc][0]=m1;    mID[nc][1]=m2;
      ++nc;
    }
  }

  release(size);

  unsigned int g,u;
  double dist,ang,dih;
  Array2D<double> tmvec;
  allocate(tmvec,6,3);
  allocate(Param,mID.size);
  g=0;
  for(unsigned int i=0;i<N-1;++i,++g) {
    allocate(Param[g],HarmonicNumberParameters);
    dist=Distance(tmvec[0],X[mID[g][0]],X[mID[g][1]],FS);
    Param[g][HarmonicEqLength].d=dist;
    Param[g][HarmonicEqStrength].d=100./(dist*dist);
    BuildParameterHarmonic<double>(Param[g]);
  }
  for(unsigned int i=0;i<N-2;++i,++g) {
    allocate(Param[g],AngleHarmonicNumberParameters);
    ang=arcCos(cosAngle(X[mID[g][0]],X[mID[g][1]],X[mID[g][2]],FS));
    Param[g][AngHarmonicEqAngle].d=ang;
    Param[g][AngHarmonicStrength].d=20.;
    BuildParameterAngleHarmonic<double>(Param[g]);
  }
  for(unsigned int i=0;i<N-3;++i,++g) {
    allocate(Param[g],
             DihPeriodicFuncParamShift+2*DihPeriodicFuncNumberParameters);
    dih=Dihedral(X[mID[g][0]],X[mID[g][1]],X[mID[g][2]],X[mID[g][3]],FS);
    Param[g][DihPeriodicNumFuncs].value<unsigned int>()=2U;
    u=DihPeriodicFuncParamShift;
    Param[g][u+DihPeriodicFuncFrequence].value<unsigned int>()=1U;
    Param[g][u+DihPeriodicFuncStrength].d=1.;
    Param[g][u+DihPeriodicFuncPhase].d=M_PI-dih;
    u+=DihPeriodicFuncNumberParameters;
    Param[g][u+DihPeriodicFuncFrequence].value<unsigned int>()=3U;
    Param[g][u+DihPeriodicFuncStrength].d=0.5;
    Param[g][u+DihPeriodicFuncPhase].d=M_PI-dih;
    BuildParameterDihedralPeriodic<double>(Param[g]);
  }
  for(unsigned int i=g;i<Param.size;++i) {
    allocate(Param[i],LJ612NumberParameters);
    dist=Distance(tmvec[0],X[mID[i][0]],X[mID[i][1]],FS);
    Param[i][LJ612EqRadius].d=dist;
    Param[i][LJ612EqEnergyDepth].d=1.;
    BuildParameterLJ612<double>(Param[i]);
  }

  allocate(S.Content);
  allocate(S.Interactions,1);
  allocate(S.Propagates,1);

  allocate(S.Content(),X);

  useParam(S.Interactions[0],Param);
  useID(S.Interactions[0],mID);
  allocate(S.Interactions[0].Geom);
  allocate(S.Interactions[0].Geom(),3);
  allocate(S.Interactions[0].EGData);
  allocate(S.Interactions[0].EGData(),X);
  allocate(S.Interactions[0].Func,mID.size);
  g=0;
  for(unsigned int i=0;i<N-1;++i,++g)
    allocate(S.Interactions[0].Func[g],Harmonic,3);
  for(unsigned int i=0;i<N-2;++i,++g)
    allocate(S.Interactions[0].Func[g],AngleHarmonic,3);
  for(unsigned int i=0;i<N-3;++i,++g)
    allocate(S.Interactions[0].Func[g],DihedralPeriodic,3);
  for(unsigned int i=g;i<mID.size;++i)
    allocate(S.Interactions[0].Func[i],LJ612,3);
  SetWorkFunc(S.Interactions[0],ArrayInteraction);

  allocate(S.Propagates[0],SysConstEVelVerlet,1);
  S.Propagates[0].MerIDRange[0].u[0]=0;
  S.Propagates[0].MerIDRange[0].u[1]=N-1;
  S.Propagates[0].buildGroupContent(S.Content());

  S.build();

  S.Propagates[0].Param[ModCEVVerletMass].u[0]=ArrayMass;

  allocate(GR);
  GR.init(23293);

  Dynamics<MicroCanonicalVVerlet,double,Array2D,
           DynamicsOutputEnergy<FileOutput,double,Array1D<IDType>,
                                Array1D<ParamType>,FreeSpace,Array2D,
                                SysContentWithEGV> >
  DynMC;

  allocate(DynMC.Output.BaseData);
  bind(DynMC,S);

  COut.precision(12);
  copy(S.Content().X(),X);
  fillArray(GR,S.Content().Velocity());
  GenericEvaluate(S.Content(),S.Interactions);
  COut<<S.Content().EGData.Energy()<<Endl;

  DynMC.BaseData.TimeStep=0.001;
  DynMC.BaseData.NumSteps=10000;
  DynMC.BaseData.StartTime=0.;
  DynMC.updateRunPeriod();
  fill(DynMC.BaseData.Mass,1.);
  S.Propagates[0].update(CalcCEVVerletHTIM);
  S.Propagates[0].update(CalcCEVVerletKE);
  allocate(DynMC.Output.OS);
  copy(DynMC.Output.OS(),COut);
  DynMC.Output.BaseData().TimeBwOutput=0.002;
  DynMC.Output.BaseData().NumStepsBwOutput=2;
  DynMC.Output.IsFirstOutput=true;
  DynMC.Output.BaseData().setNowTime(DynMC.BaseData.NowTime);

  unbind(DynMC,S);

  return 0;
}

