#include "GCShadingGroup.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "XGeometry.h"
#include "XModeller.h"
#include "XRenderer.h"
#include "3D/Manipulators/GCButtonManipulator.h"

S_IMPLEMENT_TYPED_POINTER_TYPE(GCShadingGroupPointer, GraphicsCore)
S_IMPLEMENT_TYPED_POINTER_ARRAY_TYPE(GCShadingGroupPointerArray, GraphicsCore)

S_IMPLEMENT_PROPERTY(GCShadingGroup, GraphicsCore)

void GCShadingGroup::createTypeInformation(Shift::PropertyInformationTyped<GCShadingGroup> *info,
                                           const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->add(data, &GCShadingGroup::shader, "shader");
    }
  }

GCShadingGroup::GCShadingGroup()
  {
  }

void GCShadingGroup::render(Eks::Renderer *r, const RenderState &state) const
  {
  const GCShader *s = shader.pointed();
  if(s)
    {
    s->bind(r);
    }

  GCRenderArray::render(r, state);
  }

void GCShadingGroup::addManipulators(Shift::PropertyArray *, const GCTransform *)
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
