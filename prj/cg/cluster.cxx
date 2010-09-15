
#include "vector.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
using namespace std;

struct Node;

struct Node {
  Node *left, *right, *parent;
  double dist;
  unsigned int gID;
  bool nowflag;
  string name;
};

int main() {
  Vector<double> bl,bh;
  Vector<unsigned int> bI,bJ;

  const unsigned int Np=20768;
  allocate(bl,Np);
  allocate(bh,Np);
  allocate(bI,20768);
  allocate(bJ,20768);

  ifstream ifs;
  ifs.open("12623.saddle.group.minmax");
  for(unsigned int i=0;i<Np;++i)
    ifs>>bI[i]>>bJ[i]>>bl[i]>>bh[i];
  ifs.close();
  unsigned int Nc;
  Nc=0;
  for(unsigned int i=0;i<Np;++i) {
    if(bI[i]>Nc) { Nc=bI[i]; }
    if(bJ[i]>Nc) { Nc=bJ[i]; }
  }

  Vector<unsigned int> gstate;
  allocate(gstate,Nc);
  for(unsigned int i=0;i<Nc;++i)  gstate[i]=i;
  unsigned int minI,minJ,minop;
  double minBL,tBL;

  stringstream *ss;
  Vector<Node> nd;
  Node *iND,*jND;
  unsigned int NowNode;
  allocate(nd,Nc+Nc);
  for(unsigned int i=0;i<Nc;++i) {
    nd[i].dist=-1.;
    nd[i].gID=i;
    nd[i].nowflag=true;
    nd[i].parent=NULL;
    nd[i].left=NULL;
    nd[i].right=NULL;
    ss=new stringstream;
    (*ss)<<i;
    nd[i].name=ss->str();
    delete ss;
    nd[i+Nc].nowflag=false;
  }
  NowNode=Nc;

  do{
    minI=minJ=0;
    minBL=1e10;
    iND=jND=NULL;
    minop=0;
    for(unsigned int i=0;i<Np;++i) {
      if(gstate[bI[i]]==gstate[bJ[i]])  continue;
      tBL=bl[i];
      if(minBL>tBL) {
        minBL=tBL;
        minI=gstate[bI[i]];
        minJ=gstate[bJ[i]];
        minop++;
      }
    }
    if(minop>0) {
      //cout<<minI<<"\t"<<minJ<<"\t"<<minBL<<endl;
      if(minI>minJ) swap(minI,minJ);
      for(unsigned int u=0;u<Nc;++u)
        if(gstate[u]==minI) {
          iND=&(nd[u]);
          while(iND->parent!=NULL) { iND=iND->parent; }
        }
      for(unsigned int u=0;u<Nc;++u)
        if(gstate[u]==minJ) {
          jND=&(nd[u]);
          while(jND->parent!=NULL) { jND=jND->parent; }
        }
      iND->nowflag=false;
      jND->nowflag=false;
      ss=new stringstream;
      if(iND->left!=NULL)
        (*ss)<<":"<<minBL-iND->left->dist;
      else
        (*ss)<<":"<<minBL;
      iND->name+=ss->str();
      delete ss;
      ss=new stringstream;
      if(jND->left!=NULL)
        (*ss)<<":"<<minBL-jND->left->dist;
      else
        (*ss)<<":"<<minBL;
      jND->name+=ss->str();
      delete ss;
      iND->dist=minBL;
      jND->dist=minBL;
      iND->parent=&(nd[NowNode]);
      jND->parent=&(nd[NowNode]);
      nd[NowNode].left=iND;
      nd[NowNode].right=jND;
      nd[NowNode].parent=NULL;
      nd[NowNode].dist=-1;
      nd[NowNode].gID=minI;
      nd[NowNode].nowflag=true;
      nd[NowNode].name="("+iND->name+","+jND->name+")";
      NowNode++;
      for(unsigned int u=0;u<Nc;++u)
        if(gstate[u]==minJ) { gstate[u]=minI; }
    }
  } while(minop>0);
  cout<<nd[NowNode-1].name<<endl;
  return 0;
}

