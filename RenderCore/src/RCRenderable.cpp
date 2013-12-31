#include "RCRenderable.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/scontainer.inl"
#include "shift/Properties/sdata.inl"

S_IMPLEMENT_TYPED_POINTER_TYPE(RCRenderablePointer, RenderCore)
S_IMPLEMENT_TYPED_POINTER_TYPE(RCRenderArrayPointer, RenderCore)
S_IMPLEMENT_TYPED_POINTER_ARRAY_TYPE(RCRenderablePointerArray, RenderCore)

S_IMPLEMENT_PROPERTY(RCRenderable, RenderCore)

void RCRenderable::createTypeInformation(Shift::PropertyInformationTyped<RCRenderable> *info,
                                         const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    childBlock.add(&RCRenderable::bounds, "bounds");
    }
  }

RCRenderable::RCRenderable()
  {
  }

void RCRenderable::intersect(const Eks::Line &, Selector *)
  {
  }

void RCRenderable::intersect(const Eks::Frustum &, Selector *)
  {
  }


S_IMPLEMENT_PROPERTY(RCRenderArray, RenderCore)

void unionBounds(RCRenderArray* array)
  {
  auto lock = array->bounds.computeLock();
  lock = Eks::BoundingBox();

  xForeach(auto r, array->renderGroup.walker<RCRenderablePointer>())
    {
    const RCRenderable* ptd = r->pointed();

    if(ptd)
      {
      lock->unite(ptd->bounds());
      }
    }
  }

void RCRenderArray::createTypeInformation(Shift::PropertyInformationTyped<RCRenderArray> *info,
                                          const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto rGInst = childBlock.add(&RCRenderArray::renderGroup, "renderGroup");

    auto bInst = childBlock.overrideChild(&RCRenderArray::bounds);
    bInst->setCompute<unionBounds>();

    rGInst->setAffects(data, bInst);
    }
  }

void RCRenderArray::render(Eks::Renderer *renderer, const RenderState &state) const
  {
  X_EVENT_FUNCTION;

  xForeach(auto r, renderGroup.walker<RCRenderablePointer>())
    {
    const RCRenderable* ptd = r->pointed();
    if(!ptd)
      {
      qWarning() << "Null renderable";
      continue;
      }
    
    ptd->render(renderer, state);
    }
  }

void RCRenderArray::intersect(const Eks::Line &line, Selector *s)
  {
  xForeach(auto r, renderGroup.walker<RCRenderablePointer>())
    {
    RCRenderable* ptd = r->pointed();
    if(ptd)
      {
      ptd->intersect(line, s);
      }
    }
  }

void RCRenderArray::intersect(const Eks::Frustum &frus, Selector *s)
  {
  xForeach(auto r, renderGroup.walker<RCRenderablePointer>())
    {
    RCRenderable* ptd = r->pointed();
    if(ptd)
      {
      ptd->intersect(frus, s);
      }
    }
  }
