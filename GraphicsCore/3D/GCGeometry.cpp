#include "GCGeometry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sbaseproperties.inl"
#include "shift/TypeInformation/styperegistry.h"

S_IMPLEMENT_PROPERTY(GCGeometry, GraphicsCore)

void GCGeometry::createTypeInformation(Shift::PropertyInformationTyped<GCGeometry> *info,
                                       const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    childBlock.add(&GCGeometry::runtimeGeometry, "runtimeGeometry");
    }
  }

S_IMPLEMENT_PROPERTY(GCIndexedGeometry, GraphicsCore)

void GCIndexedGeometry::createTypeInformation(Shift::PropertyInformationTyped<GCIndexedGeometry> *info,
                                       const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);
    childBlock.add(&GCIndexedGeometry::runtimeIndexGeometry, "runtimeIndexGeometry");
    }
  }
