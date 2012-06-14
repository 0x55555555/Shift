#ifndef GAPLOTPOINT_H
#define GAPLOTPOINT_H

#include "GAPlotCondition.h"

namespace GameCore
{

class PlotPoint : public PlotCondition
  {
  S_ENTITY(PlotPoint, PlotCondition, 0)

public:

  // the dependent points for this point to be available
  SPropertyArray dependencies;

  // the conditions for this point to be complete
  SPropertyArray conditions;

  // are all the depencies actually complete
  BoolProperty canComplete;

  bool conditionsComplete() const;
  void tryToComplete();
  };

}

S_PROPERTY_INTERFACE(GameCore::PlotPoint)


#endif // GAPLOTPOINT_H
