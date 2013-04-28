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
GRAPHICSCORE_EXPORT void getDefault(Eks::Transform *);
GRAPHICSCORE_EXPORT void getDefault(Eks::Matrix3x3 *);

template <int IsFull> class PODEmbeddedInstanceInformation<Shift::Data<Eks::Renderer *>, IsFull>
    : public Shift::Property::EmbeddedInstanceInformation
  {
public:
  void initiateAttribute(Attribute *propertyToInitiate) const
    {
    propertyToInitiate->uncheckedCastTo<Shift::Data<Eks::Renderer *>>()->_value = 0;
    }

  Eks::Renderer *defaultValue() const { return 0; }
  };
}
}

GRAPHICSCORE_EXPORT QTextStream &operator<<(QTextStream &s, Eks::Renderer *v);
GRAPHICSCORE_EXPORT QDataStream &operator<<(QDataStream &s, Eks::Renderer *v);
GRAPHICSCORE_EXPORT QTextStream &operator>>(QTextStream &s, Eks::Renderer *v);
GRAPHICSCORE_EXPORT QDataStream &operator>>(QDataStream &s, Eks::Renderer *v);

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

#if X_QT_INTEROP

Q_DECLARE_METATYPE(GraphicsCore::detail::ShaderInstance)

#endif

struct GCVertexLayoutWrapper
  {
  const Eks::ShaderVertexLayoutDescription *layout;
  xsize layoutCount;
  };

typedef Shift::Data<Eks::Shader, Shift::ComputedData>
  GCRuntimeShader;
typedef Shift::Data<Eks::ShaderConstantData, Shift::ComputedData>
  GCShaderRuntimeConstantData;
typedef Shift::Data<GraphicsCore::detail::ShaderInstance, Shift::ComputedData>
  GCRuntimeShaderInstance;
typedef Shift::Data<Eks::RasteriserState, Shift::ComputedData>
  GCRuntimeRasteriserState;
typedef Shift::Data<Eks::Geometry, Shift::ComputedData>
  GCRuntimeGeometry;
typedef Shift::Data<Eks::IndexGeometry, Shift::ComputedData>
  GCRuntimeIndexGeometry;
typedef Shift::Data<GCVertexLayoutWrapper, Shift::ComputedData>
  GCVertexLayout;
typedef Shift::Data<Eks::Renderer *>
  GCRenderer;
typedef Shift::Data<Eks::Transform>
  TransformProperty;
typedef Shift::Data<Eks::Matrix3x3>
  Matrix3x3Property;
typedef Shift::Data<Eks::ComplexTransform>
  ComplexTransformProperty;
typedef Shift::Data<Eks::Cuboid>
  GCBoundingBox;


S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCVertexLayoutPointer, GCVertexLayout)

#endif // GCBASEPROPERTIES_H
