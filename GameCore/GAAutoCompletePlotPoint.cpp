#include "GAAutoCompletePlotPoint.h"
#include "spropertyinformationhelpers.h"
#include "GAGlobal.h"

namespace GameCore
{

S_IMPLEMENT_PROPERTY(AutoCompletePlotPoint, GameCore)

void computeComplete(AutoCompletePlotPoint *i)
  {
  bool complete = true;

  // depends on itself in compute, this is probably not too good?
  if(!i->complete())
    {
    if(!i->canComplete() || !i->conditionsComplete())
      {
      complete = false;
      }
    }

  i->complete = complete;
  }

void AutoCompletePlotPoint::createTypeInformation(SPropertyInformationTyped<AutoCompletePlotPoint> *info,
                                                  const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto completeInst = info->child(&AutoCompletePlotPoint::complete);
    completeInst->setCompute<computeComplete>();

    auto condtionsInst = info->child(&AutoCompletePlotPoint::conditions);
    condtionsInst->setAffects(completeInst);

    auto canCompleteInst = info->child(&PlotPoint::canComplete);
    canCompleteInst->setAffects(completeInst);
    }
  }

}
