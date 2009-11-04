
#ifndef _Geometry_H_
#define _Geometry_H_

namespace std {

  enum GeometryType {

    FreeSpaceType

  };

  class FreeSpace {
  
    public:

      static const uint Type=FreeSpaceType;
      
      FreeSpace() {}
      
      FreeSpace(const FreeSpace& FS) {
        myError("Copier for FreeSpace is disabled");
      }

      FreeSpace& operator=(const FreeSpace& FS) { return *this; }

      FreeSpace& Duplicate(const FreeSpace& FS) { return *this; }
    
  };

}

#endif
