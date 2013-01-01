#include "mcsource.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(MCSource, MathsCore)

void MCSource::createTypeInformation(Shift::PropertyInformationTyped<MCSource> *info,
                                     const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->add(&MCSource::output, "output");
    }
  }

MCSource::MCSource()
  {
  }
