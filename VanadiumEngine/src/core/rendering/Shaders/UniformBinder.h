#pragma once

#include "Descriptors/ShaderDescriptor.h"
#include "UniformObject.h"
#include "ShaderType.h"
#include "UniformBindingVoucher.h"

namespace Vanadium
{
	class UniformBinder
	{
	public:
		friend UniformBindingVoucher::~UniformBindingVoucher();

		UniformBinder();
		~UniformBinder();

		UniformBindingVoucher ClaimBindingSlot();
	private:
		void ReturnBindingSlot(UniformBindingVoucher& voucher);

		std::vector<UniformBindingVoucher> m_bindingSlots;
	};
}