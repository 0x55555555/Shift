#include "GAPlotPoint.h"
#include "spropertyinformationhelpers.h"
#include "GAGlobal.h"

namespace GameCore
{

void computeCanComplete(PlotPoint *pt)
  {
  bool canComplete = true;
  xForeach(const PlotCondition *dep, pt->dependencies.typed<PlotCondition>())
    {
    if(!dep->complete())
      {
      canComplete = false;
      break;
      }
    }
  pt->canComplete = canComplete;
  }

S_IMPLEMENT_PROPERTY(PlotPoint, GameCore)

void PlotPoint::createTypeInformation(SPropertyInformationTyped<PlotPoint> *info,
                                      const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto canCompleteInst = info->add(&PlotPoint::canComplete, "canComplete");
    canCompleteInst->setCompute<computeCanComplete>();

    auto depInst = info->add(&PlotPoint::dependencies, "dependencies");
    depInst->setAffects(canCompleteInst);

    info->add(&PlotPoint::conditions, "conditions");
    }

  if(data.registerInterfaces)
    {
    auto ifc = info->apiInterface();

    ifc->addMethod<void(), &PlotPoint::tryToComplete>("tryToComplete");
    }
  }


bool PlotPoint::conditionsComplete() const
  {
  xForeach(const PlotCondition *dep, conditions.typed<PlotCondition>())
    {
    if(!dep->complete())
      {
      return false;
      }
    }
  return true;
  }

void PlotPoint::tryToComplete()
  {
  if(!complete() && canComplete())
    {
    complete = conditionsComplete();
    }
  }
}
