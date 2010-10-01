
#include "property-list.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

void Conf2Coor(const Vector<unsigned int>& Conf, PropertyList<int>& Coor) {
  unsigned int n=Conf.size;
  Coor[0][0]=0;
  Coor[0][1]=0;
  Coor[0][2]=0;
  for(unsigned int i=0;i<n;++i) {
    Coor[i+1]=Coor[i];
    switch(Conf[i]) {
      case 0: Coor[i+1][0]++; break;
      case 1: Coor[i+1][1]++; break;
      case 2: Coor[i+1][2]++; break;
      case 3: Coor[i+1][2]--; break;
      case 4: Coor[i+1][1]--; break;
      case 5: Coor[i+1][0]--; break;
    }
  }
}

double Energy(const Vector<unsigned int>& Conf, PropertyList<int>& Coor,
              const PropertyList<double>& PotMat) {
  double e=0.;
  Conf2Coor(Conf,Coor);
  for(unsigned int i=0,tu;i<12;++i)
  for(unsigned int j=i+3;j<12;j+=2) {
    tu=abs(Coor[i][0]-Coor[j][0])+abs(Coor[i][1]-Coor[j][1])+
       abs(Coor[i][2]-Coor[j][2]);
    if(tu==1) e+=PotMat[i][j];
  }
  return e;
}

int main(int argc, char** argv) {
  if(argc<3)  return 1;
  ifstream ifs;
  Vector<unsigned int> sz;

  PropertyList<unsigned int> Conf;
  allocate(sz,885641);
  assign(sz,11);
  allocate(Conf,sz);

  ifs.open("12-conf-3d");
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
  allocate(E,885641);

  const unsigned NatID=806645;
  Conf2Coor(Conf[NatID],Coor);
  assign(PotMat,0.);
  for(unsigned int i=0,tu;i<12;++i)
  for(unsigned int j=i+3;j<12;j+=2) {
    tu=abs(Coor[i][0]-Coor[j][0])+abs(Coor[i][1]-Coor[j][1])+
       abs(Coor[i][2]-Coor[j][2]);
    if(tu==1) { PotMat[i][j]=-1.; PotMat[j][i]=-1.; }
  }

  for(unsigned int i=0;i<885641;++i) E[i]=Energy(Conf[i],Coor,PotMat);

  PropertyList<unsigned int> nbID;
  PropertyList<double> transP;
  char buff[2048];
  ifs.open("12-conf-3d.basic-move");
  allocate(sz,885641);
  for(unsigned int i=0,tu;i<885641;++i) {
    ifs>>tu;
    ifs>>sz[i];
    ifs.getline(buff,2047);
  }
  allocate(nbID,sz);
  allocate(transP,sz);
  ifs.seekg(0,ios::beg);
  for(unsigned int i=0,tu;i<885641;++i) {
    ifs>>tu;
    ifs>>tu;
    for(unsigned int k=0;k<sz[i];++k)
      ifs>>nbID[i][k];
  }
  ifs.close();

  const double Temperature=0.6;
  double A=1e-5;
  double dE;
  for(unsigned int i=0;i<885641;++i) {
    for(unsigned int k=0;k<nbID[i].size;++k) {
      dE=E[nbID[i][k]]-E[i];
      transP[i][k]=(dE<0?1.:exp(-dE/Temperature));
    }
  }

  Vector<double> M,dM,mM;
  double tM,rM,S,pM,uM,gM0,gM1;
  double aT;
  allocate(M,885641);
  allocate(dM,885641);
  allocate(mM,885641);

  unsigned int bu,eu,rt;
  bu=atoi(argv[1]);
  eu=atoi(argv[2]);
  for(unsigned int u=bu;u<eu;++u)
  for(unsigned int v=0;v<nbID[u].size;++v) {
    if(u>nbID[u][v])  continue;
    assign(M,0.);
    M[u]=1;
    M[nbID[u][v]]=-1;

    A=7e-2;
    S=0;
    aT=0.;
    pM=2.;
    cout<<0<<"\t"<<2.<<"\t"<<A<<endl;
    for(rt=0;rt<2000;++rt) {
      assign(dM,0.);
      for(unsigned int i=0;i<885641;++i) {
        tM=M[i];
        uM=0.;
        for(unsigned int k=0;k<nbID[i].size;++k) {
          rM=tM*transP[i][k];
          dM[nbID[i][k]]+=rM;
          uM-=rM;
        }
        dM[i]+=uM;
      }
      assign(mM,M);
      shift(mM,0.5*A,dM);
      assign(dM,0.);
      for(unsigned int i=0;i<885641;++i) {
        tM=mM[i];
        uM=0.;
        for(unsigned int k=0;k<nbID[i].size;++k) {
          rM=tM*transP[i][k];
          dM[nbID[i][k]]+=rM;
          uM-=rM;
        }
        dM[i]+=uM;
      }
      shift(M,A,dM);
      aT+=A;
      rM=asum(M);
      S+=(pM+rM)*0.5*A;
      pM=rM;
      cout<<(rt+1)*A<<"\t"<<rM<<endl;

      if(rM<5e-3) break;

    }
    gM0=pM;
    for(rt=0;rt<100;++rt) {
      assign(dM,0.);
      for(unsigned int i=0;i<885641;++i) {
        tM=M[i];
        uM=0.;
        for(unsigned int k=0;k<nbID[i].size;++k) {
          rM=tM*transP[i][k];
          dM[nbID[i][k]]+=rM;
          uM-=rM;
        }
        dM[i]+=uM;
      }
      assign(mM,M);
      shift(mM,0.5*A,dM);
      assign(dM,0.);
      for(unsigned int i=0;i<885641;++i) {
        tM=mM[i];
        uM=0.;
        for(unsigned int k=0;k<nbID[i].size;++k) {
          rM=tM*transP[i][k];
          dM[nbID[i][k]]+=rM;
          uM-=rM;
        }
        dM[i]+=uM;
      }
      shift(M,A,dM);
      aT+=A;
      rM=asum(M);
      S+=(pM+rM)*0.5*A;
      pM=rM;
    }
    gM1=pM;
    S+=gM0/((log(gM0)-log(gM1))*(100*A));
    //cout<<u<<"\t"<<nbID[u][v]<<"\t"<<S<<endl;
    u=eu+1; break;
  }

  return 0;
}

