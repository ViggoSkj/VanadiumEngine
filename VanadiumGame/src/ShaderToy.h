#pragma once
#include "Core.h"
#include "core/IO/FileWatcher.h"

class ShaderToySetup : public SceneSetupStep
{
public:
	ShaderToySetup(Scene* scene)
		: SceneSetupStep(scene) {
	}

	void Execute() override;
};

class ShaderToy : public LiveComponent
{
public:
	ShaderToy(Vanadium::ComponentData data);

	void UpdateShader();

	void OnRender(double dt) override;

	void OnFileChange();

	float Length = 1.0;
	float Thickness = 1.0;
private:
	std::filesystem::path m_shaderPath;
	Vanadium::FileWatcher m_fileWatcher;
	std::optional<Shader> m_shader;
	VertexArray m_VAO;
	std::shared_ptr<std::atomic<bool>> m_needUpdate;
};