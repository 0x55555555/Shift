#include "RCGeometry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sdata.inl"
#include "shift/Properties/scontainer.inl"
#include "shift/TypeInformation/styperegistry.h"

S_IMPLEMENT_PROPERTY(RCGeometry, RenderCore)

void RCGeometry::createTypeInformation(Shift::PropertyInformationTyped<RCGeometry> *info,
                                       const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);

  childBlock.add(&RCGeometry::runtimeGeometry, "runtimeGeometry");
  }

S_IMPLEMENT_PROPERTY(RCIndexedGeometry, RenderCore)

void RCIndexedGeometry::createTypeInformation(Shift::PropertyInformationTyped<RCIndexedGeometry> *info,
                                       const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);
  childBlock.add(&RCIndexedGeometry::runtimeIndexGeometry, "runtimeIndexGeometry");
  }
