#ifndef MCSIMPLE_H
#define MCSIMPLE_H

#include "mcglobal.h"
#include "sentity.h"
#include "sbaseproperties.h"

class MATHSCORE_EXPORT MCSimple : public Entity
  {
  S_ENTITY(MCSimple, Entity, 0)

public:
  MCSimple();

  FloatProperty inputA;
  FloatProperty inputB;

  FloatProperty output;
  };

S_PROPERTY_INTERFACE(MCSimple)

#endif // MCSIMPLE_H
