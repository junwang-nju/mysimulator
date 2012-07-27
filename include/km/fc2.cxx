
#include "system/interface.h"
#include "pdb-file/interface.h"
#include "boundary/free/interface.h"
using namespace mysimulator;

#include <iostream>
#include <fstream>
using namespace std;

double F(System<double,FreeSpace>& S, unsigned int NC,
         Array2DNumeric<double>& XBk, Array2DNumeric<double>& GP,
         Array2DNumeric<double>& GN) {
  static const double DT=1e-5;
  static const double Gamma=5;
  static const double IGamma=1./Gamma;
  static const unsigned int NB=NC+64+2;
  for(unsigned int i=0;i<NB;++i)  S.Interaction(i).ClearFlag();
  S.UpdateG(0);
  for(unsigned int i=1;i<=65;++i) {
    S.Velocity()[i].Copy(S.Gradient()[i]);
    S.Velocity()[i].Scale(-IGamma);
  }
  XBk.BlasCopy(S.Location());
  S.Location().BlasShift(DT,S.Velocity());
  for(unsigned int i=0;i<NB;++i)  S.Interaction(i).ClearFlag();
  S.UpdateG(0);
  GP.BlasCopy(S.Gradient());
  S.Location().BlasShift(-DT-DT,S.Velocity());
  for(unsigned int i=0;i<NB;++i)  S.Interaction(i).ClearFlag();
  S.UpdateG(0);
  GN.BlasCopy(S.Gradient());
  GP.NegShift(GN);
  double T=0;
  for(unsigned int i=1;i<=65;++i) T+=GP[i].NormSQ();
  T=__SqRoot(T)/DT*0.5;
  S.Location().BlasCopy(XBk);
  return T;
}

void G(System<double,FreeSpace>& S, unsigned int NC,
       Array2DNumeric<double>& GF,
       Array2DNumeric<double>& XBk, Array2DNumeric<double>& XBk2,
       Array2DNumeric<double>& GP, Array2DNumeric<double>& GN) {
  static const double dd=1e-6;
  static const double ihdd=0.5/dd;
  double TP,TN;
  for(unsigned int i=1;i<=65;++i)
  for(unsigned int k=0;k<3;++k) {
    XBk2.BlasCopy(S.Location());
    S.Location()[i][k]+=dd;
    TP=F(S,NC,XBk,GP,GN);
    S.Location()[i][k]-=dd+dd;
    TN=F(S,NC,XBk,GP,GN);
    GF[i][k]=-(TP-TN)*ihdd;
  }
}

int main() {

  System<double,FreeSpace>  S;
  S.AllocateKind(67);
  for(unsigned int i=0;i<67;++i) S.Kind(i)=ParticleUnit;
  S.AllocateXVGE(3);

  ifstream ifs;
  ifs.open("XAxis");
  for(unsigned int i=1;i<66;++i)
  for(unsigned int k=0;k<3;++k)   ifs>>S.Location()[i][k];
  ifs.close();
  for(unsigned int i=2;i<66;++i) S.Location()[i].NegShift(S.Location()[1]);
  S.Location()[1].Fill(0);
  for(unsigned int i=1;i<66;++i) S.Location()[i][0]+=1.;
  S.Location()[0].Fill(0);
  S.Location()[66].Copy(S.Location()[65]);
  S.Location()[66][0]+=1;

  S.Velocity().Fill(0);

  Array2DNumeric<double> XBk,XBk2,GP,GN,GF;
  XBk.Imprint(S.Location());
  XBk2.Imprint(XBk);
  GP.Imprint(XBk);
  GN.Imprint(XBk);
  GF.Imprint(XBk);

  PDBFile PF;
  PDBObject PO;
  PF.Load("2CI2");
  PF.Produce(PO);

  Array2D<unsigned int> CM;
  const unsigned int NP=PO.ProduceContact<SheaDef,UseFirstModel>(CM);
  unsigned int NC=0;
  for(unsigned int i=0;i<NP;++i)
    if(CM[i][0]!=CM[i][2])        ++NC;
    else if(CM[i][3]-CM[i][1]>=4) ++NC;

  Array2D<InteractionFuncName>  IFN;
  IFN.Allocate(NC+64+2,1);
  for(unsigned int i=0;i<NC+64;++i) IFN[i][0]=Harmonic;
  S.AllocateInteraction(IFN,3);
  for(unsigned int i=0;i<64;++i) {
    S.Interaction(i).Index(0)[0]=i+1;
    S.Interaction(i).Index(0)[1]=i+2;
  }
  for(unsigned int i=0,n=0;i<NP;++i)
    if((CM[i][0]!=CM[i][2])||(CM[i][3]-CM[i][1]>=4)) {
      S.Interaction(n+64).Index(0)[0]=PO.Index(CM[i][0],CM[i][1])+1;
      S.Interaction(n+64).Index(0)[1]=PO.Index(CM[i][2],CM[i][3])+1;
      ++n;
    }
  S.Interaction(NC+64).Index(0)[0]=0;
  S.Interaction(NC+64).Index(0)[1]=1;
  S.Interaction(NC+64+1).Index(0)[0]=65;
  S.Interaction(NC+64+1).Index(0)[1]=66;
  ArrayNumeric<double> Dsp;
  FreeSpace FS;
  Dsp.Allocate(3);
  for(unsigned int i=0;i<NC+64;++i)
    Value<double>(S.Interaction(i).Parameter(0,HarmonicEqLength))=
      Distance(Dsp,S.Location()[S.Interaction(i).Index(0)[0]],
                   S.Location()[S.Interaction(i).Index(0)[1]],FS);
  Value<double>(S.Interaction(NC+64).Parameter(0,HarmonicEqLength))=1;
  Value<double>(S.Interaction(NC+64+1).Parameter(0,HarmonicEqLength))=1;

  for(unsigned int i=0;i<64;++i) {
    Value<double>(S.Interaction(i).Parameter(0,HarmonicEqStrength))=100.;
    S.Interaction(i).ParameterBuild(0);
  }
  for(unsigned int i=0;i<NC;++i) {
    Value<double>(S.Interaction(i+64).Parameter(0,HarmonicEqStrength))=20;
    S.Interaction(i+64).ParameterBuild(0);
  }
  Value<double>(S.Interaction(NC+64).Parameter(0,HarmonicEqStrength))=20;
  S.Interaction(NC+64).ParameterBuild(0);
  Value<double>(S.Interaction(NC+64+1).Parameter(0,HarmonicEqStrength))=20;
  S.Interaction(NC+64+1).ParameterBuild(0);
  
  S.AssignNumberInteractionGroup(1);
  S.InteractionGroup(0).Allocate(IFN.Size());
  for(unsigned int i=0;i<IFN.Size();++i)  S.InteractionGroup(0).WorkID(i)=i;

  double NG,Step;
  double TP,T;

  //S.Velocity()[66][0]=1.;
  S.Location()[66][0]=15.9376;
  S.Location()[66][1]=0;
  S.Location()[66][2]=0;

  T=F(S,NC,XBk,GP,GN);
  while(true) {
    G(S,NC,GF,XBk,XBk2,GP,GN);
    XBk.BlasCopy(S.Location());
    NG=0;
    for(unsigned int i=1;i<=65;++i) NG+=GF[i].NormSQ();
    if(NG<1e-12)  break;
    else {
      NG=1./__SqRoot(NG);
      GF.BlasScale(NG);
      Step=0.1;
      while(Step>1e-8) {
        S.Location().BlasCopy(XBk);
        for(unsigned int i=1;i<=65;++i) S.Location()[i].Shift(Step,GF[i]);
        TP=F(S,NC,XBk2,GP,GN);
        if(TP<T)  { T=TP; break; }
        else Step*=0.5;
      }
      cout<<Step<<"\t"<<T<<endl;
      if(Step<1e-8) break;
    }
  }

  for(unsigned int i=0;i<67;++i) {
    for(unsigned int k=0;k<3;++k) cout<<"\t"<<S.Location()[i][k];
    cout<<endl;
  }

  return 0;
}
