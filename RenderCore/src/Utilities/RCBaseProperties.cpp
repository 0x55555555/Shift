#include "RCGlobal.h"
#include "Math/XMathVector.h"
#include "Utilities/RCBaseProperties.h"
#include "shift/sdatabase.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sdata.inl"
#include "shift/Changes/shandler.inl"
#include "shift/TypeInformation/spropertytraits.h"

namespace Eks
{
std::ostream &operator<<(std::ostream &s, Eks::Renderer *)
  {
  xAssertFail();
  return s;
  }

std::istream &operator>>(std::istream &s, Eks::Renderer *)
  {
  xAssertFail();
  return s;
  }
}

namespace Shift
{
namespace detail
{
template <> class DataEmbeddedInstanceInformation<Shift::Data<Eks::Renderer *>>
    : public Shift::Property::EmbeddedInstanceInformation
  {
public:
  void initiateAttribute(Attribute *propertyToInitiate, AttributeInitialiserHelper *) const X_OVERRIDE
    {
    propertyToInitiate->uncheckedCastTo<Shift::Data<Eks::Renderer *>>()->_value = 0;
    }

  Eks::Renderer *defaultValue() const { return 0; }
  };

void getDefault(Eks::Transform *t)
  {
  *t = Eks::Transform::Identity();
  }

void getDefault(Eks::Matrix3x3 *t)
  {
  *t = Eks::Matrix3x3::Identity();
  }

void getDefault(Eks::Renderer **t)
  {
  *t = nullptr;
  }

template <int IsAttribute> class PODPropertyTraits<RCRenderer, IsAttribute, true>
    : public Shift::detail::PropertyBaseTraits
  {
public:
  static bool shouldSaveValue(const Shift::Attribute *)
    {
    return false;
    }

  static void assign(const Shift::Attribute *p, Shift::Attribute *l )
    {
    const RCRenderer* f = p->uncheckedCastTo<RCRenderer>();
    RCRenderer* t = l->uncheckedCastTo<RCRenderer>();

    t->assign(f->value());
    }
  };

void assignTo(const Shift::Attribute *, Shift::Attribute *)
  {
  xAssertFail();
  }

void assignTo(const Shift::Attribute *f, RCBoundingBox *to)
  {
  const RCBoundingBox *sProp = f->castTo<RCBoundingBox>();
  if(sProp)
    {
    to->assign(sProp->value());
    return;
    }
  }

void assignTo(const Shift::Attribute *f, Shift::Data<Eks::Renderer *> *to)
  {
  const RCRenderer *sProp = f->castTo<RCRenderer>();
  if(sProp)
    {
    to->assign(sProp->value());
    return;
    }
  }

void assignTo(const Shift::Attribute *f, Matrix3x3Property *to)
  {
  const Matrix3x3Property *sProp = f->castTo<Matrix3x3Property>();
  if(sProp)
    {
    to->assign(sProp->value());
    return;
    }
  }

void assignTo(const Shift::Attribute *f, TransformProperty *to)
  {
  const TransformProperty *sProp = f->castTo<TransformProperty>();
  if(sProp)
    {
    to->assign(sProp->value());
    return;
    }

  const ComplexTransformProperty *tProp = f->castTo<ComplexTransformProperty>();
  if(tProp)
    {
    to->assign(Eks::Transform(tProp->value().matrix()));
    return;
    }
  }

void assignTo(const Shift::Attribute *f, ComplexTransformProperty *to)
  {
  const ComplexTransformProperty *tProp = f->castTo<ComplexTransformProperty>();
  if(tProp)
    {
    to->assign(tProp->value());
    return;
    }

  const TransformProperty *sProp = f->castTo<TransformProperty>();
  if(sProp)
    {
    to->assign(Eks::ComplexTransform(sProp->value().matrix()));
    return;
    }
  }
}
}

#define IMPLEMENT_POD_RC_PROPERTY(T, Mode, name) IMPLEMENT_POD_PROPERTY(RENDERCORE_EXPORT, RenderCore, T, Mode, name)

IMPLEMENT_POD_RC_PROPERTY(Eks::Renderer *, FullData, ren);
IMPLEMENT_POD_RC_PROPERTY(Eks::Matrix3x3, FullData, mat3x3);
IMPLEMENT_POD_RC_PROPERTY(Eks::Transform, FullData, trans);
IMPLEMENT_POD_RC_PROPERTY(Eks::ComplexTransform, FullData, complexTrans);
IMPLEMENT_POD_RC_PROPERTY(Eks::BoundingBox, FullData, bb);
IMPLEMENT_POD_RC_PROPERTY(Eks::ShaderConstantData, ComputedData, data);
IMPLEMENT_POD_RC_PROPERTY(Eks::Shader, ComputedData, shad);
IMPLEMENT_POD_RC_PROPERTY(GraphicsCore::detail::ShaderInstance, ComputedData, shadInst);
IMPLEMENT_POD_RC_PROPERTY(Eks::Geometry, ComputedData, geo);
IMPLEMENT_POD_RC_PROPERTY(Eks::RasteriserState, ComputedData, ras);
IMPLEMENT_POD_RC_PROPERTY(Eks::IndexGeometry, ComputedData, igeo);
IMPLEMENT_POD_RC_PROPERTY(RCVertexLayoutWrapper, ComputedData, vertLay);

S_IMPLEMENT_TYPED_POINTER_TYPE(RCVertexLayoutPointer, RenderCore)
