#include "GCShadingGroup.h"
#include "spropertyinformationhelpers.h"
#include "XGeometry.h"
#include "XModeller.h"
#include "XRenderer.h"
#include "3D/Manipulators/GCButtonManipulator.h"
#include "sprocessmanager.h"

S_IMPLEMENT_TYPED_POINTER_TYPE(GCShadingGroupPointer, GraphicsCore)
S_IMPLEMENT_TYPED_POINTER_ARRAY_TYPE(GCShadingGroupPointerArray, GraphicsCore)

S_IMPLEMENT_PROPERTY(GCShadingGroup, GraphicsCore)

void GCShadingGroup::createTypeInformation(PropertyInformationTyped<GCShadingGroup> *info,
                                           const PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->add(&GCShadingGroup::shader, "shader");
    }

  if(data.registerInterfaces)
    {
    info->addInheritedInterface<GCManipulatable>();
    }
  }

GCShadingGroup::GCShadingGroup()
  {
  }

void GCShadingGroup::render(XRenderer *r) const
  {
  const GCStaticShader *s = shader.pointed();
  if(s)
    {
    s->bind(r);
    }

  GCRenderArray::render(r);
  }

void GCShadingGroup::addManipulators(PropertyArray *, const GCTransform *)
  {/*
  xAssert(tr == 0);
  //a->add<GCButtonManipulator>();

  // todo, probably dont do this...!
  for(GCGeometryTransformPointer* geoPtr = geometry.firstChild<GCGeometryTransformPointer>(); geoPtr; geoPtr = geoPtr->nextSibling<GCGeometryTransformPointer>())
    {
    GCGeometryTransform* geo = geoPtr->pointed();
    if(geo)
      {
      geo->addManipulators(a);
      }
    }*/
  }
