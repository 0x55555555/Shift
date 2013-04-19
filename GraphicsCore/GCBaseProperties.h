#ifndef GCBASEPROPERTIES_H
#define GCBASEPROPERTIES_H

#include "GCGlobal.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "XTransform.h"
#include "QtGui/QImage"
#include "XShader.h"
#include "XGeometry.h"
#include "XRasteriserState.h"
#include "XCuboid.h"

namespace Shift
{
namespace detail
{
void getDefault(Eks::Transform *);
void getDefault(Eks::Matrix3x3 *);
}
}

namespace GraphicsCore
{
namespace detail
{

class ShaderInstance
  {
public:
  ShaderInstance() : instance(0) { }
  Eks::Shader *instance;

  bool operator !=(const ShaderInstance& i) const
    {
    return i.instance != instance;
    }
  };
}

}

Q_DECLARE_METATYPE(GraphicsCore::detail::ShaderInstance)

namespace
{
QTextStream &operator <<(QTextStream &str, const QImage &data)
  {
  QByteArray arr;
  // approximate hopeful size?
  arr.resize(data.byteCount() + 64);
  QDataStream dStr(&arr, QIODevice::WriteOnly);
  dStr << data;

  return str << arr.toHex();
  }

QTextStream &operator >>(QTextStream &str, QImage &data)
  {
  QByteArray arr;
  str >> arr;
  arr = QByteArray::fromHex(arr);

  QDataStream dStr(&arr, QIODevice::ReadOnly);
  dStr >> data;
  return str;
  }

QTextStream &operator<<(QTextStream &s, const Eks::Geometry &)
  {
  xAssertFail();
  return s;
  }

QTextStream &operator>>(QTextStream &s, const Eks::Geometry &)
  {
  xAssertFail();
  return s;
  }


QDataStream &operator>>(QDataStream& s, GraphicsCore::detail::ShaderInstance&)
  {
  xAssertFail();
  return s;
  }

QDataStream &operator<<(QDataStream& s, const GraphicsCore::detail::ShaderInstance&)
  {
  xAssertFail();
  return s;
  }


QTextStream &operator>>(QTextStream& s, GraphicsCore::detail::ShaderInstance&)
  {
  xAssertFail();
  return s;
  }

QTextStream &operator<<(QTextStream& s, const GraphicsCore::detail::ShaderInstance&)
  {
  xAssertFail();
  return s;
  }
}

class GRAPHICSCORE_EXPORT GCRuntimeShader
    : public Shift::PODPropertyBase<Eks::Shader,
                                GCRuntimeShader>
  {
public:
  typedef Shift::detail::BasePODPropertyTraits<GCRuntimeShader> Traits;
  enum { TypeId = 152 };
  S_PROPERTY(GCRuntimeShader, Property, 0);
  };

class GRAPHICSCORE_EXPORT GCShaderRuntimeConstantData
    : public Shift::PODPropertyBase<Eks::ShaderConstantData,
                                GCShaderRuntimeConstantData>
  {
public:
  typedef Shift::detail::BasePODPropertyTraits<GCShaderRuntimeConstantData> Traits;
  enum { TypeId = 153 };
  S_PROPERTY(GCShaderRuntimeConstantData, Property, 0);
  };

class GRAPHICSCORE_EXPORT GCRuntimeShaderInstance
    : public Shift::PODPropertyBase<GraphicsCore::detail::ShaderInstance,
                                GCRuntimeShaderInstance >
  {
public:
  typedef Shift::detail::BasePODPropertyTraits<GCRuntimeShaderInstance> Traits;
  enum { TypeId = 156 };
  S_PROPERTY(GCRuntimeShaderInstance, Property, 0);
  };

class GRAPHICSCORE_EXPORT GCRuntimeRasteriserState
    : public Shift::PODPropertyBase<Eks::RasteriserState,
                                GCRuntimeRasteriserState>
  {
public:
  typedef Shift::detail::BasePODPropertyTraits<GCRuntimeRasteriserState> Traits;
  enum { TypeId = 160 };
  S_PROPERTY(GCRuntimeRasteriserState, Property, 0);
  };


class GRAPHICSCORE_EXPORT GCRuntimeGeometry
    : public Shift::PODPropertyBase<Eks::Geometry,
                                GCRuntimeGeometry>
  {
public:
  typedef Shift::detail::BasePODPropertyTraits<GCRuntimeGeometry> Traits;
  enum { TypeId = 154 };
  S_PROPERTY(GCRuntimeGeometry, Property, 0);
  };

class GRAPHICSCORE_EXPORT GCRuntimeIndexGeometry
    : public Shift::PODPropertyBase<Eks::IndexGeometry,
                                GCRuntimeIndexGeometry>
  {
public:
  typedef Shift::detail::BasePODPropertyTraits<GCRuntimeIndexGeometry> Traits;
  enum { TypeId = 158 };
  S_PROPERTY(GCRuntimeIndexGeometry, Property, 0);
  };

class GRAPHICSCORE_EXPORT GCRenderer
    : public Shift::PODProperty<Eks::Renderer *,
                                GCRenderer>
  {
public:
  class Traits;
  class EmbeddedInstanceInformation : public Shift::PODPropertyBase<Eks::Renderer *, GCRenderer>::EmbeddedInstanceInformation
    {
  public:
    void initiateAttribute(Attribute *propertyToInitiate) const;
    };

  enum { TypeId = 151 };
  S_PROPERTY(GCRenderer, Property, 0);

private:
  friend class EmbeddedInstanceInformation;
  friend class Traits;
  };

struct GCVertexLayoutWrapper
  {
  const Eks::ShaderVertexLayoutDescription *layout;
  xsize layoutCount;
  };

class GRAPHICSCORE_EXPORT GCVertexLayout
    : public Shift::PODPropertyBase<GCVertexLayoutWrapper,
                                GCVertexLayout>
  {
public:
  typedef Shift::detail::BasePODPropertyTraits<GCVertexLayout> Traits;
  enum { TypeId = 159 };
  S_PROPERTY(GCVertexLayout, Property, 0);
  };

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCVertexLayoutPointer, GCVertexLayout)

DEFINE_POD_PROPERTY(GRAPHICSCORE_EXPORT, TransformProperty, Eks::Transform, 150);
DEFINE_POD_PROPERTY(GRAPHICSCORE_EXPORT, Matrix3x3Property, Eks::Matrix3x3, 157);
DEFINE_POD_PROPERTY(GRAPHICSCORE_EXPORT, ComplexTransformProperty, Eks::ComplexTransform, 151);
DEFINE_POD_PROPERTY(GRAPHICSCORE_EXPORT, GCBoundingBox, Eks::Cuboid, 155)

#endif // GCBASEPROPERTIES_H
