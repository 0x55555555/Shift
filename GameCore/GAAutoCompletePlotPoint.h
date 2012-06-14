#ifndef GAAUTOCOMPLETEPLOTPOINT_H
#define GAAUTOCOMPLETEPLOTPOINT_H

#include "GAPlotPoint.h"

namespace GameCore
{

// automatically completes when all input conditions are complete
class AutoCompletePlotPoint : public PlotPoint
  {
  S_PROPERTY_CONTAINER(AutoCompletePlotPoint, PlotPoint, 0)

public:
  };

}

S_PROPERTY_INTERFACE(GameCore::AutoCompletePlotPoint)

#endif // GAAUTOCOMPLETEPLOTPOINT_H
