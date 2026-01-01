#pragma once
#include "core/CoreTypes.h"
#include "core/Rendering/Shaders/ShaderType.h"

namespace Vanadium
{
	class UniformBinder;

	class UniformBindingVoucher
	{
	public:
		friend class UniformBinder;

		UniformBindingVoucher(UniformBindingVoucher&& other) noexcept
			: m_binder(other.m_binder), m_slot(other.m_slot)
		{
			other.m_binder = nullptr; // invalidate old voucher;
		}

		UniformBindingVoucher& operator=(UniformBindingVoucher&& other) noexcept
		{
			if (&other == this)
				return *this;

			this->m_binder = other.m_binder;
			this->m_slot = other.m_slot;

			other.m_slot = 0;
			other.m_binder = nullptr;

			return *this;
		}

		~UniformBindingVoucher();

		u32 Slot() const { return m_slot; }

	private:
		UniformBindingVoucher() = default;
		UniformBindingVoucher(UniformBindingVoucher&) = default;
		UniformBindingVoucher(UniformBinder* binder, u32 slot)
			: m_binder(binder), m_slot(slot) {
		};

		UniformBinder* m_binder;
		u32 m_slot;
	};
}