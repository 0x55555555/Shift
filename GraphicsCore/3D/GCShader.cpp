#include "GCShader.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "XRenderer.h"
#include "shift/Properties/sdata.inl"
#include "shift/Changes/shandler.inl"

void computeData(GCShaderConstantData *d)
  {
  Eks::Renderer *r = d->renderer.value();
  if(!r)
    {
    return;
    }

  xAssertFail(); // ensure typeless walker.
  auto walker = d->walkerFrom(&d->runtimeData);
  auto it = ++walker.begin();
  auto end = walker.end();

  Eks::TemporaryAllocator alloc(d->temporaryAllocator());
  GCShaderBindableData::DataBlock data(&alloc);

  for(; it != end; ++it)
    {
    auto p = *it;
    const GCShaderBindableData *binder = p->findInterface<GCShaderBindableData>();

    xAssert(binder);
    binder->bindData(&data, p);
    }

  auto lock = d->runtimeData.computeLock();

  if(!lock->isValid())
    {
    Eks::Vector<Eks::ShaderConstantDataDescription> descs;

    it = ++walker.begin();
    for(; it != end; ++it)
      {
      auto p = *it;
      const GCShaderBindableData *binder = p->findInterface<GCShaderBindableData>();

      descs.resize(descs.size()+1);
      binder->getDescription(descs.back(), p);
      }

    Eks::ShaderConstantData::delayedCreate(*lock.data(), r, descs.data(), descs.size(), data.data());
    }
  else
    {
    lock->update(data.data());
    }
  }

S_IMPLEMENT_TYPED_POINTER_TYPE(GCShaderConstantDataPointer, GraphicsCore)

S_IMPLEMENT_PROPERTY(GCShaderConstantData, GraphicsCore)

void GCShaderConstantData::createTypeInformation(
    Shift::PropertyInformationTyped<GCShaderConstantData> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto rend = childBlock.add(&GCShaderConstantData::renderer, "renderer");

    auto rtInfo = childBlock.add(&GCShaderConstantData::runtimeData, "runtimeData");

    rtInfo->setCompute<computeData>();
    rend->setAffects(data, rtInfo);
    }
  }


S_IMPLEMENT_PROPERTY(GCShader, GraphicsCore)

void GCShader::createTypeInformation(Shift::PropertyInformationTyped<GCShader> *info,
                                     const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto rtInfo = childBlock.add(&GCShader::runtimeShader, "runtimeShader");
    rtInfo->setCompute<setupShaderRuntime>();

    auto rtInfoCore = childBlock.add(&GCShader::runtimeShaderCore, "runtimeShaderCore");
    rtInfoCore->setAffects(data, rtInfo);

    auto r = childBlock.add(&GCShader::renderer, "renderer");
    r->setAffects(data, rtInfoCore);
    }
  }

void GCShader::setupShaderRuntime(GCShader *shader)
  {
  GCRuntimeShaderInstance::ComputeLock lock(&shader->runtimeShader);

  Eks::Renderer *r = shader->renderer.value();
  if(!r)
    {
    return;
    }

  shader->resources.clear();
  shader->constantDatas.clear();

  lock.data()->instance = (Eks::Shader*)&shader->runtimeShaderCore();
  xForeach(auto p, shader->walkerFrom((Property*)&shader->runtimeShaderCore))
    {
    const GCShaderBindableResource *binder = p->findInterface<GCShaderBindableResource>();
    if(binder)
      {
      binder->bindResource(&shader->constantDatas, &shader->resources, p);
      }
    }
  }

void GCShader::bind(Eks::Renderer *r) const
  {
  Eks::Shader *s = runtimeShader().instance;
  r->setShader(s, &_layout);

  s->setShaderConstantDatas(0, constantDatas.size(), constantDatas.data());
  s->setShaderResources(0, resources.size(), resources.data());
  }


S_IMPLEMENT_ABSTRACT_PROPERTY(GCStaticShader, GraphicsCore)

void GCStaticShader::createTypeInformation(Shift::PropertyInformationTyped<GCStaticShader> *info,
                                     const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto rtInfoCore = childBlock.overrideChild(&GCShader::runtimeShaderCore);
    rtInfoCore->setCompute<computeShaderRuntime>();
    }
  }

void GCStaticShader::computeShaderRuntime(GCStaticShader *shader)
  {
  GCRuntimeShader::ComputeLock lock(&shader->runtimeShaderCore);

  Eks::Renderer *r = shader->renderer.value();
  if(!r)
    {
    return;
    }

  GCShaderInterface::Shader shaderStruct =
    {
    lock.data(),
    &shader->fragment,
    &shader->vertex,
    &shader->_layout
    };

  GCShaderInterface *ifc = shader->findInterface<GCShaderInterface>();
  xAssert(ifc);
  if(!ifc->initShader(
       shader,
       r,
       &shaderStruct))
    {
    xAssertFail();
    return;
    }
  }

S_IMPLEMENT_TYPED_POINTER_TYPE(GCShaderPointer, GraphicsCore)
