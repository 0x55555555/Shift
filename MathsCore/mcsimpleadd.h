#ifndef MCSIMPLEADD_H
#define MCSIMPLEADD_H

#include "mcsimple.h"
#include "shift/Properties/sbaseproperties.h"

class MATHSCORE_EXPORT MCSimpleAdd : public MCSimple
  {
  S_ENTITY(MCSimpleAdd, MCSimple, 0)
  };

class MATHSCORE_EXPORT MCSimpleSubtract : public MCSimple
  {
  S_ENTITY(MCSimpleSubtract, MCSimple, 0)
  };

S_PROPERTY_INTERFACE(MCSimpleAdd)
S_PROPERTY_INTERFACE(MCSimpleSubtract)

#endif // MCSIMPLEADD_H
