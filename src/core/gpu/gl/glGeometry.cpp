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

	instancingLayout_ = instancingLayout;

	buffer_.reset();
	buffer_ = std::make_unique<GlMeshBuffer>();
	buffer_->bind();
	buffer_->setVertexBuffer(vertex.size() * sizeof(float), vertex.data(), layouts);
	buffer_->setIndexBuffer(index.size() * sizeof(uint32_t), index.data());
	buffer_->unbind();
}

void GlGeometry::updateInstancingBuffer(int idx, size_t size, void* data) 
{
	assert(instancingLayout_.size() > idx && instancingLayout_[idx].count > 0) ;

	auto beforeInstanceCount = instancingLayout_[idx].instancingCount;
	auto& instancingCountRef = instancingLayout_[idx].instancingCount;

	instancingCountRef = size / (instancingLayout_[idx].count * sizeof(ns::Vec4));

	buffer_->bind();
	if(!buffer_->isInstancing(idx) || beforeInstanceCount != instancingCountRef)
	{
		buffer_->setVertexInstancingBuffer(idx, size, data, instancingLayout_[idx]);
	}
	else 
	{
		buffer_->updateVertexInstancingBuffer(idx, size, data);
	}
	buffer_->unbind();
}

}	 // namespace ns
