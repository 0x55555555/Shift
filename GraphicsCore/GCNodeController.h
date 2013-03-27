#ifndef GCNODECONTROLLER_H
#define GCNODECONTROLLER_H

#include "GCGlobal.h"
#include "X2DCanvas.h"
#include "XAbstractRenderModel.h"

namespace Shift
{
class Entity;
}
class GCAbstractNodeDelegate;

#if 0

class GRAPHICSCORE_EXPORT GCNodeController : public QObject, public XSimple2DCanvasController
  {
  Q_OBJECT
public:
  GCNodeController(X2DCanvas *c);
  ~GCNodeController();

  virtual UsedFlags mouseEvent(const MouseEvent &m);
  virtual xuint32 maxNumberOfPasses(xuint32 modelMaxPasses) const;
  virtual void paint(xuint32 pass) const;

Q_SIGNALS:
  void onContextMenu(QPoint);

private:
  Eks::AbstractRenderModel::Iterator *_iterator;

  Shift::Entity *_interactionEntity;
  xsize _interactionProperty;
  const GCAbstractNodeDelegate *_interactionDelegate;
  bool _connectingOutput;

  enum ControlMode
    {
    None,
    MovingEntity,
    ConnectingProperty,
    ConnectingEntity
    };
  ControlMode _controlMode;

  mutable xuint32 _connectionPass;
  };

#endif

#endif // GCNODECONTROLLER_H
