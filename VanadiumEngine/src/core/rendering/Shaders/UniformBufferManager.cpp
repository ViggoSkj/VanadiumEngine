#include "UniformBufferManager.h"
#include "Shaders/ShaderDataType.h"
#include "Shaders/ShaderDataTypeMaps.h"

void UniformBufferManager::ReportShaderSourceObject(ShaderDescriptor o)
{
	ReportShader(o.FragmentShader);
	ReportShader(o.VertexShader);
}

void UniformBufferManager::ReportShader(ShaderBaseDescriptor shader)
{
	for (int i = 0; i < shader.UniformObjects.size(); i++)
	{
		AddUniformObject(shader.UniformObjects[i]);
	}
}

void UniformBufferManager::SetData(std::string objectName, std::string uniformName, void* data)
{
	int index = -1;

	for (int i = 0; i < m_objects.size(); i++)
		if (m_objects[i].Name == objectName)
			index = i;

	if (index == -1)
	{
		std::cout << "no such object (" + __LINE__ + ')';
		return;
	}

	GLUniformBuffer& buffer = m_buffers[index];
	UniformObjectDescriptor& object = m_objects[index];

	// get uniform offset;

	unsigned int offset = 0;
	for (int i = 0; i < object.Uniforms.size(); i++)
	{
		if (object.Uniforms[i].name == uniformName)
		{
			buffer.SetData(data, offset, ShaderDataTypeToSize.at(object.Uniforms[i].type));
			break;
		}
		offset += ShaderDataTypeToSize.at(object.Uniforms[i].type);
	}
}

void UniformBufferManager::AddUniformObject(UniformObjectDescriptor& object)
{
	// make sure its unique
	for (int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i].Name == object.Name)
			return;
	}

	m_objects.push_back(object);

	unsigned int size = 0;

	for (int i = 0; i < object.Uniforms.size(); i++)
	{
		size += ShaderDataTypeToSize.at(object.Uniforms[i].type);
	}

	m_buffers.emplace_back(size, GL_STREAM_DRAW);
}
