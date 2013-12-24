#include "shift/TypeInformation/spropertytraits.h"
#include "shift/TypeInformation/spropertyinstanceinformation.h"
#include "shift/Properties/scontainer.h"
#include "shift/Properties/scontainer.inl"
#include "shift/Properties/scontaineriterators.h"
#include "shift/Serialisation/sloader.h"
#include "shift/Serialisation/sattributeio.h"
#include "Utilities/XEventLogger.h"
#include "Memory/XTemporaryAllocator.h"

namespace Shift
{

namespace detail
{

void PropertyBaseTraits::assign(const Attribute *, Attribute *)
  {
  }

void PropertyBaseTraits::save(const Attribute *p, AttributeSaver &l)
  {
  save(p, l, true);
  }

void PropertyBaseTraits::save(const Attribute *p, AttributeSaver &l, bool writeInput)
  {
  SProfileFunction

  Eks::TemporaryAllocator alloc(p->temporaryAllocator());

  bool dyn(p->isDynamic());
  if(dyn)
    {
    const PropertyInstanceInformation *instInfo = p->baseInstanceInformation();

    if(!instInfo->isDefaultMode())
      {
      const Eks::String &mode = instInfo->modeString();

      l.write(l.modeSymbol(), mode);
      }
    }

  if(const Property* prop = p->castTo<Property>())
    {
    if(writeInput && prop->input())
      {
      Eks::String path = prop->input()->path(p, &alloc);

      l.write(l.inputSymbol(), path);
      }
    }
  }

Attribute *PropertyBaseTraits::load(Container */* parent */, AttributeLoader &)
  {
  class Initialiser : public PropertyInstanceInformationInitialiser
    {
  public:
    //Initialiser() : affects(0) { }
    void initialise(PropertyInstanceInformation *inst)
      {
      //inst->setAffects(affects);
      inst->setModeString(mode);
      }

    //xsize *affects;
    QString mode;
    };

  SProfileFunction

  Initialiser initialiser;

  xAssertFail();
  /*
  const auto data = l.currentData();

  l.beginAttribute("mode");
  readValue(l, initialiser.mode);
  l.endAttribute("mode");

  Attribute *attr = 0;
  if(data->dynamic != 0)
    {
    const PropertyInformation *type = data->type;
    xAssert(type);

    attr = parent->addAttribute(type, X_UINT8_SENTINEL, data->name, &initialiser);
    xAssert(attr);
    }
  else
    {
    attr = data->existing;
    xAssert(attr);
    }

  if(Property *prop = attr->castTo<Property>())
    {
    l.beginAttribute("input");
    Loader::InputString input;
    readValue(l, input);
    l.endAttribute("input");

    if(!input.isEmpty())
      {
      l.resolveInputAfterLoad(prop, input);
      }
    }

  return attr;
    */
  return nullptr;
  }

bool PropertyBaseTraits::shouldSaveValue(const Attribute *p)
  {
  if(const Property *prop = p->castTo<Property>())
    {
    if(prop->hasInput())
      {
      return false;
      }

    if(prop->isComputed())
      {
      return false;
      }
    }

  return true;
  }

bool PropertyBaseTraits::shouldSave(const Attribute *p)
  {
  if(p->isDynamic())
    {
    return true;
    }

  if(const Property *prop = p->castTo<Property>())
    {
    if(prop->hasInput())
      {
      xsize inputLocation = prop->embeddedBaseInstanceInformation()->defaultInput();
      if(inputLocation != 0)
        {
        const xuint8 *inputPropertyData = (xuint8*)p + inputLocation;

        const Property *inputProperty = (Property*)inputPropertyData;
        if(inputProperty != prop->input())
          {
          return true;
          }
        }
      else
        {
        return true;
        }
      }
    }

  const PropertyInformation *info = p->typeInformation();
  if(info->functions().shouldSaveValue(p))
    {
    return true;
    }

  return false;
  }


void PropertyContainerTraits::assign(const Attribute *f, Attribute *t)
  {
  SProfileFunction
  const Container *from = f->uncheckedCastTo<Container>();
  Container *to = t->uncheckedCastTo<Container>();

  if(from->containedProperties() == to->containedProperties())
    {
    xuint8 index = 0;
    auto tChildIt = to->walker().begin();
    xForeach(auto fChild, from->walker())
      {
      auto tChild = *tChildIt;

      if(!tChild || tChild->staticTypeInformation() != fChild->staticTypeInformation())
        {
        xAssert(tChild->isDynamic());
        if(tChild)
          {
          to->removeAttribute(tChild);
          }

        tChild = to->addAttribute(fChild->staticTypeInformation(), index);
        }

      tChild->assign(fChild);

      ++tChildIt;
      ++index;
      }
    }
  }

bool PropertyContainerTraits::shouldSaveValue(const Attribute *p)
  {
  const Container *ptr = p->uncheckedCastTo<Container>();
  if(ptr->containedProperties() < ptr->size())
    {
    return true;
    }

  xForeach(auto p, ptr->walker())
    {
    const PropertyInformation *info = p->typeInformation();
    if(info->functions().shouldSave(p))
      {
      return true;
      }
    }

  return false;
  }

}

}
