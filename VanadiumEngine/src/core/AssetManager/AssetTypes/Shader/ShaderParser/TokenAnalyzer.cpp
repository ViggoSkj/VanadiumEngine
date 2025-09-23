#include "TokenAnalyzer.h"
#include "../ShaderDataTypeMaps.h"
#include "../ShaderKeyword.h"

void TokenizedVertexShaderAnalyzer::GetVertexAttributes(TokenizedShader& shader, std::vector<VertexAttribute>& vertexAttributes)
{
	std::vector<Token> tokens = shader.Tokens();
	unsigned int cursor = -1;

	while ((cursor = shader.FindKeyword(ShaderKeyword::In, cursor + 1)) != -1)
	{
		Token typeToken = tokens[cursor + 1];
		Token locationToken = tokens[cursor - 2];

		unsigned int location = std::stoi(locationToken.Text);
		ShaderDataType type = StringToShaderDataType.at(typeToken.Text);

		vertexAttributes.push_back(VertexAttribute(type, location));
	}
}

void TokenizedVertexShaderAnalyzer::GetUniformObjects(TokenizedShader& shader, std::vector<UniformObjectDescriptor>& uniformObjects)
{
	unsigned int cursor = -1;
	const std::vector<Token> tokens = shader.Tokens();

	while ((cursor = shader.FindKeyword(ShaderKeyword::Uniform, cursor + 1)) != -1)
	{
		// is uniform object
		if (tokens[cursor + 1].Type == TokenType::Name)
		{
			std::vector<UniformDescriptor> uniforms;

			unsigned int cursor2 = shader.FindToken(TokenType::Type, cursor);
			unsigned int end = shader.FindToken(TokenType::FlowControl, cursor2);

			// get uniforms in object
			while (cursor2 < end)
			{
				Token typeToken = tokens[cursor2];
				Token nameToken = tokens[cursor2 + 1];
				uniforms.push_back(UniformDescriptor(nameToken.Text, StringToShaderDataType.at(typeToken.Text)));
				cursor2 = shader.FindToken(TokenType::Type, cursor2 + 1);
			}

			Token objectNameToken = tokens[cursor + 1];

			UniformObjectDescriptor obj;
			obj.name = objectNameToken.Text;
			obj.uniforms = std::move(uniforms);
			uniformObjects.push_back(obj);

			cursor += 1;
		}
	}
}

void TokenizedVertexShaderAnalyzer::GetUniforms(TokenizedShader& shader, std::vector<UniformDescriptor>& uniforms)
{
	unsigned int cursor = -1;
	const std::vector<Token> tokens = shader.Tokens();

	while ((cursor = shader.FindKeyword(ShaderKeyword::Uniform, cursor + 1)) != -1)
	{
		if (tokens[cursor + 1].Type == TokenType::Type)
		{
			Token typeToken = tokens[cursor + 1];
			Token nameToken = tokens[cursor + 2];
			uniforms.push_back(UniformDescriptor(nameToken.Text, StringToShaderDataType.at(typeToken.Text)));
		}
	}
}
