#ifndef MCSIMPLEMULTIPLY_H
#define MCSIMPLEMULTIPLY_H

#include "mcsimple.h"
#include "sbaseproperties.h"

class MATHSCORE_EXPORT MCSimpleMultiply : public MCSimple
  {
  S_ENTITY(MCSimpleMultiply, MCSimple, 0)

public:
  MCSimpleMultiply();
  };

S_PROPERTY_INTERFACE(MCSimpleMultiply)

#endif // MCSIMPLEMULTIPLY_H
