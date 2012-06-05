
#include "system/interface.h"
#include "pdb-file/interface.h"
#include "boundary/free/interface.h"
using namespace mysimulator;

#include <iostream>
#include <fstream>
using namespace std;

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
  IFN.Allocate(NC+64,1);
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
  ArrayNumeric<double> Dsp;
  FreeSpace FS;
  Dsp.Allocate(3);
  for(unsigned int i=0;i<NC+64;++i)
    Value<double>(S.Interaction(i).Parameter(0,HarmonicEqLength))=
      Distance(Dsp,S.Location()[S.Interaction(i).Index(0)[0]],
                   S.Location()[S.Interaction(i).Index(0)[1]],FS);
  for(unsigned int i=0;i<64;++i) {
    Value<double>(S.Interaction(i).Parameter(0,HarmonicEqStrength))=100.;
    S.Interaction(i).ParameterBuild(0);
  }
  for(unsigned int i=0;i<NC;++i) {
    Value<double>(S.Interaction(i+64).Parameter(0,HarmonicEqStrength))=20;
    S.Interaction(i+64).ParameterBuild(0);
  }
  S.AssignNumberInteractionGroup(1);
  S.InteractionGroup(0).Allocate(IFN.Size());
  for(unsigned int i=0;i<IFN.Size();++i)  S.InteractionGroup(0).WorkID(i)=i;

  return 0;
}
