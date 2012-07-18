#ifndef MCSIMPLEADD_H
#define MCSIMPLEADD_H

#include "mcsimple.h"
#include "sbaseproperties.h"

class MATHSCORE_EXPORT MCSimpleAdd : public MCSimple
  {
  S_ENTITY(MCSimpleAdd, MCSimple, 0)

public:
  MCSimpleAdd();
  };

S_PROPERTY_INTERFACE(MCSimpleAdd)

#endif // MCSIMPLEADD_H
