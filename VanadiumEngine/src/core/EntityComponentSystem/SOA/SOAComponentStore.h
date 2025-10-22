#pragma once
#include "SOAComponentBlueprint.h"
#include "core/Util/IdIndexMap.h"

class SOAComponentStore
{
public:
	SOAComponentStore(SOAComponentBlueprint blueprint);

private:
	SOAComponentBlueprint m_blueprint;
	IdIndexMap m_idIndexMap;
};