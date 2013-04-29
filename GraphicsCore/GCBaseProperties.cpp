#include "GCGlobal.h"
#include "GCBaseProperties.h"
#include "shift/sdatabase.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sdata.inl"
#include "shift/Changes/shandler.inl"
#include "shift/TypeInformation/spropertytraits.h"


QTextStream &operator<<(QTextStream &s, Eks::Renderer *)
  {
  xAssertFail();
  return s;
  }

QDataStream &operator<<(QDataStream &s, Eks::Renderer *)
  {
  xAssertFail();
  return s;
  }

QTextStream &operator>>(QTextStream &s, Eks::Renderer *)
  {
  xAssertFail();
  return s;
  }

QDataStream &operator>>(QDataStream &s, Eks::Renderer *)
  {
  xAssertFail();
  return s;
  }

namespace Shift
{
namespace detail
{
void getDefault(Eks::Transform *t)
  {
  *t = Eks::Transform::Identity();
  }

void getDefault(Eks::Matrix3x3 *t)
  {
  *t = Eks::Matrix3x3::Identity();
  }

template <int IsAttribute> class PODPropertyTraits<GCRenderer, IsAttribute, true>
    : public Shift::detail::PropertyBaseTraits
  {
public:
  static bool shouldSaveValue(const Shift::Attribute *)
    {
    return false;
    }

  static void assign(const Shift::Attribute *p, Shift::Attribute *l )
    {
    const GCRenderer* f = p->uncheckedCastTo<GCRenderer>();
    GCRenderer* t = l->uncheckedCastTo<GCRenderer>();

    t->assign(f->value());
    }
  };

void assignTo(const Shift::Attribute *f, GCBoundingBox *to)
  {
  const GCBoundingBox *sProp = f->castTo<GCBoundingBox>();
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

#define IMPLEMENT_POD_GC_PROPERTY(T, Mode, name) IMPLEMENT_POD_PROPERTY(GRAPHICSCORE_EXPORT, GraphicsCore, T, Mode, name)

IMPLEMENT_POD_GC_PROPERTY(Eks::Renderer *, FullData, ren);
IMPLEMENT_POD_GC_PROPERTY(Eks::Matrix3x3, FullData, mat3x3);
IMPLEMENT_POD_GC_PROPERTY(Eks::Transform, FullData, trans);
IMPLEMENT_POD_GC_PROPERTY(Eks::ComplexTransform, FullData, complexTrans);
IMPLEMENT_POD_GC_PROPERTY(Eks::Cuboid, FullData, bb);
IMPLEMENT_POD_GC_PROPERTY(Eks::ShaderConstantData, ComputedData, data);
IMPLEMENT_POD_GC_PROPERTY(Eks::Shader, ComputedData, shad);
IMPLEMENT_POD_GC_PROPERTY(GraphicsCore::detail::ShaderInstance, ComputedData, shadInst);
IMPLEMENT_POD_GC_PROPERTY(Eks::Geometry, ComputedData, geo);
IMPLEMENT_POD_GC_PROPERTY(Eks::RasteriserState, ComputedData, ras);
IMPLEMENT_POD_GC_PROPERTY(Eks::IndexGeometry, ComputedData, igeo);
IMPLEMENT_POD_GC_PROPERTY(GCVertexLayoutWrapper, ComputedData, vertLay);

S_IMPLEMENT_TYPED_POINTER_TYPE(GCVertexLayoutPointer, GraphicsCore)
