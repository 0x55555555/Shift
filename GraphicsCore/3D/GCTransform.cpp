#include "3D/GCTransform.h"
#include "shift/TypeInformation/styperegistry.h"
#include "Manipulators/GCTranslateManipulator.h"
#include "shift/sdatabase.h"
#include "XLine.h"
#include "XFrustum.h"
#include "XRenderer.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Changes/shandler.inl"

void unionTransformedBounds(GCTransform* tr)
  {
  GCBoundingBox::ComputeLock l(&tr->bounds);
  Eks::Cuboid *data = l.data();
  *data = Eks::Cuboid();

  xForeach(auto r, tr->renderGroup.walker<GCRenderablePointer>())
    {
    const GCRenderable* ptd = r->pointed();

    data->unite(ptd->bounds());
    }

  *data = tr->transform() * *data;
  }

S_IMPLEMENT_PROPERTY(GCTransform, GraphicsCore)

void GCTransform::createTypeInformation(Shift::PropertyInformationTyped<GCTransform> *info,
                                        const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto boundsInfo = childBlock.overrideChild(&GCTransform::bounds);
    boundsInfo->setCompute<unionTransformedBounds>();

    auto trInfo = childBlock.add(&GCTransform::transform, "transform");
    trInfo->setDefault(Eks::Transform::Identity());
    trInfo->setAffects(data, boundsInfo);
    }
  }

void GCTransform::render(Eks::Renderer *r, const RenderState &state) const
  {
  RenderState s;
  s.transform = state.transform * transform();

  r->setTransform(s.transform);

  GCRenderArray::render(r, s);
  }

void GCTransform::addManipulators(Shift::PropertyArray *a, const GCTransform *tr)
  {
  xAssert(tr == 0);

  GCTranslateManipulator *manip = a->add<GCTranslateManipulator>();

  manip->addDriven(&transform);

  transform.connect(&manip->worldCentre);
  }

class InternalSelector : public GCRenderable::Selector
  {
public:
  InternalSelector(const Eks::Transform &tr, Selector *parent)
      : _parent(parent), _transform(tr)
    {
    }

  void onHit(const Eks::Vector3D &point, const Eks::Vector3D &normal, GCRenderable *renderable)
    {
    _parent->onHit(_transform * point, _transform.linear() * normal, renderable);
    }

private:
  GCRenderable::Selector *_parent;
  Eks::Transform _transform;
  };

void GCTransform::intersect(const Eks::Line& line, Selector *s)
  {
  const Eks::Transform &tr = transform();

  Eks::Line lineCpy(line);
  lineCpy.transform(tr.inverse());

  InternalSelector sel(tr, s);
  GCRenderArray::intersect(lineCpy, &sel);
  }

void GCTransform::intersect(const Eks::Frustum& frus, Selector *s)
  {
  const Eks::Transform &tr = transform();

  Eks::Frustum frusCpy(frus);
  frusCpy.transform(tr.inverse());

  InternalSelector sel(tr, s);
  GCRenderArray::intersect(frusCpy, &sel);
  }

