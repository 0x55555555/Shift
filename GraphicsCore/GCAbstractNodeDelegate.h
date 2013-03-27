#ifndef GCABSTRACTNODEDELEGATE_H
#define GCABSTRACTNODEDELEGATE_H

#include "GCGlobal.h"
#include "XAbstractDelegate.h"
#include "QSize"
#include "QRect"
#include "QStaticText"
#include "QFontMetrics"
#include "QHash"

#if 0

class QPoint;
namespace Shift
{
class Entity;
}

class GRAPHICSCORE_EXPORT GCAbstractNodeDelegate : public Eks::AbstractDelegate
  {
public:
  enum HitArea
    {
    None,
    NodeDull,
    NodeTranslatable,
    Input,
    NodeOutput,
    Output,
    MaxNodeParts
    };

  // should be implemented to determine which area is hit on the node.
  virtual HitArea hitTest(const QPoint &point, const void *ent, xsize &index) const = 0;
  virtual void move(const QPoint &delta, const void *ent) const = 0;
  virtual void drawConnection(Eks::AbstractCanvas *c, const void *ent, xsize prop, bool fromOutput, const QPoint &to) const = 0;
  };

class GRAPHICSCORE_EXPORT GCSimpleNodeDelegate : public GCAbstractNodeDelegate
  {
public:
  enum
    {
    ShadowPass,
    ConnectionPass,
    NodePass,
    MaxPasses
    };

  GCSimpleNodeDelegate();

  virtual void update(const Eks::AbstractCanvas *, const Eks::AbstractRenderModel::Iterator *, const Eks::AbstractRenderModel *) const;
  virtual void paint(xuint32 pass, Eks::AbstractCanvas *, const Eks::AbstractRenderModel::Iterator *, const Eks::AbstractRenderModel *) const;
  virtual xuint32 maxNumberOfPasses(Eks::AbstractCanvas *, const Eks::AbstractRenderModel::Iterator *, const Eks::AbstractRenderModel *) const { return MaxPasses; }
  virtual HitArea hitTest(const QPoint &point, const void *ent, xsize &index) const;
  virtual void move(const QPoint &delta, const void *ent) const;
  virtual void drawConnection(Eks::AbstractCanvas *c, const void *ent, xsize prop, bool fromOutput, const QPoint &to) const;

  struct RenderData
    {
    QPoint position;
    QSize size;
    QRect titleBounds;
    QStaticText title;

    QPoint entOutputPos;
    xuint32 entOutputRadius;

    struct PropertyData
      {
      QStaticText text;
      QPoint position;
      QSize renderSize;
      bool onRight;

      QVector<PropertyData> childProperties;
      };

    QVector<PropertyData> properties;
    };
  mutable QHash<const void *, RenderData> _renderData;
  void updateRenderData(const Shift::Entity *ent) const;
  void ensureRenderData(const Shift::Entity *ent) const;

private:
  void preSetupProperty(const QFont& font, RenderData::PropertyData& data, const Shift::Property *prop, int yOffset) const;
  void postSetupProperty(const QFont& font, RenderData::PropertyData& data, const Shift::Property *prop, int minX, int maxWidth) const;

  void paintProperties(QPainter *ptr, QPoint nodePos, const QVector<RenderData::PropertyData> &) const;

  QFont _titleFnt;
  QFontMetrics _titleFntMetrics;

  QFont _propFnt;
  QFontMetrics _propFntMetrics;
  };

#endif

#endif // GCABSTRACTNODEDELEGATE_H
