#include "GCRenderable.h"
#include "spropertyinformationhelpers.h"

S_IMPLEMENT_TYPED_POINTER_TYPE(GCRenderablePointer, GraphicsCore)
S_IMPLEMENT_TYPED_POINTER_TYPE(GCRenderArrayPointer, GraphicsCore)
S_IMPLEMENT_TYPED_POINTER_ARRAY_TYPE(GCRenderablePointerArray, GraphicsCore)

S_IMPLEMENT_PROPERTY(GCRenderable, GraphicsCore)

void GCRenderable::createTypeInformation(PropertyInformationTyped<GCRenderable> *info,
                                         const PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->add(&GCRenderable::bounds, "bounds");
    }
  }

GCRenderable::GCRenderable()
  {
  }

void GCRenderable::intersect(const XLine &, Selector *)
  {
  }

void GCRenderable::intersect(const XFrustum &, Selector *)
  {
  }


S_IMPLEMENT_PROPERTY(GCRenderArray, GraphicsCore)

void unionBounds(GCRenderArray* array)
  {
  GCBoundingBox::ComputeLock l(&array->bounds);
  XCuboid *data = l.data();
  *data = XCuboid();

  xForeach(auto r, array->renderGroup.walker<GCRenderablePointer>())
    {
    const GCRenderable* ptd = r->pointed();

    data->unite(ptd->bounds());
    }
  }

void GCRenderArray::createTypeInformation(PropertyInformationTyped<GCRenderArray> *info,
                                          const PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto rGInst = info->add(&GCRenderArray::renderGroup, "renderGroup");

    auto bInst = info->child(&GCRenderArray::bounds);
    bInst->setCompute<unionBounds>();

    rGInst->setAffects(bInst);
    }
  }

GCRenderArray::GCRenderArray()
  {
  }

void GCRenderArray::render(XRenderer *renderer) const
  {
  xForeach(auto r, renderGroup.walker<GCRenderablePointer>())
    {
    const GCRenderable* ptd = r->pointed();
    if(!ptd)
      {
      qWarning() << "Null renderable";
      continue;
      }
    
    ptd->render(renderer);
    }
  }

void GCRenderArray::intersect(const XLine &line, Selector *s)
  {
  xForeach(auto r, renderGroup.walker<GCRenderablePointer>())
    {
    GCRenderable* ptd = r->pointed();
    if(ptd)
      {
      ptd->intersect(line, s);
      }
    }
  }

void GCRenderArray::intersect(const XFrustum &frus, Selector *s)
  {
  xForeach(auto r, renderGroup.walker<GCRenderablePointer>())
    {
    GCRenderable* ptd = r->pointed();
    if(ptd)
      {
      ptd->intersect(frus, s);
      }
    }
  }
