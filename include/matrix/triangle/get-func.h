
#ifndef _Matrix_Triangle_Get_Function_H_
#define _Matrix_Triangle_Get_Function_H_

#include "vector/interface.h"

namespace mysimulator {

  template <typename T>
  T& MatrixTri_Get4CUSD(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I<J?s[I][J-I]:s[J][I-J];
  }

  template <typename T>
  T& MatrixTri_Get4CUSN(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I==J?*OE:(I<J?s[I][J-I-1]:s[J][I-J-1]);
  }

  template <typename T>
  T& MatrixTri_Get4CUAD(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I>J?*OE:s[I][J-I];
  }

  template <typename T>
  T& MatrixTri_Get4CUAN(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I>=J?*OE:s[I][J-I-1];
  }

  template <typename T>
  T& MatrixTri_Get4CLSD(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I>J?s[I][J]:s[J][I];
  }

  template <typename T>
  T& MatrixTri_Get4CLSN(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I==J?*OE:(I>J?s[I-1][J]:s[J-1][I]);
  }

  template <typename T>
  T& MatrixTri_Get4CLAD(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I<J?*OE:s[I][J];
  }

  template <typename T>
  T& MatrixTri_Get4CLAN(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I<=J?*OE:s[I-1][J];
  }

  template <typename T>
  T& MatrixTri_Get4FUSD(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I<J?s[J-1][I]:s[I-1][J];
  }

  template <typename T>
  T& MatrixTri_Get4FUSN(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I==J?*OE:(I<J?s[J-1][I]:s[I-1][J]);
  }

  template <typename T>
  T& MatrixTri_Get4FUAD(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I>J?*OE:s[J][I];
  }

  template <typename T>
  T& MatrixTri_Get4FUAN(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I>=J?*OE:s[J-1][I];
  }

  template <typename T>
  T& MatrixTri_Get4FLSD(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I>J?s[J][I-J]:s[I][J-I];
  }

  template <typename T>
  T& MatrixTri_Get4FLSN(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I==J?*OE:(I>J?s[J][I-J-1]:s[I][J-I-1]);
  }

  template <typename T>
  T& MatrixTri_Get4FLAD(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I<J?*OE:s[J][I-J];
  }

  template <typename T>
  T& MatrixTri_Get4FLAN(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I<=J?*OE:s[J][I-J-1];
  }

  template <typename T>
  T& MatrixTri_Get4DUSD(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I<J?s[J-I][I]:s[I-J][J];
  }

  template <typename T>
  T& MatrixTri_Get4DUSN(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I==J?*OE:(I<J?s[J-I-1][I]:s[I-J-1][J]);
  }

  template <typename T>
  T& MatrixTri_Get4DUAD(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I>J?*OE:s[J-I][I];
  }

  template <typename T>
  T& MatrixTri_Get4DUAN(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I>=J?*OE:s[J-I-1][I];
  }

  template <typename T>
  T& MatrixTri_Get4DLSD(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I<J?s[J-I][I]:s[I-J][J];
  }

  template <typename T>
  T& MatrixTri_Get4DLSN(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I==J?*OE:(I<J?s[J-I-1][I]:s[I-J-1][J]);
  }

  template <typename T>
  T& MatrixTri_Get4DLAD(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I<J?*OE:s[I-J][J];
  }

  template <typename T>
  T& MatrixTri_Get4DLAN(Vector<Vector<T> >& s,
                        const unsigned int I, const unsigned int J,
                        T* const& OE) {
    return I<=J?*OE:s[I-J-1][J];
  }

}

#endif

