#pragma once
#include "core/ErrorValue/ErrorValue.h"
#include "core/Rendering/Primitives/Color.h"
#include "core/Util/Array2D.h"

namespace Vanadium
{
	enum ImageFileFormat
	{
		Png
	};

	class Texture
	{
	public:
		Texture() {};
		virtual unsigned int GetWidth() const { return 0; };
		virtual unsigned int GetHeight() const { return 0; };
		virtual void* GetData() const { return nullptr; };
	};

	class TextureRGBA : public Texture
	{
	public:
		static std::expected<TextureRGBA, ErrorValue> LoadFromFile(std::filesystem::path path, ImageFileFormat format);

		TextureRGBA() = default;

		void Copy(TextureRGBA& destination) const;

		u32 GetWidth() const override { return m_data.GetWidth(); }
		u32 GetHeight() const override { return m_data.GetHeight(); }

		void* GetData() const override { return (void*) m_data.Data(); }

	private:
		Array2D<ColorRGBA> m_data;
	};
}