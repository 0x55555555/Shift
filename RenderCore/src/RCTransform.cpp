#include "RCTransform.h"
#include "shift/TypeInformation/styperegistry.h"
#include "shift/sdatabase.h"
#include "XLine.h"
#include "XFrustum.h"
#include "XRenderer.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Changes/shandler.inl"
#include "shift/Properties/sdata.inl"

void unionTransformedBounds(RCTransform* tr)
  {
  auto lock = tr->bounds.computeLock();
  lock = Eks::BoundingBox();

  xForeach(auto r, tr->renderGroup.walker<RCRenderablePointer>())
    {
    const RCRenderable* ptd = r->pointed();

    lock->unite(ptd->bounds());
    }

  lock = tr->transform() * lock;
  }

S_IMPLEMENT_PROPERTY(RCTransform, RenderCore)

void RCTransform::createTypeInformation(Shift::PropertyInformationTyped<RCTransform> *info,
                                        const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto boundsInfo = childBlock.overrideChild(&RCTransform::bounds);
    boundsInfo->setCompute<unionTransformedBounds>();

    auto trInfo = childBlock.add(&RCTransform::transform, "transform");
    trInfo->setDefault(Eks::Transform::Identity());
    trInfo->setAffects(data, boundsInfo);
    }
  }

void RCTransform::render(Eks::Renderer *r, const RenderState &state) const
  {
  RenderState s = state;
  s.transform *= transform().matrix();

  r->setTransform(s.transform);

  RCRenderArray::render(r, s);
  }

class InternalSelector : public RCRenderable::Selector
  {
public:
  InternalSelector(const Eks::Transform &tr, Selector *parent)
      : _parent(parent), _transform(tr)
    {
    }

  void onHit(const Eks::Vector3D &point, const Eks::Vector3D &normal, RCRenderable *renderable)
    {
    _parent->onHit(_transform * point, _transform.linear() * normal, renderable);
    }

private:
  RCRenderable::Selector *_parent;
  Eks::Transform _transform;
  };

void RCTransform::intersect(const Eks::Line& line, Selector *s)
  {
  const Eks::Transform &tr = transform();

  Eks::Line lineCpy(line);
  lineCpy.transform(tr.inverse());

  InternalSelector sel(tr, s);
  RCRenderArray::intersect(lineCpy, &sel);
  }

void RCTransform::intersect(const Eks::Frustum& frus, Selector *s)
  {
  const Eks::Transform &tr = transform();

  Eks::Frustum frusCpy(frus);
  frusCpy.transform(tr.inverse());

  InternalSelector sel(tr, s);
  RCRenderArray::intersect(frusCpy, &sel);
  }

