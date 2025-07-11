#include "glGeometry.h"

namespace ns
{

GlMeshBuffer* GlGeometry::getBuffer()
{
	return buffer_.get();
}

void GlGeometry::init(const GeometryInfo& info, const Layouts& layouts, const InstancingLayouts& instancingLayout)
{
	geometry_ = info;
	auto& index = info.index;
	auto& vertex = info.vertex;
	auto& instancingVertex = info.instancingVertex;

	instancingLayout_ = instancingLayout;

	buffer_.reset();
	buffer_ = std::make_unique<GlMeshBuffer>();
	buffer_->bind();
	buffer_->setVertexBuffer(vertex.size() * sizeof(float), vertex.data(), layouts);
	if(instancingLayout.count != 0)
	{
		buffer_->setVertexInstancingBuffer(instancingVertex.size()*sizeof(ns::Vec4), instancingVertex.data(), instancingLayout_);
	}
	buffer_->setIndexBuffer(index.size() * sizeof(uint32_t), index.data());
	buffer_->unbind();
}

void GlGeometry::updateInstancingBuffer() 
{
	auto& instancingVertex = geometry_.instancingVertex;
	buffer_->bind();
	if(!buffer_->isInstancing())
	{
		buffer_->setVertexInstancingBuffer(instancingVertex.size()*sizeof(ns::Vec4), instancingVertex.data(), instancingLayout_);
	}
	else 
	{
		buffer_->updateVertexInstancingBuffer(instancingVertex.size()*sizeof(ns::Vec4), instancingVertex.data());
	}
}

}	 // namespace ns
