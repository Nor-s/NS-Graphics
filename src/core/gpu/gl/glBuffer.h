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
        GLCHECK(glGenBuffers(1, &id_));
        assert(id_ != 0);
    }
	~GlBuffer()
    {
        if(id_)
        {
            GLCHECK(glDeleteBuffers(1, &id_));
        }
    }

    void bind() const
    {
        GLCHECK(glBindBuffer(static_cast<GLuint>(TARGET_), id_));
    }
	void updateBufferData( uint32_t size, const void* data)
    {
        GLCHECK(glBufferData(static_cast<GLuint>(TARGET_), size, data, static_cast<GLuint>(USAGE_)));
    }
    void unbind() const
    {
        GLCHECK(glBindBuffer(static_cast<GLuint>(TARGET_), 0));
    }

private:
	GLuint id_;
};

// todo: add noncopyable, move functions 
class GlMeshBuffer
{
public:
    using VertexBuffer = GlBuffer<GpuBufferTarget::ARRAY_BUFFER, GpuBufferUsage::STATIC>;
    using IndexBuffer = GlBuffer<GpuBufferTarget::ELEMENT_ARRAY_BUFFER, GpuBufferUsage::STATIC>;

public:
    GlMeshBuffer();
    ~GlMeshBuffer();

    void bind() const;
    void unbind() const;
    void setVertexBuffer(size_t size, const void* data, const Layouts& layouts);
    void setIndexBuffer(size_t size, const void* data);
    GLuint getVao()  const {return vao_;}

private:
    GLuint vao_;
    VertexBuffer vbo_;
    IndexBuffer ebo_;
};

}	 // namespace ns

#endif