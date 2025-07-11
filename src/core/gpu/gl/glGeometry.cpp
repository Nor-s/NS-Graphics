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
	auto& instancingVerts = info.instancingVertex;

	instancingLayout_ = instancingLayout;

	buffer_.reset();
	buffer_ = std::make_unique<GlMeshBuffer>();
	buffer_->bind();
	buffer_->setVertexBuffer(vertex.size() * sizeof(float), vertex.data(), layouts);
	if(instancingLayout_.size() != 0)
	{
		assert(instancingVerts.size() == instancingLayout.size());
		for(int i = 0; i < instancingVerts.size() ; i++)
		{
			buffer_->setVertexInstancingBuffer(i, instancingVerts[i].size()*sizeof(ns::Vec4), instancingVerts[i].data(), instancingLayout_[i]);
		}
	}
	buffer_->setIndexBuffer(index.size() * sizeof(uint32_t), index.data());
	buffer_->unbind();
}

void GlGeometry::updateInstancingBuffer(int idx) 
{
	auto& instancingVertex = geometry_.instancingVertex;
	buffer_->bind();
	if(!buffer_->isInstancing())
	{
		buffer_->setVertexInstancingBuffer(idx, instancingVertex[idx].size()*sizeof(ns::Vec4), instancingVertex[idx].data(), instancingLayout_[idx]);
	}
	else 
	{
		buffer_->updateVertexInstancingBuffer(idx, instancingVertex[idx].size()*sizeof(ns::Vec4), instancingVertex[idx].data());
	}
}

}	 // namespace ns
