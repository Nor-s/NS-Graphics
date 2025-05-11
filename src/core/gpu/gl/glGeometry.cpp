#include "glGeometry.h"

namespace ns
{

const GlMeshBuffer* GlGeometry::getBuffer()
{
    return buffer_.get();
}

void GlGeometry::init(const GeometryInfo& info, const GlMeshBuffer::Layouts& layouts)
{
    auto& index = info.index;
    auto& vertex = info.vertex;

    geometry_.index = index;
    geometry_.vertex = vertex;

    buffer_.reset();
    buffer_ = std::make_unique<GlMeshBuffer>();
    buffer_->bind();
    buffer_->setVertexBuffer(vertex.size()*sizeof(float), vertex.data(), layouts);
    buffer_->setIndexBuffer(index.size()*sizeof(uint32_t), index.data());
    buffer_->unbind();
}

}	 // namespace ns
