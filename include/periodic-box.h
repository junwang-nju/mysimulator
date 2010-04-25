
#ifndef _Periodic_Box_H_
#define _Periodic_Box_H_

#include "geometry-id.h"
#include "displacement-direct.h"

namespace std {

  struct PeriodicBox;

  void assign(PeriodicBox&, const PeriodicBox&);
  void release(PeriodicBox&);

  enum PeriodicStateName {
    HavePeriodic=1,
    NoPeriodic=0
  };

  struct PeriodicBox {

    static const unsigned int TypeID;

    double* box;
    double* halfbox;
    unsigned int* edgeflag;
    unsigned int size;
    unsigned int state;

    typedef PeriodicBox Type;

    PeriodicBox()
      : box(NULL), halfbox(NULL), edgeflag(NULL), size(0), state(Unused) {}
    PeriodicBox(const Type&) { myError("Cannot create from Periodic Box"); }
    Type& operator=(const Type& PB) { assign(*this,PB); return *this; }
    ~PeriodicBox() { release(*this); }

  };

  const unsigned int PeriodicBox::TypeID=PeriodicBoxType;

  bool IsAvailable(const PeriodicBox& PB) { return IsAvailable(PB.box); }

  void release(PeriodicBox& PB) {
    if(PB.state==Allocated) {
      safe_delete_array(PB.box);
      safe_delete_array(PB.halfbox);
      safe_delete_array(PB.edgeflag);
    } else {
      PB.box=NULL;
      PB.halfbox=NULL;
      PB.edgeflag=NULL;
    }
    PB.size=0;
    PB.state=Unused;
  }

  void assign(PeriodicBox& dest, const PeriodicBox& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    unsigned int n=(dest.size<src.size?dest.size:src.size);
    assign(dest.box,src.box,n);
    assign(dest.halfbox,src.halfbox,n);
    assign(dest.edgeflag,src.edgeflag,n);
  }

  void allocate(PeriodicBox& PB,const unsigned int dim) {
    release(PB);
    PB.box=new double[dim];
    PB.halfbox=new double[dim];
    PB.edgeflag=new unsigned int[dim];
    PB.size=dim;
    PB.state=Allocated;
  }

  void refer(PeriodicBox& dest, const PeriodicBox& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.box=src.box;
    dest.halfbox=src.halfbox;
    dest.edgeflag=src.edgeflag;
    dest.size=src.size;
    dest.state=Reference;
  }

  void update(PeriodicBox& PB) {
    assert(IsAvailable(PB));
    assign(PB.halfbox,PB.box,PB.size);
    scale(PB.halfbox,0.5,PB.size);
  }

  void set(PeriodicBox& PB,
           const double* box, const unsigned int* flag, const unsigned int m,
           const int boff=iZero, const long bstep=lOne,
           const int foff=iZero, const long fstep=lOne) {
    assert(IsAvailable(PB));
    assert(IsAvailable(box));
    assert(IsAvailable(flag));
    unsigned int n=(m<PB.size?m:PB.size);
    assign(PB.box,box,n,boff,bstep);
    assign(PB.edgeflag,flag,n,foff,fstep);
    update(PB);
  }

  void set(PeriodicBox& PB,
           const Vector<double>& box, const Vector<unsigned int>& flag) {
    unsigned int m=(box.size<flag.size?box.size:flag.size);
    set(PB,box(),flag(),m);
  }

  void set(PeriodicBox& PB,
           const double* box, const unsigned int m,
           const unsigned int fg=HavePeriodic,
           const int boff=iZero, const long bstep=lOne) {
    assert(IsAvailable(PB));
    assert(IsAvailable(box));
    unsigned int n=(m<PB.size?m:PB.size);
    assign(PB.box,box,n,boff,bstep);
    assign(PB.edgeflag,fg,n);
    update(PB);
  }

  void set(PeriodicBox& PB,
           const Vector<double>& box, const unsigned int fg=HavePeriodic) {
    set(PB,box(),box.size,fg);
  }

  void Compress2MainRegion(const PeriodicBox& PB, double* v,
                           const unsigned int vdim,
                           const unsigned int voff=uZero,
                           const unsigned int vstep=uOne) {
    assert(IsAvailable(PB));
    assert(IsAvailable(v));
    double bmd, bhd;
    unsigned int n=(PB.size<vdim?PB.size:vdim);
    double *pv=v+voff;
    for(unsigned int i=0;i<n;++i,pv+=vstep) {
      bhd=PB.halfbox[i];
      bmd=PB.box[i];
      while(*pv<-bhd) *pv+=bmd;
      while(*pv>=bhd) *pv-=bmd;
    }
  }

  void Compress2MainRegion(const PeriodicBox& PB, Vector<double>& v) {
    Compress2MainRegion(PB,v(),v.size);
  }

  void DisplacementFunc(const double* va, const double* vb,
                        const unsigned int dim, double* Dsp,
                        const PeriodicBox& PB,
                        const int aoff=iZero, const long astep=lOne,
                        const int boff=iZero, const long bstep=lOne,
                        const int doff=iZero, const long dstep=lOne) {
    unsigned int n=(dim<PB.size?dim:PB.size);
    DisplacementFunc(va,vb,n,Dsp,aoff,astep,boff,bstep,doff,dstep);
    Compress2MainRegion(PB,Dsp,n,doff,dstep);
  }

  void DisplacementFunc(const Vector<double>& va, const Vector<double>& vb,
                        Vector<double>& Dsp, const PeriodicBox& PB) {
    unsigned int m;
    m=(va.size<vb.size?va.size:vb.size);
    m=(m<Dsp.size?m:Dsp.size);
    DisplacementFunc(va(),vb(),m,Dsp(),PB);
  }

}

#endif

