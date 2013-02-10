#include "GCShader.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "XRenderer.h"
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

  Eks::TemporaryAllocator alloc(Shift::TypeRegistry::temporaryAllocator());
  GCShaderBindableData::DataBlock data(&alloc);

  for(; it != end; ++it)
    {
    auto p = *it;
    const GCShaderBindableData *binder = p->interface<GCShaderBindableData>();

    xAssert(binder);
    binder->bindData(&data, p);
    }

  GCShaderRuntimeConstantData::ComputeLock l(&d->runtimeData);

  if(!l.data()->isValid())
    {
    Eks::ShaderConstantData::delayedCreate(*l.data(), r, data.size(), data.data());
    }
  else
    {
    l.data()->update(data.data());
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

    auto rtInfoCore = childBlock.add(&GCShader::runtimeShaderCore, "runtimeShaderCore");

    auto r = childBlock.add(&GCShader::renderer, "renderer");
    r->setAffects(data, rtInfoCore);

    childBlock.add(&GCShader::layoutDescription, "layoutDescription");

    auto rtInfo = childBlock.add(&GCShader::runtimeShader, "runtimeShader");
    rtInfo->setCompute<setupShaderRuntime>();
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
    const GCShaderBindableResource *binder = p->interface<GCShaderBindableResource>();
    if(binder)
      {
      binder->bindResource(&shader->constantDatas, &shader->resources, p);
      }
    }
  }

void GCShader::bind(Eks::Renderer *r) const
  {
  Eks::Shader *s = runtimeShader().instance;
  r->setShader(s, &layout);

  s->setFragmentShaderConstantDatas(0, constantDatas.size(), constantDatas.data());
  s->setVertexShaderConstantDatas(0, constantDatas.size(), constantDatas.data());

  s->setFragmentShaderResources(0, resources.size(), resources.data());
  s->setVertexShaderResources(0, resources.size(), resources.data());
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

  GCVertexLayout *gcLayout = shader->layoutDescription();
  if(!gcLayout)
    {
    return;
    }

  const GCVertexLayoutWrapper &layoutDesc = gcLayout->value();
  if(!layoutDesc.layout)
    {
    return;
    }

  shader->layout.~ShaderVertexLayout();
  new(&shader->layout) Eks::ShaderVertexLayout();

  shader->vertex.~ShaderVertexComponent();
  new(&shader->vertex) Eks::ShaderVertexComponent();

  GCShaderInterface *ifc = shader->interface<GCShaderInterface>();
  xAssert(ifc);
  if(!ifc->initVertexShader(
       shader,
       r,
       &shader->vertex,
       layoutDesc.layout,
       layoutDesc.layoutCount,
       &shader->layout))
    {
    xAssertFail();
    return;
    }

  shader->fragment.~ShaderFragmentComponent();
  new(&shader->fragment) Eks::ShaderFragmentComponent();

  if(!ifc->initFragmentShader(shader, r, &shader->fragment))
    {
    xAssertFail();
    return;
    }

  lock.data()->~Shader();
  new(lock.data()) Eks::Shader(r, &shader->vertex, &shader->fragment);
  }

S_IMPLEMENT_TYPED_POINTER_TYPE(GCShaderPointer, GraphicsCore)
