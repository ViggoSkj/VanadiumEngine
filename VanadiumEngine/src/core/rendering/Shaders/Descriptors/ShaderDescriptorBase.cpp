#include "pch.h"
#include "ShaderDescriptorBase.h"

namespace Vanadium
{
    bool ShaderBaseDescriptor::UsesUniformObject(std::string name)
    {
        for (int i = 0; i < UniformObjects.size(); i++)
        {
            if (UniformObjects[i].Name == name)
                return true;
        }

        return false;
    }
}