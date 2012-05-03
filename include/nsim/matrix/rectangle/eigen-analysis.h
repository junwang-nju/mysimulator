
#ifndef _Matrix_Rectangle_EigenAnalysis_H_
#define _Matrix_Rectangle_EigenAnalysis_H_

#include "matrix/rectangle/interface.h"
#include "linear-algebra/lapack.h"

namespace mysimulator {

  template <typename T>
  void EigenValue(MatrixRectangle<T>& M, Array1D<T>& EV,Array1D<T>& TMP,
                  Array1D<int>& ITMP) {
    char Fg[]="NU";
    int INF;
    int n=(M.NumRows>=M.NumColumns?M.NumColumns:M.NumRows), l=M.NumColumns;
    int nw=TMP.Size(), niw=ITMP.Size();
    assert(nw>=2*n+1);
    assert(niw>=1);
    LAPACK<T>::SyEVD(Fg,Fg+1,&n,M._ldata._data,&l,EV._data,TMP._data,&nw,
                     ITMP._data,&niw,&INF);
  }

  template <typename T>
  void Eigen(MatrixRectangle<T>& M, Array1D<T>& EV,Array1D<T>& TMP,
             Array1D<int>& ITMP) {
    char Fg[]="VU";
    int INF;
    int n=(M.NumRows>=M.NumColumns?M.NumColumns:M.NumRows), l=M.NumColumns;
    int nw=TMP.Size(), niw=ITMP.Size();
    assert(nw>=2*n*n+6*n+1);
    assert(niw>=3+5*n);
    LAPACK<T>::SyEVD(Fg,Fg+1,&n,M._ldata._data,&l,EV._data,TMP._data,&nw,
                     ITMP._data,&niw,&INF);
  }

}

#endif

