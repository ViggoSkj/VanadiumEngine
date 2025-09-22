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

	{Sampler1D, "sampler1D"}, {Sampler2D, "sampler2D"}, {Sampler3D, "sampler3D"},
	{SamplerCube, "samplercube"}, {Sampler2DRect, "sampler2Drect"},
	{Sampler1DShadow, "sampler1Dshadow"}, {Sampler2DShadow, "sampler2Dshadow"},
	{SamplerCubeShadow, "samplercubeshadow"}, {Sampler2DRectShadow, "sampler2Drectshadow"},
	{Sampler1DArray, "sampler1Darray"}, {Sampler2DArray, "sampler2Darray"},
	{Sampler1DArrayShadow, "sampler1Darrayshadow"}, {Sampler2DArrayShadow, "sampler2Darrayshadow"},
	{SamplerBuffer, "samplerbuffer"}, {Sampler2DMS, "sampler2Dms"}, {Sampler2DMSArray, "sampler2Dmsarray"},
	{ISampler1D, "isampler1D"}, {ISampler2D, "isampler2D"}, {ISampler3D, "isampler3D"},
	{ISamplerCube, "isamplercube"}, {ISampler2DRect, "isampler2Drect"},
	{ISampler1DArray, "isampler1Darray"}, {ISampler2DArray, "isampler2Darray"},
	{ISamplerBuffer, "isamplerbuffer"}, {ISampler2DMS, "isampler2Dms"}, {ISampler2DMSArray, "isampler2Dmsarray"},
	{USampler1D, "usampler1D"}, {USampler2D, "usampler2D"}, {USampler3D, "usampler3D"},
	{USamplerCube, "usamplercube"}, {USampler2DRect, "usampler2Drect"},
	{USampler1DArray, "usampler1Darray"}, {USampler2DArray, "usampler2Darray"},
	{USamplerBuffer, "usamplerbuffer"}, {USampler2DMS, "usampler2Dms"}, {USampler2DMSArray, "usampler2Dmsarray"},

	{Image1D, "image1D"}, {Image2D, "image2D"}, {Image3D, "image3D"}, {ImageCube, "imagecube"}, {Image2DRect, "image2Drect"},
	{Image1DArray, "image1Darray"}, {Image2DArray, "image2Darray"}, {ImageBuffer, "imagebuffer"}, {Image2DMS, "image2Dms"}, {Image2DMSArray, "image2Dmsarray"},
	{IImage1D, "iimage1D"}, {IImage2D, "iimage2D"}, {IImage3D, "iimage3D"}, {IImageCube, "iimagecube"}, {IImage2DRect, "iimage2Drect"},
	{IImage1DArray, "iimage1Darray"}, {IImage2DArray, "iimage2Darray"}, {IImageBuffer, "iimagebuffer"}, {IImage2DMS, "iimage2Dms"}, {IImage2DMSArray, "iimage2Dmsarray"},
	{UImage1D, "uimage1D"}, {UImage2D, "uimage2D"}, {UImage3D, "uimage3D"}, {UImageCube, "uimagecube"}, {UImage2DRect, "uimage2Drect"},
	{UImage1DArray, "uimage1Darray"}, {UImage2DArray, "uimage2Darray"}, {UImageBuffer, "uimagebuffer"}, {UImage2DMS, "uimage2Dms"}, {UImage2DMSArray, "uimage2Dmsarray"}
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

	{"sampler1D", Sampler1D}, {"sampler2D", Sampler2D}, {"sampler3D", Sampler3D},
	{"samplercube", SamplerCube}, {"sampler2Drect", Sampler2DRect},
	{"sampler1Dshadow", Sampler1DShadow}, {"sampler2Dshadow", Sampler2DShadow},
	{"samplercubeshadow", SamplerCubeShadow}, {"sampler2Drectshadow", Sampler2DRectShadow},
	{"sampler1Darray", Sampler1DArray}, {"sampler2Darray", Sampler2DArray},
	{"sampler1Darrayshadow", Sampler1DArrayShadow}, {"sampler2Darrayshadow", Sampler2DArrayShadow},
	{"samplerbuffer", SamplerBuffer}, {"sampler2Dms", Sampler2DMS}, {"sampler2Dmsarray", Sampler2DMSArray},
	{"isampler1D", ISampler1D}, {"isampler2D", ISampler2D}, {"isampler3D", ISampler3D},
	{"isamplercube", ISamplerCube}, {"isampler2Drect", ISampler2DRect},
	{"isampler1Darray", ISampler1DArray}, {"isampler2Darray", ISampler2DArray},
	{"isamplerbuffer", ISamplerBuffer}, {"isampler2Dms", ISampler2DMS}, {"isampler2Dmsarray", ISampler2DMSArray},
	{"usampler1D", USampler1D}, {"usampler2D", USampler2D}, {"usampler3D", USampler3D},
	{"usamplercube", USamplerCube}, {"usampler2Drect", USampler2DRect},
	{"usampler1Darray", USampler1DArray}, {"usampler2Darray", USampler2DArray},
	{"usamplerbuffer", USamplerBuffer}, {"usampler2Dms", USampler2DMS}, {"usampler2Dmsarray", USampler2DMSArray},

	{"image1D", Image1D}, {"image2D", Image2D}, {"image3D", Image3D}, {"imagecube", ImageCube}, {"image2Drect", Image2DRect},
	{"image1Darray", Image1DArray}, {"image2Darray", Image2DArray}, {"imagebuffer", ImageBuffer}, {"image2Dms", Image2DMS}, {"image2Dmsarray", Image2DMSArray},
	{"iimage1D", IImage1D}, {"iimage2D", IImage2D}, {"iimage3D", IImage3D}, {"iimagecube", IImageCube}, {"iimage2Drect", IImage2DRect},
	{"iimage1Darray", IImage1DArray}, {"iimage2Darray", IImage2DArray}, {"iimagebuffer", IImageBuffer}, {"iimage2Dms", IImage2DMS}, {"iimage2Dmsarray", IImage2DMSArray},
	{"uimage1D", UImage1D}, {"uimage2D", UImage2D}, {"uimage3D", UImage3D}, {"uimagecube", UImageCube}, {"uimage2Drect", UImage2DRect},
	{"uimage1Darray", UImage1DArray}, {"uimage2Darray", UImage2DArray}, {"uimagebuffer", UImageBuffer}, {"uimage2Dms", UImage2DMS}, {"uimage2Dmsarray", UImage2DMSArray}
};
