
#include "interaction-method.h"
#include "distance-evaluate-direct.h"
#include "free-space.h"
#include <iostream>

using namespace std;

int main() {
  cout<<"Test -- initialize"<<endl;
  InteractionMethod<DistanceEvalDirect,FreeSpace> IM;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(IM);
  cout<<endl;

  cout<<"Test -- assign"<<endl;
  InteractionMethod<DistanceEvalDirect,FreeSpace> IM2;
  allocate(IM2);
  assign(IM2,IM);
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(IM2);
  cout<<endl;

  cout<<"Test - check availability"<<endl;
  cout<<IsAvailable(IM)<<endl;
  cout<<IsAvailable(IM2)<<endl;
  cout<<endl;

  cout<<"Test -- refer"<<endl;
  refer(IM2,IM);
  cout<<endl;
  return 1;
}

