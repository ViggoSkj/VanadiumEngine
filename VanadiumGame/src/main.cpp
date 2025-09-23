#include <iostream>
#include "core/Application.h"
#include "core/rendering/rendering.h"
#include "core/Shaders.h"
#include "TestSquareLayer.h"

int main()
{
    Application app;
	AssetManager man = app.GetAssetManager();

	AssetRef ref = man.LoadFileAsset<ShaderAsset>("res/shaders/texture.shader");
	ShaderAsset a = man.GetAsset<ShaderAsset>(ref);

	return 0;
}