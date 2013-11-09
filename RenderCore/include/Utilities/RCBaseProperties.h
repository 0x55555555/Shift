#ifndef RCBASEPROPERTIES_H
#define RCBASEPROPERTIES_H

#include "RCGlobal.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "XTransform.h"
#include "QtGui/QImage"
#include "XShader.h"
#include "XGeometry.h"
#include "XRasteriserState.h"
#include "XBoundingBox.h"

namespace Shift
{
namespace detail
{
RENDERCORE_EXPORT void getDefault(Eks::Transform *);
RENDERCORE_EXPORT void getDefault(Eks::Matrix3x3 *);

template <> class DataEmbeddedInstanceInformation<Shift::Data<Eks::Renderer *>>
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

RENDERCORE_EXPORT QTextStream &operator<<(QTextStream &s, Eks::Renderer *v);
RENDERCORE_EXPORT QDataStream &operator<<(QDataStream &s, Eks::Renderer *v);
RENDERCORE_EXPORT QTextStream &operator>>(QTextStream &s, Eks::Renderer *v);
RENDERCORE_EXPORT QDataStream &operator>>(QDataStream &s, Eks::Renderer *v);

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

struct RCVertexLayoutWrapper
  {
  const Eks::ShaderVertexLayoutDescription *layout;
  xsize layoutCount;
  };

typedef Shift::Data<Eks::Shader, Shift::ComputedData>
  RCRuntimeShader;
typedef Shift::Data<Eks::ShaderConstantData, Shift::ComputedData>
  RCShaderRuntimeConstantData;
typedef Shift::Data<GraphicsCore::detail::ShaderInstance, Shift::ComputedData>
  RCRuntimeShaderInstance;
typedef Shift::Data<Eks::RasteriserState, Shift::ComputedData>
  RCRuntimeRasteriserState;
typedef Shift::Data<Eks::Geometry, Shift::ComputedData>
  RCRuntimeGeometry;
typedef Shift::Data<Eks::IndexGeometry, Shift::ComputedData>
  RCRuntimeIndexGeometry;
typedef Shift::Data<RCVertexLayoutWrapper, Shift::ComputedData>
  RCVertexLayout;
typedef Shift::Data<Eks::Renderer *>
  RCRenderer;
typedef Shift::Data<Eks::Transform>
  TransformProperty;
typedef Shift::Data<Eks::Matrix3x3>
  Matrix3x3Property;
typedef Shift::Data<Eks::ComplexTransform>
  ComplexTransformProperty;
typedef Shift::Data<Eks::BoundingBox>
  RCBoundingBox;


S_TYPED_POINTER_TYPE(RENDERCORE_EXPORT, RCVertexLayoutPointer, RCVertexLayout)

#endif // RCBASEPROPERTIES_H
