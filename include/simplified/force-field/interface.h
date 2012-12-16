
#ifndef _Force_Field_Interface_H_
#define _Force_Field_Interface_H_

#include "force-field/name.h"
#include "basic/memory/deleter.h"

namespace mysimulator {

  class ForceField {

    public:

      typedef ForceField    Type;

    private:

      ForceFieldName  _tag;
      char* _content;

    public:

      ForceField() : _tag(ForceFieldName::Unknown), _content(nullptr) {}
      ~ForceField() { reset(); }

      ForceFieldName Name() const { return _tag; }
      const char* Configuration() const { return _content; }
      void reset() {
        _tag=ForceFieldName::Unknown;
        __delete_array<char>(_content);
      }

  };

}

#endif

