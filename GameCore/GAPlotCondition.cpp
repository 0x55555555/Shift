#include "GAPlotCondition.h"
#include "spropertyinformationhelpers.h"
#include "GAGlobal.h"

namespace GameCore
{

S_IMPLEMENT_PROPERTY(PlotCondition, GameCore)

void PlotCondition::createTypeInformation(SPropertyInformationTyped<PlotCondition> *info,
                                      const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->add(&PlotCondition::complete, "complete");
    }
  }

}
