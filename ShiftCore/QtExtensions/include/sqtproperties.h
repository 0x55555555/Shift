#ifndef SQTPROPERTIES_H
#define SQTPROPERTIES_H

#include "shift/sglobal.h"
#include "shift/Properties/sdata.h"
#include "shift/Utilities/smetatype.h"
#include "shift/Serialisation/sattributeio.h"
#include "shift/TypeInformation/spropertyinstanceinformation.h"
#include "QtCore/QByteArray"
#include "QtCore/QUuid"

SHIFT_EXPORT Eks::String::IStream &operator>>(Eks::String::IStream &str, const QUuid &u);

namespace Shift
{

namespace detail
{
SHIFT_EXPORT void assignTo(const Attribute *f, Data<QUuid> *to);
}

template <> class SHIFT_EXPORT TypedSerialisationValue<QUuid> :  public SerialisationValue
  {
public:
  TypedSerialisationValue(const QUuid *t);

  bool hasUtf8() const X_OVERRIDE { return true; }
  bool hasBinary() const X_OVERRIDE { return false; }

  Eks::String asUtf8(Eks::AllocatorBase *a) const;

private:
  const QUuid *_val;
  };

namespace detail
{
class SHIFT_EXPORT UuidPropertyInstanceInformation : public EmbeddedPropertyInstanceInformation
  {
  typedef QUuid PODType;

public:
  UuidPropertyInstanceInformation()
    {
    }
  void initiateAttribute(Attribute *propertyToInitiate, AttributeInitialiserHelper *) const X_OVERRIDE;

  QUuid defaultValue() const
    {
    return QUuid();
    }
  };

template<> class DataEmbeddedInstanceInformation<Data<QUuid, AttributeData>>
    : public UuidPropertyInstanceInformation
  {
public:
  DataEmbeddedInstanceInformation()
    {
    }
  };

template<> class DataEmbeddedInstanceInformation<Data<QUuid, FullData>>
    : public UuidPropertyInstanceInformation
  {
public:
  DataEmbeddedInstanceInformation()
    {
    }
  };
}

S_DECLARE_METATYPE(Shift::Data<QUuid>, "uuid");

}

namespace std
{
template<> struct hash<QUuid>
  {
  typedef QUuid argument_type;
  typedef std::size_t result_type;

  result_type operator()(argument_type const& s) const;
  };
}

#endif // SQTPROPERTIES_H
