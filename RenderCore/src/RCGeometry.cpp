#include "RCGeometry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sdata.inl"
#include "shift/TypeInformation/styperegistry.h"

S_IMPLEMENT_PROPERTY(RCGeometry, RenderCore)

void RCGeometry::createTypeInformation(Shift::PropertyInformationTyped<RCGeometry> *info,
                                       const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    childBlock.add(&RCGeometry::runtimeGeometry, "runtimeGeometry");
    }
  }

S_IMPLEMENT_PROPERTY(RCIndexedGeometry, RenderCore)

void RCIndexedGeometry::createTypeInformation(Shift::PropertyInformationTyped<RCIndexedGeometry> *info,
                                       const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);
    childBlock.add(&RCIndexedGeometry::runtimeIndexGeometry, "runtimeIndexGeometry");
    }
  }
