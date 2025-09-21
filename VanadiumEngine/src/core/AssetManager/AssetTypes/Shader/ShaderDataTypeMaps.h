#pragma once
#include "ShaderDataType.h"
#include <unordered_map>
#include <string>

inline const std::unordered_map<ShaderDataType, std::string> ShaderDataTypeToString = {
	{Void, "void"},
	{Bool, "bool"},
	{Int, "int"},
	{UInt, "uint"},
	{Float, "float"},
	{Double, "double"},

	{Bool2, "bvec2"}, {Bool3, "bvec3"}, {Bool4, "bvec4"},
	{Int2, "ivec2"}, {Int3, "ivec3"}, {Int4, "ivec4"},
	{UInt2, "uvec2"}, {UInt3, "uvec3"}, {UInt4, "uvec4"},
	{Float2, "vec2"}, {Float3, "vec3"}, {Float4, "vec4"},
	{Double2, "dvec2"}, {Double3, "dvec3"}, {Double4, "dvec4"},

	{Mat2, "mat2"}, {Mat2x3, "mat2x3"}, {Mat2x4, "mat2x4"},
	{Mat3, "mat3"}, {Mat3x2, "mat3x2"}, {Mat3x4, "mat3x4"},
	{Mat4, "mat4"}, {Mat4x2, "mat4x2"}, {Mat4x3, "mat4x3"},
	{DMat2, "dmat2"}, {DMat2x3, "dmat2x3"}, {DMat2x4, "dmat2x4"},
	{DMat3, "dmat3"}, {DMat3x2, "dmat3x2"}, {DMat3x4, "dmat3x4"},
	{DMat4, "dmat4"}, {DMat4x2, "dmat4x2"}, {DMat4x3, "dmat4x3"},

	{Sampler1D, "sampler1d"}, {Sampler2D, "sampler2d"}, {Sampler3D, "sampler3d"},
	{SamplerCube, "samplercube"}, {Sampler2DRect, "sampler2drect"},
	{Sampler1DShadow, "sampler1dshadow"}, {Sampler2DShadow, "sampler2dshadow"},
	{SamplerCubeShadow, "samplercubeshadow"}, {Sampler2DRectShadow, "sampler2drectshadow"},
	{Sampler1DArray, "sampler1darray"}, {Sampler2DArray, "sampler2darray"},
	{Sampler1DArrayShadow, "sampler1darrayshadow"}, {Sampler2DArrayShadow, "sampler2darrayshadow"},
	{SamplerBuffer, "samplerbuffer"}, {Sampler2DMS, "sampler2dms"}, {Sampler2DMSArray, "sampler2dmsarray"},
	{ISampler1D, "isampler1d"}, {ISampler2D, "isampler2d"}, {ISampler3D, "isampler3d"},
	{ISamplerCube, "isamplercube"}, {ISampler2DRect, "isampler2drect"},
	{ISampler1DArray, "isampler1darray"}, {ISampler2DArray, "isampler2darray"},
	{ISamplerBuffer, "isamplerbuffer"}, {ISampler2DMS, "isampler2dms"}, {ISampler2DMSArray, "isampler2dmsarray"},
	{USampler1D, "usampler1d"}, {USampler2D, "usampler2d"}, {USampler3D, "usampler3d"},
	{USamplerCube, "usamplercube"}, {USampler2DRect, "usampler2drect"},
	{USampler1DArray, "usampler1darray"}, {USampler2DArray, "usampler2darray"},
	{USamplerBuffer, "usamplerbuffer"}, {USampler2DMS, "usampler2dms"}, {USampler2DMSArray, "usampler2dmsarray"},

	{Image1D, "image1d"}, {Image2D, "image2d"}, {Image3D, "image3d"}, {ImageCube, "imagecube"}, {Image2DRect, "image2drect"},
	{Image1DArray, "image1darray"}, {Image2DArray, "image2darray"}, {ImageBuffer, "imagebuffer"}, {Image2DMS, "image2dms"}, {Image2DMSArray, "image2dmsarray"},
	{IImage1D, "iimage1d"}, {IImage2D, "iimage2d"}, {IImage3D, "iimage3d"}, {IImageCube, "iimagecube"}, {IImage2DRect, "iimage2drect"},
	{IImage1DArray, "iimage1darray"}, {IImage2DArray, "iimage2darray"}, {IImageBuffer, "iimagebuffer"}, {IImage2DMS, "iimage2dms"}, {IImage2DMSArray, "iimage2dmsarray"},
	{UImage1D, "uimage1d"}, {UImage2D, "uimage2d"}, {UImage3D, "uimage3d"}, {UImageCube, "uimagecube"}, {UImage2DRect, "uimage2drect"},
	{UImage1DArray, "uimage1darray"}, {UImage2DArray, "uimage2darray"}, {UImageBuffer, "uimagebuffer"}, {UImage2DMS, "uimage2dms"}, {UImage2DMSArray, "uimage2dmsarray"}
};

inline const std::unordered_map<std::string, ShaderDataType> StringToShaderDataType = {
	{"void", Void},
	{"bool", Bool},
	{"int", Int},
	{"uint", UInt},
	{"float", Float},
	{"double", Double},

	{"bvec2", Bool2}, {"bvec3", Bool3}, {"bvec4", Bool4},
	{"ivec2", Int2}, {"ivec3", Int3}, {"ivec4", Int4},
	{"uvec2", UInt2}, {"uvec3", UInt3}, {"uvec4", UInt4},
	{"vec2", Float2}, {"vec3", Float3}, {"vec4", Float4},
	{"dvec2", Double2}, {"dvec3", Double3}, {"dvec4", Double4},

	{"mat2", Mat2}, {"mat2x3", Mat2x3}, {"mat2x4", Mat2x4},
	{"mat3", Mat3}, {"mat3x2", Mat3x2}, {"mat3x4", Mat3x4},
	{"mat4", Mat4}, {"mat4x2", Mat4x2}, {"mat4x3", Mat4x3},
	{"dmat2", DMat2}, {"dmat2x3", DMat2x3}, {"dmat2x4", DMat2x4},
	{"dmat3", DMat3}, {"dmat3x2", DMat3x2}, {"dmat3x4", DMat3x4},
	{"dmat4", DMat4}, {"dmat4x2", DMat4x2}, {"dmat4x3", DMat4x3},

	{"sampler1d", Sampler1D}, {"sampler2d", Sampler2D}, {"sampler3d", Sampler3D},
	{"samplercube", SamplerCube}, {"sampler2drect", Sampler2DRect},
	{"sampler1dshadow", Sampler1DShadow}, {"sampler2dshadow", Sampler2DShadow},
	{"samplercubeshadow", SamplerCubeShadow}, {"sampler2drectshadow", Sampler2DRectShadow},
	{"sampler1darray", Sampler1DArray}, {"sampler2darray", Sampler2DArray},
	{"sampler1darrayshadow", Sampler1DArrayShadow}, {"sampler2darrayshadow", Sampler2DArrayShadow},
	{"samplerbuffer", SamplerBuffer}, {"sampler2dms", Sampler2DMS}, {"sampler2dmsarray", Sampler2DMSArray},
	{"isampler1d", ISampler1D}, {"isampler2d", ISampler2D}, {"isampler3d", ISampler3D},
	{"isamplercube", ISamplerCube}, {"isampler2drect", ISampler2DRect},
	{"isampler1darray", ISampler1DArray}, {"isampler2darray", ISampler2DArray},
	{"isamplerbuffer", ISamplerBuffer}, {"isampler2dms", ISampler2DMS}, {"isampler2dmsarray", ISampler2DMSArray},
	{"usampler1d", USampler1D}, {"usampler2d", USampler2D}, {"usampler3d", USampler3D},
	{"usamplercube", USamplerCube}, {"usampler2drect", USampler2DRect},
	{"usampler1darray", USampler1DArray}, {"usampler2darray", USampler2DArray},
	{"usamplerbuffer", USamplerBuffer}, {"usampler2dms", USampler2DMS}, {"usampler2dmsarray", USampler2DMSArray},

	{"image1d", Image1D}, {"image2d", Image2D}, {"image3d", Image3D}, {"imagecube", ImageCube}, {"image2drect", Image2DRect},
	{"image1darray", Image1DArray}, {"image2darray", Image2DArray}, {"imagebuffer", ImageBuffer}, {"image2dms", Image2DMS}, {"image2dmsarray", Image2DMSArray},
	{"iimage1d", IImage1D}, {"iimage2d", IImage2D}, {"iimage3d", IImage3D}, {"iimagecube", IImageCube}, {"iimage2drect", IImage2DRect},
	{"iimage1darray", IImage1DArray}, {"iimage2darray", IImage2DArray}, {"iimagebuffer", IImageBuffer}, {"iimage2dms", IImage2DMS}, {"iimage2dmsarray", IImage2DMSArray},
	{"uimage1d", UImage1D}, {"uimage2d", UImage2D}, {"uimage3d", UImage3D}, {"uimagecube", UImageCube}, {"uimage2drect", UImage2DRect},
	{"uimage1darray", UImage1DArray}, {"uimage2darray", UImage2DArray}, {"uimagebuffer", UImageBuffer}, {"uimage2dms", UImage2DMS}, {"uimage2dmsarray", UImage2DMSArray}
};
