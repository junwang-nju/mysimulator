
#include "distance-evaluate-base.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- initialize"<<endl;
  DistanceEvalBase DEB;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(DEB,5);
  cout<<DEB.size<<endl;
  cout<<endl;

  cout<<"Test -- access (directly)"<<endl;
  DEB.displacement[0]=12.8;
  DEB.displacement[1]=2.9;
  DEB.displacement[2]=1.5;
  DEB.displacement[3]=-12.;
  DEB.displacement[4]=23.4;
  DEB()=normSQ(DEB.displacement,5);
  cout<<DEB()<<endl;
  cout<<endl;

  cout<<"Test -- assign from another DistanceEvalBase"<<endl;
  DistanceEvalBase DEB2;
  allocate(DEB2,4);
  assign(DEB2,DEB);
  for(unsigned int i=0;i<DEB2.size;++i)
    cout<<DEB2.displacement[i]<<"\t";
  cout<<endl;
  cout<<DEB2()<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(DEB2);
  cout<<endl;

  cout<<"Test -- availability check"<<endl;
  cout<<IsAvailable(DEB)<<endl;
  cout<<IsAvailable(DEB2)<<endl;
  cout<<endl;

  cout<<"Test -- refer operation"<<endl;
  refer(DEB2,DEB);
  for(unsigned int i=0;i<DEB2.size;++i)
    cout<<DEB2.displacement[i]<<"\t";
  cout<<endl;
  cout<<DEB2()<<endl;
  cout<<endl;

  cout<<"Test -- check whether DistanceEval method"<<endl;
  cout<<IsDistanceEvalMethod(DEB)<<endl;
  cout<<IsDistanceEvalMethod(DEB.displacement)<<endl;
  cout<<endl;

  return 1;
}

