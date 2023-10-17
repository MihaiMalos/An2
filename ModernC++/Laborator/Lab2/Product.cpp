#include "Product.h"

Product::Product(uint16_t id, std::string_view name, float rawPrice)
	: m_id{id}
	, m_name{name}
	, m_rawPrice{rawPrice}
{

}

uint16_t Product::GetID() const
{
	return m_id;
}

const std::string& Product::GetName() const
{
	return m_name;
}

float Product::GetRawPrice() const
{
	return m_rawPrice;
}

