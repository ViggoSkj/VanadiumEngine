#include "TestSquareLayer.h"

TestSquareLayer::TestSquareLayer()
{
	Application& application = Application::Get();

	AssetManager& assetManager = application.GetAssetManager();
	AssetRef playerRunning = assetManager.AddFileAsset(FileAsset(
		"res/images/player-running.png",
		FileAssetType::Image
	));

	m_texture.Use();
	std::shared_ptr<Texture> tex = assetManager.LoadTexture(playerRunning);
	m_texture.AssignTexture(tex.get());

	float vertices[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


	m_VAO.Bind();

	VertexBuffer vertexBuffer;
	vertexBuffer.SetVertecies(vertices, sizeof(vertices));
	vertexBuffer.Bind();

	IndexBuffer indexBuffer;
	indexBuffer.SetData(indices, sizeof(indices));
	indexBuffer.Bind();

	m_VAO.AssignVertexAttributes({
		{sizeof(float), GL_FLOAT, 3},
		{sizeof(float), GL_FLOAT, 2},
		});


	shader.LoadSource("res/shaders/texture.shader");
	m_samplerId = shader.GetUniformLocation("u_sampler");
	glActiveTexture(GL_TEXTURE0);
	m_texture.Bind();
}

void TestSquareLayer::OnRender(double dt)
{
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(m_samplerId, 0);
	m_texture.Bind();
	m_VAO.Bind();
	shader.Use();
	;	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
