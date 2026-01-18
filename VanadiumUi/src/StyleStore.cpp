#include "StyleStore.h"

Vanadium::Handle<Style> StyleStore::GetClassStyleHandle(u64 stringHash)
{
    return m_styles.Create();
}

Style* StyleStore::GetStyleDefinition(Vanadium::Handle<Style> handle)
{
    return m_styles.Get(handle);
}
