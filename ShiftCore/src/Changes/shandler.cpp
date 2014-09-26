#include "shift/Changes/shandler.h"
#include "shift/sdatabase.h"
#include "shift/Properties/sattribute.inl"

namespace Shift
{

Handler::Handler(bool stateStorageEnabled)
  : _database(0),
    _revision(0),
    _blockLevel(0),
    _changeIncrease(1),
    _blockObservers(TypeRegistry::generalPurposeAllocator()),
    _done(TypeRegistry::generalPurposeAllocator()),
    _blockSize(TypeRegistry::generalPurposeAllocator()),
    _stateStorageEnabled(stateStorageEnabled)
  {
  }

Handler::~Handler()
  {
  clearChanges();
  }

void Handler::clearChanges()
  {
  clearUndo();
  }

void Handler::clearUndo()
  {
  xForeach(Change *ch, _done)
    {
    changeAllocator()->destroy(ch);
    }

  _done.clear();
  _done.squeeze();

  _blockSize.clear();
  _blockSize.squeeze();
  }

Handler *Handler::findHandler(Container *parent, Entity *prop)
  {
  Handler *handler = prop->findInterface<Handler>();
  if(handler)
    {
    handler->setDatabase(parent->database());
    xAssert(handler->database());
    return handler;
    }
  xAssert(parent->handler()->database());
  return parent->handler();
  }

Eks::AllocatorBase *Handler::changeAllocator()
  {
  return _database->persistantAllocator();
  }

Eks::TemporaryAllocatorCore *Handler::temporaryAllocator() const
  {
  return _database->temporaryAllocator();
  }

Eks::AllocatorBase *Handler::persistentBlockAllocator() const
  {
  return _database->persistantAllocator();
  }

Eks::AllocatorBase *Handler::generalPurposeAllocator() const
  {
  return TypeRegistry::generalPurposeAllocator();
  }

void Handler::beginBlock()
  {
  xAssert(_blockLevel != 0 || _blockChangeCount == 0);

  _blockLevel++;
  _blockSize << _done.size();
  }

void Handler::endBlock(bool cancel)
  {
  xAssert(_blockLevel > 0);
  _blockLevel--;

  xsize previousPoint = _blockSize.popBack();

  if(cancel)
    {
    undoTo(previousPoint);
    }

  // wrap everything into one inform block (ignore if no changes applied)
  if(_blockLevel == 0 && _blockChangeCount > 0)
    {
    onChangeComplete();
    }
  }

void Handler::undoTo(xsize p)
  {
  xAssert(p <= (xsize)_done.size());
  for(xptrdiff i = (_done.size()-1); i >= (xptrdiff)p; --i)
    {
    Change *c = _done[i];

    X_USED_FOR_ASSERTS(bool result =)
      c->unApply() && c->inform(true);
    xAssert(result);

    // todo dont need this here, when undo fully implemented.
    _done.popBack();
    --_revision;
    xAssert(_revision >= 0);
    }
  }

void Handler::onChangeComplete()
  {
  auto changeCount = _blockChangeCount;
  _blockChangeCount = 0;
  SProfileFunction
  std::sort(_blockObservers.begin(), _blockObservers.end());
  _blockObservers.erase(
    std::unique(_blockObservers.begin(), _blockObservers.end() ),
    _blockObservers.end());

  xForeach(Observer *obs, _blockObservers)
    {
    obs->actOnChanges();
    }
  _blockObservers.clear();

  if (changeCount != 0)
    {
    ++_revision;
    }
  }

RevisionHoldBlock::RevisionHoldBlock(Handler *h)
    : _handler(h),
      _old(_handler->revisionsEnabled())
  {
  _handler->setRevisionsEnabled(false);
  }

RevisionHoldBlock::~RevisionHoldBlock()
  {
  _handler->setRevisionsEnabled(_old);
  }

}
