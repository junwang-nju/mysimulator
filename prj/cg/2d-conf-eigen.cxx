
#include "property-list.h"
#include "lapack.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

void Conf2Coor(const Vector<unsigned int>& Conf, PropertyList<int>& Coor) {
  unsigned int n=Conf.size;
  Coor[0][0]=0;
  Coor[0][1]=0;
  for(unsigned int i=0;i<n;++i) {
    Coor[i+1]=Coor[i];
    switch(Conf[i]) {
      case 0: Coor[i+1][0]++; break;
      case 1: Coor[i+1][1]++; break;
      case 2: Coor[i+1][1]--; break;
      case 3: Coor[i+1][0]--; break;
    }
  }
}

double Energy(const Vector<unsigned int>& Conf, PropertyList<int>& Coor,
              const PropertyList<double>& PotMat) {
  double e=0.;
  Conf2Coor(Conf,Coor);
  for(unsigned int i=0,tu;i<12;++i)
  for(unsigned int j=i+3;j<12;j+=2) {
    tu=abs(Coor[i][0]-Coor[j][0])+abs(Coor[i][1]-Coor[j][1]);
    if(tu==1) e+=PotMat[i][j];
  }
  return e;
}

int main() {
  ifstream ifs;
  Vector<unsigned int> sz;

  PropertyList<unsigned int> Conf;
  allocate(sz,15037);
  assign(sz,11);
  allocate(Conf,sz);

  ifs.open("12-conf");
  ifs>>Conf;
  ifs.close();

  PropertyList<double> PotMat;
  allocate(sz,12);
  assign(sz,12);
  allocate(PotMat,sz);

  PropertyList<int> Coor;
  Vector<double> E;
  assign(sz,2);
  allocate(Coor,sz);
  allocate(E,15037);

  const unsigned NatID=12623;
  Conf2Coor(Conf[NatID],Coor);
  assign(PotMat,0.);
  for(unsigned int i=0,tu;i<12;++i)
  for(unsigned int j=i+3;j<12;j+=2) {
    tu=abs(Coor[i][0]-Coor[j][0])+abs(Coor[i][1]-Coor[j][1]);
    if(tu==1) { PotMat[i][j]=-1.; PotMat[j][i]=-1.; }
  }

  for(unsigned int i=0;i<15037;++i) E[i]=Energy(Conf[i],Coor,PotMat);

  release(Conf);

  PropertyList<unsigned int> nbID;
  PropertyList<double> transP;
  char buff[2048];
  ifs.open("12-conf.basic-move");
  allocate(sz,15037);
  for(unsigned int i=0,tu;i<15037;++i) {
    ifs>>tu;
    ifs>>sz[i];
    ++sz[i];
    ifs.getline(buff,2047);
  }
  allocate(nbID,sz);
  allocate(transP,sz);
  ifs.seekg(0,ios::beg);
  for(unsigned int i=0,tu;i<15037;++i) {
    ifs>>tu;
    ifs>>tu;
    for(unsigned int k=1;k<sz[i];++k)
      ifs>>nbID[i][k];
    nbID[i][0]=i;
  }
  ifs.close();

  const double Temperature=0.6;
  //const double A=1e-3;
  double dE,sumP;
  for(unsigned int i=0;i<15037;++i) {
    sumP=0.;
    for(unsigned int k=1;k<nbID[i].size;++k) {
      dE=E[nbID[i][k]]-E[i];
      transP[i][k]=(dE<0?1.:exp(-dE/Temperature));
      sumP+=(dE>0?1.:exp(dE/Temperature));
    }
    transP[i][0]=-sumP;
  }

  PropertyList<double> Mat;
  allocate(sz,15037);
  assign(sz,15037);
  allocate(Mat,sz);
  for(unsigned int i=0;i<15037;++i) {
    for(unsigned int k=0;k<nbID[i].size;++k)
      Mat[i][nbID[i][k]]=-transP[i][k];
  }
  release(nbID);
  release(transP);

  Vector<double> eV,Work;
  Vector<int> IWork;
  int N,LWork,LIWork;
  N=15037;
  LWork=1+6*15037+2*15037*15037;
  LIWork=1+2*15037;
  allocate(eV,15037);
  cout<<"==============="<<endl;getchar();
  allocate(Work,LWork);
  cout<<"==============="<<endl;getchar();
  allocate(IWork,LIWork);
  cout<<"==============="<<endl;

  int LDA,info;
  LDA=15037;
  char J='V',P='U';

  dsyevd_(&J,&P,&N,Mat.data,&LDA,eV.data,Work.data,&LWork,IWork.data,&LIWork,
          &info);
  return 0;
}

