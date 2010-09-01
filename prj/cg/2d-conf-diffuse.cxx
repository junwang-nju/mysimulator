
#include "property-list.h"
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

int main(int argc, char** argv) {
  if(argc<3)  return 1;
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

  PropertyList<unsigned int> nbID;
  PropertyList<double> transP;
  char buff[2048];
  ifs.open("12-conf.basic-move");
  allocate(sz,15037);
  for(unsigned int i=0,tu;i<15037;++i) {
    ifs>>tu;
    ifs>>sz[i];
    ifs.getline(buff,2047);
  }
  allocate(nbID,sz);
  allocate(transP,sz);
  ifs.seekg(0,ios::beg);
  for(unsigned int i=0,tu;i<15037;++i) {
    ifs>>tu;
    ifs>>tu;
    for(unsigned int k=0;k<sz[i];++k)
      ifs>>nbID[i][k];
  }
  ifs.close();

  const double Temperature=0.6;
  const double A=1e-3;
  double dE;
  for(unsigned int i=0;i<15037;++i) {
    for(unsigned int k=0;k<nbID[i].size;++k) {
      dE=E[nbID[i][k]]-E[i];
      transP[i][k]=(dE<0?1.:exp(-dE/Temperature))*A;
    }
  }

  Vector<double> M,dM;
  double rM,S;
  allocate(M,15037);
  allocate(dM,15037);

  unsigned int bu,eu,rt;
  bu=atoi(argv[1]);
  eu=atoi(argv[2]);
  for(unsigned int u=bu;u<eu;++u)
  for(unsigned int v=0;v<nbID[u].size;++v) {
    if(u>nbID[u][v])  continue;
    assign(M,0.);
    M[u]=1;
    M[nbID[u][v]]=-1;

    S=1;
    for(rt=0;rt<800000000;++rt) {
      assign(dM,0.);
      for(unsigned int i=0;i<15037;++i)
        for(unsigned int k=0;k<nbID[i].size;++k) {
          rM=M[i]*transP[i][k];
          dM[nbID[i][k]]+=rM;
          dM[i]-=rM;
        }
      shift(M,dM);
      rM=asum(M);
      if(rM<1e-3) {
        S+=0.5*rM;  break;
      } else
        S+=rM;
    }
    cout<<u<<"\t"<<nbID[u][v]<<"\t"<<S<<"\t"<<rt<<endl;
  }

  return 0;
}

