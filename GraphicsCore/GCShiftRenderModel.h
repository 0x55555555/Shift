#ifndef GCSHIFTRENDERMODEL_H
#define GCSHIFTRENDERMODEL_H

#include "XAbstractRenderModel.h"
#include "GCGlobal.h"
#include "sobserver.h"
#include "sentityweakpointer.h"
#include "siterator.h"

class Entity;

class GRAPHICSCORE_EXPORT GCShiftRenderModel : public XAbstractRenderModel, ConnectionObserver, TreeObserver
  {
XProperties:
  XROProperty(EntityWeakPointer, entity);

public:
  class GRAPHICSCORE_EXPORT Iterator : public XAbstractRenderModel::Iterator
    {
  XProperties:
    XROProperty(const GCShiftRenderModel *, model);
    XROProperty(Property *, property);

  public:
    Iterator(const GCShiftRenderModel *model);
    virtual bool next();

    Entity *entity() const
      {
      if(property())
        {
        Entity *ent = property()->castTo<Entity>();
        xAssert(ent);
        return ent;
        }
      return 0;
      }

  protected:
    void reset();
    void setProperty(Property *p) { _property = p; }

    friend class GCShiftRenderModel;
    };

  GCShiftRenderModel(Entity *ent=0);
  ~GCShiftRenderModel();

  void setEntity(Entity *entity);

  virtual XAbstractRenderModel::Iterator *createIterator() const;

  virtual void resetIterator(XAbstractRenderModel::Iterator *) const;

  void actOnChanges();
  void onConnectionChange(const Change *);
  void onTreeChange(const Change *);
  };

#endif // GCSHIFTRENDERMODEL_H
