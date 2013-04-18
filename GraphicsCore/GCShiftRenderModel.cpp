#include "GCShiftRenderModel.h"
#include "shift/sentity.h"
#include "shift/Properties/scontaineriterators.h"
#include "shift/Properties/sattribute.inl"

#if 0

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

GCShiftRenderModel::GCShiftRenderModel(Shift::Entity *ent) : _entity(0)
  {
  setEntity(ent);
  }

GCShiftRenderModel::~GCShiftRenderModel()
  {
  setEntity(0);
  }

void GCShiftRenderModel::setEntity(Shift::Entity *entity)
  {
  if(_entity)
    {
    _entity->removeTreeObserver(this);

    xForeach(auto child, _entity->children.walker<Shift::Entity>())
      {
      child->removeConnectionObserver(this);
      }
    }

  _entity = entity;

  if(_entity)
    {
    _entity->addTreeObserver(this);

    xForeach(auto child, _entity->children.walker<Shift::Entity>())
      {
      child->addConnectionObserver(this);
      }
    }
  }

Eks::AbstractRenderModel::Iterator *GCShiftRenderModel::createIterator() const
  {
  return new GCShiftRenderModel::Iterator(this);
  }

void GCShiftRenderModel::resetIterator(Eks::AbstractRenderModel::Iterator *it) const
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

void GCShiftRenderModel::onConnectionChange(const Shift::Change *)
  {
  }

void GCShiftRenderModel::onTreeChange(const Shift::Change *c)
  {
  const Shift::PropertyContainer::TreeChange *t = c->castTo<Shift::PropertyContainer::TreeChange>();
  if(t)
    {
    if(t->before() && t->before()->isDescendedFrom(_entity))
      {
      const_cast<Shift::Entity*>(t->before()->entity())->removeConnectionObserver(this);
      }
    if(t->after() && t->after()->isDescendedFrom(_entity))
      {
      const_cast<Shift::Entity*>(t->property()->entity())->addConnectionObserver(this);
      }
    }
  }

#endif
