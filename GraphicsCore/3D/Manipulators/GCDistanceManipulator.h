#ifndef GCDISTANCEMANIPULATOR_H
#define GCDISTANCEMANIPULATOR_H

#include "GCGlobal.h"
#include "GCManipulator.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"

class GCManipulatorDistanceDelegate : public GCVisualManipulator::Delegate
  {
public:
  virtual bool hitTest(
      const GCVisualManipulator *manip,
      const QPoint &,
      const GCViewableTransform *camera,
      const Eks::Vector3D &clickDirection, // in world space
      float *distance) const;

  virtual void render(const GCVisualManipulator *manip,
      const GCViewableTransform *,
      Eks::Renderer *r) const;

private:
  mutable Eks::IndexGeometry _igeo;
  mutable Eks::Geometry _geo;
  mutable Eks::Shader *_shader;
  mutable const Eks::ShaderVertexLayout *_layout;
  mutable Eks::ShaderConstantData _data;
  };

class GRAPHICSCORE_EXPORT GCDistanceManipulator : public GCDisplacementDragManipulator
  {
  S_PROPERTY_CONTAINER(GCDistanceManipulator, GCDisplacementDragManipulator, 0);

public:
  GCDistanceManipulator();

  Shift::FloatProperty distance;
  Shift::FloatProperty scaleFactor;

  // displacement moved from click point in local space
  Shift::Vector3DProperty absoluteDisplacement;

  void addDriven(Shift::FloatProperty *in);

  void onDrag(const MouseMoveEvent &);

  void setDriver(Shift::FloatProperty *f)
    {
    distance.setInput(f);
    }

  Eks::Transform resultTransform(const GCViewableTransform *tr) const X_OVERRIDE;

private:
  QVector <Shift::FloatProperty *> _driven;
  };

#endif // GCDISTANCEMANIPULATOR_H
