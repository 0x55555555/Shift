#include "GCRenderable.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

S_IMPLEMENT_TYPED_POINTER_TYPE(GCRenderablePointer, GraphicsCore)
S_IMPLEMENT_TYPED_POINTER_TYPE(GCRenderArrayPointer, GraphicsCore)
S_IMPLEMENT_TYPED_POINTER_ARRAY_TYPE(GCRenderablePointerArray, GraphicsCore)

S_IMPLEMENT_PROPERTY(GCRenderable, GraphicsCore)

void GCRenderable::createTypeInformation(Shift::PropertyInformationTyped<GCRenderable> *info,
                                         const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->add(data, &GCRenderable::bounds, "bounds");
    }
  }

GCRenderable::GCRenderable()
  {
  }

void GCRenderable::intersect(const Eks::Line &, Selector *)
  {
  }

void GCRenderable::intersect(const Eks::Frustum &, Selector *)
  {
  }


S_IMPLEMENT_PROPERTY(GCRenderArray, GraphicsCore)

void unionBounds(GCRenderArray* array)
  {
  GCBoundingBox::ComputeLock l(&array->bounds);
  Eks::Cuboid *data = l.data();
  *data = Eks::Cuboid();

  xForeach(auto r, array->renderGroup.walker<GCRenderablePointer>())
    {
    const GCRenderable* ptd = r->pointed();

    data->unite(ptd->bounds());
    }
  }

void GCRenderArray::createTypeInformation(Shift::PropertyInformationTyped<GCRenderArray> *info,
                                          const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto rGInst = info->add(data, &GCRenderArray::renderGroup, "renderGroup");

    auto bInst = info->child(&GCRenderArray::bounds);
    bInst->setCompute<unionBounds>();

    rGInst->setAffects(data, bInst);
    }
  }

void GCRenderArray::render(Eks::Renderer *renderer) const
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

void GCRenderArray::intersect(const Eks::Line &line, Selector *s)
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

void GCRenderArray::intersect(const Eks::Frustum &frus, Selector *s)
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
