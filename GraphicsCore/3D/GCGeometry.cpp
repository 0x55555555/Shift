#include "GCGeometry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/TypeInformation/styperegistry.h"

S_IMPLEMENT_PROPERTY(GCGeometry, GraphicsCore)

void GCGeometry::createTypeInformation(Shift::PropertyInformationTyped<GCGeometry> *info,
                                       const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->add(data, &GCGeometry::runtimeGeometry, "runtimeGeometry");
    }
  }

GCGeometry::GCGeometry()
  {
  }

S_IMPLEMENT_TYPED_POINTER_TYPE(GCGeometryPointer, GraphicsCore)
