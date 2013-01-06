#ifndef GCBASEPROPERTIES_H
#define GCBASEPROPERTIES_H

#include "GCGlobal.h"
#include "shift/Properties/sbaseproperties.h"
#include "XTransform.h"
#include "QImage"
#include "XShader.h"
#include "XGeometry.h"
#include "XCuboid.h"

namespace GraphicsCore
{
namespace detail
{

class ShaderInstance
  {
public:
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

DEFINE_POD_PROPERTY(GRAPHICSCORE_EXPORT, TransformProperty, Eks::Transform, Eks::Transform::Identity(), 150);
DEFINE_POD_PROPERTY(GRAPHICSCORE_EXPORT, Matrix3x3Property, Eks::Matrix3x3, Eks::Matrix3x3::Identity(), 157);
DEFINE_POD_PROPERTY(GRAPHICSCORE_EXPORT, ComplexTransformProperty, Eks::ComplexTransform, Eks::ComplexTransform(), 151);
DEFINE_POD_PROPERTY(GRAPHICSCORE_EXPORT, GCRuntimeShader, Eks::Shader, Eks::Shader(), 152)
DEFINE_POD_PROPERTY(GRAPHICSCORE_EXPORT, GCQImage, QImage, QImage(), 153)
DEFINE_POD_PROPERTY(GRAPHICSCORE_EXPORT, GCRuntimeGeometry, Eks::Geometry, Eks::Geometry(), 154)
DEFINE_POD_PROPERTY(GRAPHICSCORE_EXPORT, GCBoundingBox, Eks::Cuboid, Eks::Cuboid(), 155)
DEFINE_POD_PROPERTY(GRAPHICSCORE_EXPORT, GCRuntimeShaderInstance, GraphicsCore::detail::ShaderInstance, GraphicsCore::detail::   ShaderInstance(), 156)

#endif // GCBASEPROPERTIES_H
