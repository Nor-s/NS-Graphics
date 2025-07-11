#ifndef _NS_GRAPHICS_CORE_GPU_GL_GL_BUFFER_H_
#define _NS_GRAPHICS_CORE_GPU_GL_GL_BUFFER_H_

#include "glCommon.h"

namespace ns
{
enum class GpuBufferTarget : GLuint 
{
	ARRAY_BUFFER = GL_ARRAY_BUFFER,
	ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
	UNIFORM_BUFFER = GL_UNIFORM_BUFFER,
};
enum class GpuBufferUsage : GLuint 
{
	STATIC = GL_STATIC_DRAW,
    DYNAMIC= GL_DYNAMIC_DRAW,
};

// todo: add noncopyable, move functions 
template<GpuBufferTarget TARGET_, GpuBufferUsage USAGE_>
class GlBuffer
{
public:
	GlBuffer()
    {
        id_ = 0;
    }
	~GlBuffer()
    {
        if(id_ != 0)
        {
            GLCHECK(glDeleteBuffers(1, &id_));
        }
    }

    void bind()
    {
        if( id_ == 0)
        {
            GLCHECK(glGenBuffers(1, &id_));
            assert(id_ != 0);
        }
        GLCHECK(glBindBuffer(static_cast<GLuint>(TARGET_), id_));
    }
	void updateBufferData( uint32_t size, const void* data)
    {
        size_ = size;
        GLCHECK(glBufferData(static_cast<GLuint>(TARGET_), size, data, static_cast<GLuint>(USAGE_)));
    }
    void subBufferData(uint32_t size, const void* data)
    {
        if(size_ != size)
            updateBufferData(size, data);
        else
            GLCHECK(glBufferSubData(static_cast<GLuint>(TARGET_), 0, size, data));
    }
    void mapBufferData(uint32_t size, const void* data)
    {
        if(size_ != size)
        {
            updateBufferData(size, data);
        }
        else 
        {
            GLCHECK(void* ptr = glMapBufferRange(static_cast<GLuint>(TARGET_), 0, size, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
            memcpy(ptr, data, size);
            GLCHECK(glUnmapBuffer(static_cast<GLuint>(TARGET_)));
        }
    }
    void unbind() const
    {
        GLCHECK(glBindBuffer(static_cast<GLuint>(TARGET_), 0));
    }
    bool isValid()
    {
        return id_ != 0;
    }

private:
	GLuint id_=0;
    uint32_t size_ = 0;
};

// todo: add noncopyable, move functions 
class GlMeshBuffer
{
public:
    using DynamicVertexBuffer = GlBuffer<GpuBufferTarget::ARRAY_BUFFER, GpuBufferUsage::DYNAMIC>;
    using StaticVertexBuffer = GlBuffer<GpuBufferTarget::ARRAY_BUFFER, GpuBufferUsage::STATIC>;
    using IndexBuffer = GlBuffer<GpuBufferTarget::ELEMENT_ARRAY_BUFFER, GpuBufferUsage::STATIC>;

public:
    GlMeshBuffer();
    ~GlMeshBuffer();

    void bind();
    void unbind() const;
    void setVertexBuffer(size_t size, const void* data, const Layouts& layouts);
    void setVertexInstancingBuffer(size_t size, const void* data, const InstancingLayouts& layouts);
    void updateVertexInstancingBuffer(size_t size, const void* data);
    void setIndexBuffer(size_t size, const void* data);
    GLuint getVao()  const {return vao_;}

    bool isInstancing() 
    {
        return instancingVbo_.isValid();
    }

private:
    GLuint vao_;
    StaticVertexBuffer staticVbo_;
    DynamicVertexBuffer instancingVbo_;
    IndexBuffer ebo_;
};

}	 // namespace ns

#endif