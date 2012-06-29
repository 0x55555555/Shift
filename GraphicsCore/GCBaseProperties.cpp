#include "GCBaseProperties.h"
#include "sdatabase.h"
#include "spropertyinformationhelpers.h"
#include "shandlerimpl.h"

void writeValue(SSaver &, const XShader &)
  {
  xAssertFail();
  }

void readValue(SLoader &, XShader &)
  {
  xAssertFail();
  }

#define IMPLEMENT_POD_GC_PROPERTY(name) IMPLEMENT_POD_PROPERTY(name, GraphicsCore)

IMPLEMENT_POD_GC_PROPERTY(TransformProperty);
IMPLEMENT_POD_GC_PROPERTY(ComplexTransformProperty);
IMPLEMENT_POD_GC_PROPERTY(GCRuntimeShader)
IMPLEMENT_POD_GC_PROPERTY(GCQImage)
IMPLEMENT_POD_GC_PROPERTY(GCRuntimeGeometry)
IMPLEMENT_POD_GC_PROPERTY(GCBoundingBox)
IMPLEMENT_POD_GC_PROPERTY(GCRuntimeShaderInstance)

void GCBoundingBox::assignProperty(const SProperty *f, SProperty *t)
  {
  GCBoundingBox *to = t->uncheckedCastTo<GCBoundingBox>();

  const GCBoundingBox *sProp = f->castTo<GCBoundingBox>();
  if(sProp)
    {
    to->assign(sProp->value());
    return;
    }
  }
void GCRuntimeGeometry::assignProperty(const SProperty *f, SProperty *t)
  {
  GCRuntimeGeometry *to = t->uncheckedCastTo<GCRuntimeGeometry>();

  const GCRuntimeGeometry *sProp = f->castTo<GCRuntimeGeometry>();
  if(sProp)
    {
    to->assign(sProp->value());
    return;
    }
  }

void GCQImage::assignProperty(const SProperty *f, SProperty *t)
  {
  SProfileFunction
  GCQImage *to = t->uncheckedCastTo<GCQImage>();

  const GCQImage *qImageProp = f->castTo<GCQImage>();
  if(qImageProp)
    {
    to->assign(qImageProp->value());
    }
  }

void GCRuntimeShader::assignProperty(const SProperty *f, SProperty *t)
  {
  GCRuntimeShader *to = t->uncheckedCastTo<GCRuntimeShader>();

  const GCRuntimeShader *sProp = f->castTo<GCRuntimeShader>();
  if(sProp)
    {
    to->assign(sProp->value());
    return;
    }
  }
void GCRuntimeShaderInstance::assignProperty(const SProperty *f, SProperty *t)
  {
  GCRuntimeShaderInstance *to = t->uncheckedCastTo<GCRuntimeShaderInstance>();

  const GCRuntimeShaderInstance *sProp = f->castTo<GCRuntimeShaderInstance>();
  if(sProp)
    {
    to->assign(sProp->value());
    return;
    }
  }

void TransformProperty::assignProperty(const SProperty *f, SProperty *t)
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
    to->assign(XTransform(tProp->value().matrix()));
    return;
    }
  }

void ComplexTransformProperty::assignProperty(const SProperty *f, SProperty *t)
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
    to->assign(XComplexTransform(sProp->value().matrix()));
    return;
    }

  }
