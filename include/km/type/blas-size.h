
#ifndef _Type_BlasSize_H_
#define _Type_BlasSize_H_

namespace mysimulator {

  template <typename T>
  class BlasSizeState { public: static const unsigned int State; };

  template <typename T>
  const unsigned int BlasSizeState<T>::State=
    (sizeof(T)==sizeof(double)?1:
    (sizeof(T)==sizeof(float)?2:0));

  template <unsigned int State>
  class BlasSizeProduce {};

  template <> class BlasSizeProduce<1> {  public: typedef double Type;  };
  template <> class BlasSizeProduce<2> {  public: typedef float Type;  };

  template <typename T>
  class BlasSize {
    public:
      typedef typename BlasSizeProduce<BlasSizeState<T>::State>::Type Type;
  };

}

#endif

