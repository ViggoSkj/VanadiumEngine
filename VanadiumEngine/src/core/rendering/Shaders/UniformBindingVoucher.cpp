#include "pch.h"
#include "UniformBindingVoucher.h"
#include "UniformBinder.h"

namespace Vanadium
{
	UniformBindingVoucher::~UniformBindingVoucher()
	{
		if (m_binder != nullptr)
			m_binder->ReturnBindingSlot(*this);
	}
}