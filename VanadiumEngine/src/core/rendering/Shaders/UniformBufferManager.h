#pragma once
#include <vector>
#include "core/Shaders.h"

class UniformBufferManager
{
public:
	void ReportShaderSourceObject(ShaderDescriptor o);
	void ReportShader(ShaderBaseDescriptor shader);

	// optimize with hashmap or somthing
	void SetData(std::string objectName, std::string uniformName, void* uniformData);

private:
	void AddUniformObject(UniformObjectDescriptor& object);
	
	std::vector<UniformObjectDescriptor> m_objects;
	std::vector<GLUniformBuffer> m_buffers;
};