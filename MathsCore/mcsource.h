#ifndef MCSOURCE_H
#define MCSOURCE_H

#include "shift/sentity.h"
#include "mcmathsoperation.h"

class MATHSCORE_EXPORT MCSource : public Shift::Entity
  {
  S_ENTITY(MCSource, Shift::Entity, 0);

public:
  MCSource();

  MCMathsOperation output;
  };

S_PROPERTY_INTERFACE(MCSource)

#endif // MCSOURCE_H
