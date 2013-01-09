#ifndef GCMANIPULATOR_H
#define GCMANIPULATOR_H

#include "GCGlobal.h"
#include "shift/Properties/spropertycontainer.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "GCBaseProperties.h"

class XRenderer;
class QPainter;
class GCTransform;
class GCCamera;

class GRAPHICSCORE_EXPORT GCManipulatable : public Shift::InterfaceBase
  {
  S_INTERFACE_TYPE(ManipulatableInterface)  
public:
  virtual void addManipulators(Shift::PropertyArray *, const GCTransform *tr=0) = 0;
  };

class GRAPHICSCORE_EXPORT GCVisualManipulator : public Shift::PropertyContainer
  {
  S_ABSTRACT_PROPERTY_CONTAINER(GCVisualManipulator, PropertyContainer, 0)

public:
  class Delegate
    {
  public:
    virtual ~Delegate() { }

    virtual bool hitTest(
      const GCVisualManipulator *toRender,
      const QPoint &widgetSpacePoint,
      const GCCamera *camera,
      const Eks::Vector3D &clickDirection, // in world space
      float *distance) = 0;

    virtual void render(const GCVisualManipulator *toRender,
                        const GCCamera *camera,
                        XRenderer *) = 0;

    virtual Eks::Vector3D focalPoint(const GCVisualManipulator *toRender) const
      {
      return toRender->worldCentre().translation();
      }
    };

XProperties:
  XProperty(Delegate *, delegate, setDelegate);

public:
  GCVisualManipulator();
  
  Shift::BoolProperty show;
  TransformProperty worldCentre;
  Shift::FloatProperty manipulatorsDisplayScale;

  virtual Eks::Vector3D focalPoint() const;
  
  virtual bool hitTest(
    const QPoint &widgetSpacePoint,
    const GCCamera *camera,
    const Eks::Vector3D &clickDirection, // in world space
    float *distance,
    GCVisualManipulator **clicked);
    
  virtual void render(const GCCamera *camera, XRenderer *) const;
  
  struct MouseEvent
    {
    QPoint widgetPoint;
    const GCCamera *cam;
    Eks::Vector3D direction;
    };

  struct MouseMoveEvent : public MouseEvent
    {
    QPoint lastWidgetPoint;
    Eks::Vector3D lastDirection;
    };

  virtual void onMouseClick(const MouseEvent &) = 0;
  virtual void onMouseDoubleClick(const MouseEvent &) = 0;
  virtual void onMouseDrag(const MouseMoveEvent &) = 0;
  virtual void onMouseRelease(const MouseEvent &) = 0;
  };

S_PROPERTY_INTERFACE(GCVisualManipulator);
  
class GRAPHICSCORE_EXPORT GCVisualCompoundManipulator : public GCVisualManipulator
  {
  S_ABSTRACT_PROPERTY_CONTAINER(GCVisualCompoundManipulator, GCVisualManipulator, 0)

public:
  GCVisualCompoundManipulator();
  
  virtual bool hitTest(
    const QPoint &widgetSpacePoint,
    const GCCamera *camera,
    const Eks::Vector3D &clickDirection, // in world space
    float *distance,
    GCVisualManipulator **clicked);

  virtual void render(const GCCamera *camera, XRenderer *r) const;

  virtual void onMouseClick(const MouseEvent &);
  virtual void onMouseDoubleClick(const MouseEvent &);
  virtual void onMouseDrag(const MouseMoveEvent &);
  virtual void onMouseRelease(const MouseEvent &);
  };

S_PROPERTY_INTERFACE(GCVisualCompoundManipulator);

class GRAPHICSCORE_EXPORT GCVisualDragManipulator : public GCVisualManipulator
  {
  S_ABSTRACT_PROPERTY_CONTAINER(GCVisualDragManipulator, GCVisualManipulator, 0)

public:
  GCVisualDragManipulator();
  
  virtual void onDrag(const MouseMoveEvent &) = 0;

  virtual void onMouseClick(const MouseEvent &);
  virtual void onMouseDoubleClick(const MouseEvent &);
  virtual void onMouseDrag(const MouseMoveEvent &);
  virtual void onMouseRelease(const MouseEvent &);
  };

S_PROPERTY_INTERFACE(GCVisualDragManipulator);

class GRAPHICSCORE_EXPORT GCVisualClickManipulator : public GCVisualManipulator
  {
  S_ABSTRACT_PROPERTY_CONTAINER(GCVisualClickManipulator, GCVisualManipulator, 0)

public:
  GCVisualClickManipulator();

  virtual void onClick() = 0;

  virtual void onMouseClick(const MouseEvent &);
  virtual void onMouseDoubleClick(const MouseEvent &);
  virtual void onMouseDrag(const MouseMoveEvent &);
  virtual void onMouseRelease(const MouseEvent &);
  };

S_PROPERTY_INTERFACE(GCVisualClickManipulator);

class GRAPHICSCORE_EXPORT GCLinearDragManipulator : public GCVisualDragManipulator
  {
  S_ABSTRACT_PROPERTY_CONTAINER(GCLinearDragManipulator, GCVisualDragManipulator, 0)

public:
  GCLinearDragManipulator();

  enum LockMode
    {
    Free,
    Planar,
    Linear
    };

  Shift::EnumProperty lockMode;
  Shift::Vector3DProperty lockDirection; // normal for planar, direction for linear, local space

  void onDrag(const MouseMoveEvent &, Eks::Vector3D &rel);
  };

S_PROPERTY_INTERFACE(GCLinearDragManipulator);

#endif // GCMANIPULATOR_H
