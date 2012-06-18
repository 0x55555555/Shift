#include "GCShaderDataBindings.h"
#include "GCTexture.h"

namespace GCShaderDataBindings
{

Vector3::Vector3() : GCShaderBindableData(true)
  {
  }

void Vector3::bindData(XShader *s, const SProperty *p) const
  {
  const Vector3DProperty *c = p->uncheckedCastTo<Vector3DProperty>();

  XShaderVariable *v = s->getVariable(p->name());
  xAssert(v);

  v->setValue(c->value());
  }

Vector4::Vector4() : GCShaderBindableData(true)
  {
  }

void Vector4::bindData(XShader *s, const SProperty *p) const
  {
  const ColourProperty *c = p->uncheckedCastTo<ColourProperty>();

  XShaderVariable *v = s->getVariable(p->name());
  xAssert(v);

  v->setValue(c->value());
  }

TextureRef::TextureRef() : GCShaderBindableData(true)
  {
  }

void TextureRef::bindData(XShader *s, const SProperty *p) const
  {
  const GCTexturePointer *c = p->uncheckedCastTo<GCTexturePointer>();

  XShaderVariable *v = s->getVariable(p->name());
  xAssert(v);

  if(c->input())
    {
    v->setValue(c->pointed()->value());
    }
  }

}
