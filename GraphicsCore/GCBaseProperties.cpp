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

void GCRuntimeShaderInstance::assignProperty(const Property *f, Property *t)
  {
  GCRuntimeShaderInstance *to = t->uncheckedCastTo<GCRuntimeShaderInstance>();

  const GCRuntimeShaderInstance *sProp = f->castTo<GCRuntimeShaderInstance>();
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
