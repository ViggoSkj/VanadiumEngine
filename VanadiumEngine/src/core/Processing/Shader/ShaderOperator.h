#include <vector>
#include <string>
#include <unordered_map>

enum ShaderOperator
{
	And,
	Or,
	Equal,
	_Last
};

inline std::vector<std::string> ShaderOperatorToString = {
	"&&",
	"||",
	"==",
};

inline std::unordered_map<std::string, ShaderOperator> StringToShaderOperator = {
	{ "&&", ShaderOperator::And },
	{ "||", ShaderOperator::Or },
	{ "==", ShaderOperator::Equal },
};