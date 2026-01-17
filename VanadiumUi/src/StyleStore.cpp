#include "StyleStore.h"

Vanadium::Handle<Style> StyleStore::GetClassStyleHandle(u64 stringHash)
{
    
}

Style* StyleStore::GetStyleDefinition(Vanadium::Handle<Style> handle)
{
    return m_styles.Get(handle);
}
