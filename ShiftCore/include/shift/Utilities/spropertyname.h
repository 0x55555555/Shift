#ifndef SPROPERTYNAME_H
#define SPROPERTYNAME_H

#include "shift/sglobal.h"
#include "Containers/XStringSimple.h"
#include "Utilities/XStringRef.h"

namespace Shift
{

enum
  {
  NamePreallocSize = 32
  };

typedef Eks::StringBase<Eks::Char, NamePreallocSize> Name;

class SHIFT_EXPORT NameArg : public Eks::StringRef
  {
public:
  NameArg() { }

  NameArg(NameArg &&n)
    : StringRef(std::move(n))
    {
    }

#if X_QT_INTEROP
  NameArg(const QString &);
#endif

  template <typename C, xsize S, typename A>
  NameArg(const Eks::StringBase<C, S, A> &in)
      : StringRef(in)
    {
    }

  NameArg(const Eks::Char *in)
      : StringRef(in)
    {
    }

  void toName(Name &out) const
    {
    toString(out);
    }
  };

}

#endif // SPROPERTYNAME_H
