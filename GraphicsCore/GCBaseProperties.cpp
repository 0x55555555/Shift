#include "GCGlobal.h"
#include "GCBaseProperties.h"
#include "shift/sdatabase.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Changes/shandler.inl"
#include "shift/TypeInformation/spropertytraits.h"

void writeValue(Shift::Saver &, const Eks::Shader &)
  {
  xAssertFail();
  }

void readValue(Shift::Loader &, Eks::Shader &)
  {
  xAssertFail();
  }

#define IMPLEMENT_POD_GC_PROPERTY(name) IMPLEMENT_POD_PROPERTY(name, GraphicsCore)

IMPLEMENT_POD_GC_PROPERTY(Matrix3x3Property);
IMPLEMENT_POD_GC_PROPERTY(TransformProperty);
IMPLEMENT_POD_GC_PROPERTY(ComplexTransformProperty);
IMPLEMENT_POD_GC_PROPERTY(GCBoundingBox)

void GCBoundingBox::assignProperty(const Property *f, Property *t)
  {
  GCBoundingBox *to = t->uncheckedCastTo<GCBoundingBox>();

  const GCBoundingBox *sProp = f->castTo<GCBoundingBox>();
  if(sProp)
    {
    to->assign(sProp->value());
    return;
    }
  }

void Matrix3x3Property::assignProperty(const Property *f, Property *t)
  {
  Matrix3x3Property *to = t->uncheckedCastTo<Matrix3x3Property>();

  const Matrix3x3Property *sProp = f->castTo<Matrix3x3Property>();
  if(sProp)
    {
    to->assign(sProp->value());
    return;
    }
  }

void TransformProperty::assignProperty(const Property *f, Property *t)
  {
  TransformProperty *to = t->uncheckedCastTo<TransformProperty>();

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

void ComplexTransformProperty::assignProperty(const Property *f, Property *t)
  {
  ComplexTransformProperty *to = t->uncheckedCastTo<ComplexTransformProperty>();

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

S_IMPLEMENT_PROPERTY(GCRuntimeShader, GraphicsCore)

void GCRuntimeShader::createTypeInformation(
    Shift::PropertyInformationTyped<GCRuntimeShader> *,
    const Shift::PropertyInformationCreateData &)
  {
  }

S_IMPLEMENT_PROPERTY(GCRuntimeGeometry, GraphicsCore)

void GCRuntimeGeometry::createTypeInformation(
    Shift::PropertyInformationTyped<GCRuntimeGeometry> *,
    const Shift::PropertyInformationCreateData &)
  {
  }

S_IMPLEMENT_PROPERTY(GCRuntimeIndexGeometry, GraphicsCore)

void GCRuntimeIndexGeometry::createTypeInformation(
    Shift::PropertyInformationTyped<GCRuntimeIndexGeometry> *,
    const Shift::PropertyInformationCreateData &)
  {
  }

S_IMPLEMENT_PROPERTY(GCRuntimeShaderInstance, GraphicsCore)

void GCRuntimeShaderInstance::createTypeInformation(
    Shift::PropertyInformationTyped<GCRuntimeShaderInstance> *,
    const Shift::PropertyInformationCreateData &)
  {
  }

class GCRenderer::Traits : public Shift::PODPropertyBase<Eks::Renderer *, GCRenderer>::Traits
  {
public:
  static void assignProperty(const Shift::Property *p, Shift::Property *l )
    {
    const GCRenderer* f = p->uncheckedCastTo<GCRenderer>();
    GCRenderer* t = l->uncheckedCastTo<GCRenderer>();

    t->assign(f->value());
    }
  };

S_IMPLEMENT_PROPERTY(GCRenderer, GraphicsCore)

void GCRenderer::createTypeInformation(
    Shift::PropertyInformationTyped<GCRenderer> *,
    const Shift::PropertyInformationCreateData &)
  {
  }

void GCRenderer::EmbeddedInstanceInformation::initiateProperty(Property *propertyToInitiate) const
  {
  propertyToInitiate->uncheckedCastTo<GCRenderer>()->_value = 0;
  }


S_IMPLEMENT_PROPERTY(GCVertexLayout, GraphicsCore)

void GCVertexLayout::createTypeInformation(
    Shift::PropertyInformationTyped<GCVertexLayout> *,
    const Shift::PropertyInformationCreateData &)
  {
  }

S_IMPLEMENT_TYPED_POINTER_TYPE(GCVertexLayoutPointer, GraphicsCore)
