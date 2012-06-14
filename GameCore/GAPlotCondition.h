#ifndef GAPLOTCONDITION_H
#define GAPLOTCONDITION_H

#include "spropertycontainer.h"
#include "sbaseproperties.h"

namespace GameCore
{

class PlotCondition : public SEntity
  {
  S_PROPERTY_CONTAINER(PlotCondition, SEntity, 0)

public:
  // has the point been completed
  BoolProperty complete;
  };

}

S_PROPERTY_INTERFACE(GameCore::PlotCondition)

#endif // GAPLOTCONDITION_H
