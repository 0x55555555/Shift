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
    auto childBlock = info->createChildrenBlock(data);

    childBlock.add(&GCShadingGroup::shader, "shader");
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

  (void)state;
  r->setTransform(Eks::Transform::Identity());

  if (!_geo.isValid())
    {
    float pos[] =
    {
      1000, 0, 0,  1, 1, 1,  0, 0,
      0, 1000, 0,  1, 1, 1,  0, 0,
      0,    0, 0,  1, 1, 1,  0, 0
    };

    Eks::Geometry::delayedCreate(const_cast<Eks::Geometry&>(_geo), r, pos, sizeof(float) * 8, 3);
    }

  r->drawTriangles(&_geo);
  //GCRenderArray::render(r, state);
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
