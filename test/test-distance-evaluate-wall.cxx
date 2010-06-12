
#include "distance-evaluate-wall.h"
#include "distance-evaluate-direct.h"
#include "free-space.h"
#include <iostream>
using namespace std;

int main() {

  DistanceEvalDirect DED;
  FreeSpace FS;
  allocate(DED,3,5);
  allocate(FS,3);

  Vector<double> Coor;
  allocate(Coor,3);
  assign(Coor,1.);

  cout<<"Test -- distance to plane"<<endl;
  Vector<UniqueParameter> Plane;
  allocate(Plane,6);
  Plane[0].d=2.;
  Plane[1].d=1.;
  Plane[2].d=0.;
  Plane[3].d=-1./sqrt(2);
  Plane[4].d=-1./sqrt(2);
  Plane[5].d=0.;
  DistanceDisplacement2Plane(&Coor,&uZero,Plane(),DED,FS);
  cout<<DED()<<endl;
  cout<<DED.displacementvec<<endl;
  cout<<endl;

  cout<<"Test -- distance to sphere"<<endl;
  Vector<UniqueParameter> Sphere;
  allocate(Sphere,5);
  Sphere[0]=5.5;
  Sphere[1]=1.;
  Sphere[2]=1.;
  Sphere[3]=0.;
  Sphere[4]=0.5;
  DistanceDisplacement2Sphere(&Coor,&uZero,Sphere(),DED,FS);
  cout<<DED()<<endl;
  cout<<DED.displacementvec<<endl;
  cout<<endl;

  return 0;
}

