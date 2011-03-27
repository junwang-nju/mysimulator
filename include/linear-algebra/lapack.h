
#ifndef _LinearAlgebra_LAPACK_H_
#define _LinearAlgebra_LAPACK_H_

extern "C" {

  void dgeqrf_(int*,int*,double*,int*,double*,double*,int*,int*);
  void dsyevd_(char*,char*,int*,double*,int*,double*,double*,int*,
               int*,int*,int*);
  void dspevd_(char*,char*,int*,double*,double*,double*,int*,double*,int*,
               int*,int*,int*);

  void sgeqrf_(int*,int*,float*,int*,float*,float*,int*,int*);
  void ssyevd_(char*,char*,int*,float*,int*,float*,float*,int*,
               int*,int*,int*);
  void sspevd_(char*,char*,int*,float*,float*,float*,int*,float*,int*,
               int*,int*,int*);

}

#endif

