#include "pch.h"
#include "Rendering.h"
#include "ShapeRendererLayer.h"
#include "ShapeRenderer.h"
#include "AssetManager.h"
#include "core/Debug/Log.h"
#include "core/Math.h"
#include "core/Rendering/Util.h"

namespace Vanadium
{
	using Vanadium::Application;
	using Vanadium::Detail::Rendering::RenderingManager;

	ShapeRendererLayer::ShapeRendererLayer()
		: m_squareShader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/shapes/rect.shader")->CreateShader().value()),
		m_arrowShader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/shapes/arrow.shader")->CreateShader().value()),
		m_cirlceShader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/shapes/circle.shader")->CreateShader().value())
	{
		RenderingManager& man = *Application::Get().GetRenderingManager();
		UniformObjectDescriptor matricesDescriptor = m_squareShader.Descriptor().FindUniformObjectDescriptor("Matrices");

		m_squareShader.TryUseUniformObject(*man.FindUniformObject("Matrices"), ShaderType::VertexShader);
		m_arrowShader.TryUseUniformObject(*man.FindUniformObject("Matrices"), ShaderType::VertexShader);
	}

	void ShapeRendererLayer::OnRender(double dt)
	{
		VertexArray VAO(Util::SquareVertexArray());

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
				mat = glm::rotate(mat, Shape.Rotation, glm::vec3(0, 0, 1));
				mat = glm::scale(mat, glm::vec3(Shape.Size, 0.0));

				GL_CHECK(glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(mat)));
				GL_CHECK(glUniform4f(loc, Call.Color.r, Call.Color.g, Call.Color.b, Call.Color.a));
				break;
			}
			case ShapeBuffers::ArrowBuffer:
			{
				ArrowShape Shape = ShapeRenderer::Get()->PopArrowShape();
				m_arrowShader.GlShader().Use();
				u32 loc = m_arrowShader.GlShader().GetUniformLocation("u_length");
				u32 locModel = m_arrowShader.GlShader().GetUniformLocation("u_model");

				Vector2 middle = Shape.Start + (Shape.End - Shape.Start) / 2.0f;
				float length = glm::length(Shape.End - Shape.Start);
				float angle = Math::Angle(Shape.End - Shape.Start) - Math::PI / 2.0;

				glm::mat4 mat = glm::identity<glm::mat4>();
				mat = glm::translate(mat, glm::vec3(middle, 0.0));
				mat = glm::rotate(mat, angle, glm::vec3(0, 0, 1));
				mat = glm::scale(mat, glm::vec3(1.0 / 25.0, length, 1.0));


				GL_CHECK(glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(mat)));
				GL_CHECK(glUniform1f(loc, length * 25.0));
				break;
			}
			case ShapeBuffers::CirlceBuffer:
			{
				CircleShape circle = ShapeRenderer::Get()->PopCircleShape();
				m_cirlceShader.GlShader().Use();
				u32 loc = m_cirlceShader.GlShader().GetUniformLocation("u_color");
				u32 locModel = m_cirlceShader.GlShader().GetUniformLocation("u_model");

				glm::mat4 mat = glm::identity<glm::mat4>();
				mat = glm::translate(mat, glm::vec3(circle.Center, 0.0));
				mat = glm::scale(mat, glm::vec3(circle.Radius, circle.Radius, 1.0));

				GL_CHECK(glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(mat)));
				GL_CHECK(glUniform4f(loc, Call.Color.r, Call.Color.g, Call.Color.b, Call.Color.a));
				break;
			}
			default:
				LogDebug("Invalid shape buffer.");

			}
			VAO.Bind();
			GL_CHECK(glDepthFunc(GL_ALWAYS));
			GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
			GL_CHECK(glDepthFunc(GL_LESS));
		}
	}
}