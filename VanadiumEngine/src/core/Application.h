#pragma once
#include <vector>
#include <memory>
#include "core/rendering/Window.h"
#include "core/rendering/Renderer.h"
#include "core/AssetManager/AssetManager.h"
#include "ApplicationLayer.h"

class Application
{
public:
	Application();
	~Application();
	static Application& Get() { return *Application::s_instance; }

	void Run();
	void Stop();

	template <typename TLayer>
		requires(std::is_base_of_v<ApplicationLayer, TLayer>)
	void PushLayer()
	{
		m_applicationLayers.push_back(std::make_unique<TLayer>());
	}

	Renderer& GetRenderer() { return m_renderer; };
	Window& GetWindow() { return m_window; };
	AssetManager& GetAssetManager() { return m_assetManager; }
private:
	static Application* s_instance;

	std::vector<std::unique_ptr<ApplicationLayer>> m_applicationLayers;
	bool m_running = true;
	Window m_window;
	Renderer m_renderer;
	AssetManager m_assetManager;
};