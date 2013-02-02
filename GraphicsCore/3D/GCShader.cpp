#include "GCShader.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "XRenderer.h"
#include "shift/Changes/shandler.inl"

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

  GCShaderBindableData::DataBlock data;

  shader->resources.clear();

  lock.data()->instance = (Eks::Shader*)&shader->runtimeShaderCore();
  xForeach(auto p, shader->walkerFrom((Property*)&shader->runtimeShaderCore))
    {
    const GCShaderBindableData *binder = p->interface<GCShaderBindableData>();
    if(binder)
      {
      binder->bindData(&data, &shader->resources, p);
      }
    }

  if(!shader->constantData.isValid())
    {
    Eks::ShaderConstantData::delayedCreate(shader->constantData, r, data.size(), data.data());
    }
  else
    {
    shader->constantData.update(data.data());
    }
  }

void GCShader::bind(Eks::Renderer *r) const
  {
  Eks::Shader *s = runtimeShader().instance;
  r->setShader(s, &layout);

  s->setFragmentShaderConstantData(0, &constantData);
  s->setVertexShaderConstantData(0, &constantData);

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
  if(!r)
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
  if(!shader->embeddedInstanceInformation()->initVertexShader(
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
  if(!shader->embeddedInstanceInformation()->initFragmentShader(shader, r, &shader->fragment))
    {
    xAssertFail();
    return;
    }

  lock.data()->~Shader();
  new(lock.data()) Eks::Shader(r, &shader->vertex, &shader->fragment);
  }

S_IMPLEMENT_TYPED_POINTER_TYPE(GCShaderPointer, GraphicsCore)
