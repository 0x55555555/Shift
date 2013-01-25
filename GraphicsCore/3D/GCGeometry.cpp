#include "GCGeometry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/TypeInformation/styperegistry.h"

S_IMPLEMENT_PROPERTY(GCGeometry, GraphicsCore)

void GCGeometry::createTypeInformation(Shift::PropertyInformationTyped<GCGeometry> *info,
                                       const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    childBlock.add(&GCGeometry::runtimeGeometry, "runtimeGeometry");
    childBlock.add(&GCGeometry::runtimeIndexGeometry, "runtimeIndexGeometry");
    }
  }

S_IMPLEMENT_TYPED_POINTER_TYPE(GCGeometryPointer, GraphicsCore)
