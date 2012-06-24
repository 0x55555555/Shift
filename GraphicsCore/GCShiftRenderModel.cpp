#include "GCShiftRenderModel.h"
#include "sentity.h"

GCShiftRenderModel::Iterator::Iterator(const GCShiftRenderModel *m) : _model(m)
  {
  }

bool GCShiftRenderModel::Iterator::next()
  {
  xAssert(_model);


  setProperty(0);
  return property() != 0;
  }

void GCShiftRenderModel::Iterator::reset()
  {
  _property = 0;
  }

GCShiftRenderModel::GCShiftRenderModel(SEntity *ent) : _entity(0)
  {
  setEntity(ent);
  }

GCShiftRenderModel::~GCShiftRenderModel()
  {
  setEntity(0);
  }

void GCShiftRenderModel::setEntity(SEntity *entity)
  {
  if(_entity)
    {
    _entity->removeTreeObserver(this);

    xForeach(auto child, _entity->children.walker<SEntity>())
      {
      child->removeConnectionObserver(this);
      }
    }

  _entity = entity;

  if(_entity)
    {
    _entity->addTreeObserver(this);

    xForeach(auto child, _entity->children.walker<SEntity>())
      {
      child->addConnectionObserver(this);
      }
    }
  }

XAbstractRenderModel::Iterator *GCShiftRenderModel::createIterator() const
  {
  return new GCShiftRenderModel::Iterator(this);
  }

void GCShiftRenderModel::resetIterator(XAbstractRenderModel::Iterator *it) const
  {
  GCShiftRenderModel::Iterator *slIt = static_cast<GCShiftRenderModel::Iterator*>(it);
  slIt->reset();
  }

void GCShiftRenderModel::actOnChanges()
  {
  GCProfileFunction
  // only called if a change was triggered, so no need to test.
  update(TreeChange);
  }

void GCShiftRenderModel::onConnectionChange(const SChange *)
  {
  }

void GCShiftRenderModel::onTreeChange(const SChange *c)
  {
  const SPropertyContainer::TreeChange *t = c->castTo<SPropertyContainer::TreeChange>();
  if(t)
    {
    if(t->before() && t->before()->isDescendedFrom(_entity))
      {
      const_cast<SEntity*>(t->before()->entity())->removeConnectionObserver(this);
      }
    if(t->after() && t->after()->isDescendedFrom(_entity))
      {
      const_cast<SEntity*>(t->property()->entity())->addConnectionObserver(this);
      }
    }
  }
