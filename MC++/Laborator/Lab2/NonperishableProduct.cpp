#include "NonperishableProduct.h"

NonperishableProduct::NonperishableProduct(uint16_t id, std::string_view name, float rawPrice, NonperishableProductType type)
	: Product{ id, name, rawPrice }
	, m_type{ type }
{

}

NonperishableProductType NonperishableProduct::GetType()
{
	return m_type;
}

int32_t NonperishableProduct::GetVAT() const
{
	return VAT;
}

float NonperishableProduct::GetPrice() const
{
	return m_rawPrice + m_rawPrice * VAT / 100.0f;
}
