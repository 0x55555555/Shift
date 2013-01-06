#ifndef GCSHIFTRENDERMODEL_H
#define GCSHIFTRENDERMODEL_H

#include "XAbstractRenderModel.h"
#include "GCGlobal.h"
#include "shift/Changes/sobserver.h"
#include "shift/Utilities/sentityweakpointer.h"
#include "shift/Utilities/siterator.h"

namespace Shift
{
class Entity;
}

class GRAPHICSCORE_EXPORT GCShiftRenderModel
    : public Eks::AbstractRenderModel,
    Shift::ConnectionObserver,
    Shift::TreeObserver
  {
XProperties:
  XROProperty(Shift::EntityWeakPointer, entity);

public:
  class GRAPHICSCORE_EXPORT Iterator : public Eks::AbstractRenderModel::Iterator
    {
  XProperties:
    XROProperty(const GCShiftRenderModel *, model);
    XROProperty(Shift::Property *, property);

  public:
    Iterator(const GCShiftRenderModel *model);
    virtual bool next();

    Shift::Entity *entity() const
      {
      if(property())
        {
        Shift::Entity *ent = property()->castTo<Shift::Entity>();
        xAssert(ent);
        return ent;
        }
      return 0;
      }

  protected:
    void reset();
    void setProperty(Shift::Property *p) { _property = p; }

    friend class GCShiftRenderModel;
    };

  GCShiftRenderModel(Shift::Entity *ent=0);
  ~GCShiftRenderModel();

  void setEntity(Shift::Entity *entity);

  virtual Eks::AbstractRenderModel::Iterator *createIterator() const;

  virtual void resetIterator(Eks::AbstractRenderModel::Iterator *) const;

  void actOnChanges();
  void onConnectionChange(const Shift::Change *);
  void onTreeChange(const Shift::Change *);
  };

#endif // GCSHIFTRENDERMODEL_H
