#include "pch.h"
#include "RectCollisionDebugLayer.h"
#include "core/Components/RectCollisionComponent.h"	
#include "core/Components/TransformComponent.h"	

RectCollisionDebugLayer::RectCollisionDebugLayer()
	: shader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/pure_color.shader")->CreateShader().value()), vao(Util::SquareVertexArray())
{
}

void RectCollisionDebugLayer::OnRender(double dt)
{

	EntityComponentSystem& ECS = *Application::Get().GetECS();

	ComponentStore<RectCollisionComponent>& store = *ECS.GetComponentStore<RectCollisionComponent>();

	UnorderedVector<RectCollisionComponent>& colliders = store.GetComponents();

	if (colliders.size() == 0)
		return;


	unsigned int loc = shader.GlShader().GetUniformLocation("u_color");
	unsigned int loc2 = shader.GlShader().GetUniformLocation("u_model");


	shader.GlShader().Use();
	vao.Bind();
	for (int i = 0; i < colliders.size(); i++)
	{
		RectCollisionComponent& r = colliders[i];
		TransformComponent& t = *r.GetComponent<TransformComponent>();

		float width = r.Rect.End.x - r.Rect.Start.x;
		float height = r.Rect.End.y - r.Rect.Start.y;
		glm::mat4 a = glm::scale(t.ModelMatrix(), glm::vec3(height, width, 1.0));
		GL_CHECK(glUniformMatrix4fv(loc2, 1, GL_FALSE, glm::value_ptr(a)));

		if (r.Collisions.size() > 0)
		{
			GL_CHECK(glUniform4f(loc, 1, 0, 0, 0.5));
		}
		else
		{
			GL_CHECK(glUniform4f(loc, 0, 1, 0, 0.5));
		}

		GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
	}

}
