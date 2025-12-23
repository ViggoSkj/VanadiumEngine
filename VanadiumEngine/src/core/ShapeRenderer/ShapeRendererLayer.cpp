#include "pch.h"
#include "Rendering.h"
#include "ShapeRendererLayer.h"
#include "ShapeRenderer.h"
#include "AssetManager.h"
#include "core/Debug/Log.h"

ShapeRendererLayer::ShapeRendererLayer()
	: m_squareShader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/shapes/rect.shader")->CreateShader().value()),
	m_arrowShader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/shapes/arrow.shader")->CreateShader().value())
{
	RenderingManager& man = *Application::Get().GetRenderingManager();
	UniformObjectDescriptor matricesDescriptor = m_squareShader.Descriptor().FindUniformObjectDescriptor("Matrices");

	m_squareShader.ReportUniformObject(*man.FindUniformObject("Matrices").value());
	m_arrowShader.ReportUniformObject(*man.FindUniformObject("Matrices").value());
}

void ShapeRendererLayer::OnRender(double dt)
{
	float* squareVertices = Util::RectVertices(1.0, 1.0, true, false);

	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	VertexArray VAO;
	VAO.Bind();

	VertexBuffer VBO;
	VBO.SetVertecies(squareVertices, sizeof(float) * 4 * 3, GL_STATIC_DRAW);
	VBO.Bind();

	IndexBuffer IBO;
	IBO.SetData(indices, 3 * 2);
	IBO.Bind();

	VAO.AssignVertexAttributes({
		{sizeof(float), GL_FLOAT, 3},
		});

	std::optional<ShapeDrawCall> oCall;
	while ((oCall = ShapeRenderer::Get()->PopDrawCall()).has_value())
	{
		ShapeDrawCall Call = oCall.value();

		switch (Call.ShapeBuffer)
		{
		case ShapeBuffers::RectBuffer:
		{
			RectShape Shape = ShapeRenderer::Get()->PopRectShape();
			m_squareShader.GlShader().Use();
			u32 loc = m_squareShader.GlShader().GetUniformLocation("u_color");
			u32 locModel = m_squareShader.GlShader().GetUniformLocation("u_model");

			glm::mat4 mat = glm::identity<glm::mat4>();
			mat = glm::translate(mat, glm::vec3(Shape.Center, 0.0));
			mat = glm::scale(mat, glm::vec3(Shape.Size, 0.0));
			mat = glm::rotate(mat, Shape.Rotation, glm::vec3(0, 0, 1));

			GL_CHECK(glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(mat)));

			GL_CHECK(glUniform4f(loc, Call.Color.r, Call.Color.g, Call.Color.b, Call.Color.a));
			break;
		}
		case ShapeBuffers::ArrowBuffer:
		{
			ArrowShape Shape = ShapeRenderer::Get()->PopArrowShape();
			m_arrowShader.GlShader().Use();
			u32 loc = m_arrowShader.GlShader().GetUniformLocation("u_color");
			u32 locModel = m_arrowShader.GlShader().GetUniformLocation("u_model");

			glm::mat4 mat = glm::identity<glm::mat4>();

			GL_CHECK(glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(mat)));

			GL_CHECK(glUniform4f(loc, Call.Color.r, Call.Color.g, Call.Color.b, Call.Color.a));
		}
		default:
			LogDebug("Invalid shape buffer.");

		}
		VAO.Bind();
		GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
	}
}