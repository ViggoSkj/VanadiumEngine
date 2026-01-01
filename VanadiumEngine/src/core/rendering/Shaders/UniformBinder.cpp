#include "pch.h"
#include "UniformBinder.h"
#include "core/Rendering/GLCommon.h"

namespace Vanadium
{
	UniformBinder::UniformBinder()
	{
		int maxBindingSlot;
		GL_CHECK(glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &maxBindingSlot));

		for (i32 i = maxBindingSlot - 1; i >= 0; i--)
		{
			m_bindingSlots.push_back(UniformBindingVoucher(this, i));
		}
	}

	UniformBinder::~UniformBinder()
	{
		for (i32 i = 0; i < m_bindingSlots.size(); i++)
		{
			m_bindingSlots[i].m_binder = nullptr;
		}
	}

	UniformBindingVoucher UniformBinder::ClaimBindingSlot()
	{
		UniformBindingVoucher v = std::move(m_bindingSlots.back());
		m_bindingSlots.pop_back();
		return v;
	}

	void UniformBinder::ReturnBindingSlot(UniformBindingVoucher& voucher)
	{
		m_bindingSlots.push_back(UniformBindingVoucher(this, voucher.Slot()));
		voucher.m_slot = 0;
		voucher.m_binder = nullptr;
	}
}