#include "UniformBinder.h"

unsigned int UniformBinder::BlockCount(GLenum block)
{
    int count;
    glGetIntegerv(block, &count);
    return count;
}

UniformBinder::UniformBinder(ShaderType shaderType, unsigned int count)
{
    for (int i = 0; i < count; i++)
    {
        m_bindingSlots.emplace_back(UniformBindingSlot(shaderType, count - i));
    }
}

UniformBindingSlot UniformBinder::LoneBindingSlot()
{
    UniformBindingSlot b = m_bindingSlots.back();
    m_bindingSlots.pop_back();
    return b;
}

void UniformBinder::ReturnBindingSlot(UniformBindingSlot bindingSlot)
{
    m_bindingSlots.push_back(bindingSlot);
}
