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

void GlMeshBuffer::bind() const
{
    glBindVertexArray(vao_);
    vbo_.bind();
    ebo_.bind();
}

void GlMeshBuffer::unbind() const
{
    glBindVertexArray(0);
    vbo_.unbind();
    ebo_.unbind();
}
void GlMeshBuffer::setVertexBuffer(size_t size, const void* data, const Layouts& layouts)
{
    if(size == 0) return;
    vbo_.updateBufferData(size, data);
    for(auto& layout: layouts)
    {
        GLCHECK(glEnableVertexAttribArray(layout.index));
        GLCHECK(glVertexAttribPointer(layout.index,layout.size,GL_FLOAT,GL_FALSE,layout.stride,reinterpret_cast<void*>(layout.offset)));
    }
}

void GlMeshBuffer::setIndexBuffer(size_t size, const void* data)
{
    if(size == 0) return;
    ebo_.updateBufferData(size, data);
}

}	 // namespace ns