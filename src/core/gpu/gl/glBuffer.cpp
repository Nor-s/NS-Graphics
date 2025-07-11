#include "glBuffer.h"

namespace ns
{
GlMeshBuffer::GlMeshBuffer()
{
    vao_ = 0;
    GLCHECK(glGenVertexArrays(1, &vao_));
}
GlMeshBuffer::~GlMeshBuffer()
{
    if (vao_)
    {
        GLCHECK(glDeleteVertexArrays(1, &vao_));
        vao_ = 0;
    }
}

void GlMeshBuffer::bind()
{
    glBindVertexArray(vao_);
    staticVbo_.bind();
    ebo_.bind();
}

void GlMeshBuffer::unbind() const
{
    glBindVertexArray(0);
    staticVbo_.unbind();
    ebo_.unbind();
}
void GlMeshBuffer::setVertexBuffer(size_t size, const void* data, const Layouts& layouts)
{
    if(size == 0) return;
    staticVbo_.updateBufferData(size, data);
    for(auto& layout: layouts)
    {
        GLCHECK(glEnableVertexAttribArray(layout.index));
        GLCHECK(glVertexAttribPointer(layout.index,layout.size,GL_FLOAT,GL_FALSE,layout.stride,reinterpret_cast<void*>(layout.offset)));
    }
}

void GlMeshBuffer::setVertexInstancingBuffer(size_t size, const void* data, const InstancingLayouts& layouts)
{
    if(size == 0) return;

    instancingVbo_.bind();
    instancingVbo_.updateBufferData(size, data);

    size_t unitSize = sizeof(ns::Vec4);
    size_t stride = layouts.count * unitSize;

    for(int i = 0; i < layouts.count; i++)
    {
        int index = layouts.startIndex + i;
        GLCHECK(glEnableVertexAttribArray(index));
        GLCHECK(glVertexAttribPointer(index, 4, GL_FLOAT,GL_FALSE, stride, reinterpret_cast<void*>(i*unitSize)));
        GLCHECK(glVertexAttribDivisor(index, 1));
    }
}

void GlMeshBuffer::updateVertexInstancingBuffer(size_t size, const void* data)
{
    if(size != 0 && data == nullptr) return;

    instancingVbo_.bind();
    instancingVbo_.subBufferData(size, data);
}

void GlMeshBuffer::setIndexBuffer(size_t size, const void* data)
{
    if(size == 0) return;
    ebo_.updateBufferData(size, data);
}

}	 // namespace ns