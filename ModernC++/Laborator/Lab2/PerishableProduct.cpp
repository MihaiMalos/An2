#include "PerishableProduct.h"

PerishableProduct::PerishableProduct(uint16_t id, std::string_view name, float rawPrice, std::string_view expriationDate)
	: Product{id, name, rawPrice}
	, m_expirationDate{expriationDate}
{

}

const std::string& PerishableProduct::GetExpirationDate() const
{
	return m_expirationDate;
}

int32_t PerishableProduct::GetVAT() const
{
	return VAT;
}

float PerishableProduct::GetPrice() const
{
	return m_rawPrice + m_rawPrice * VAT / 100.0f;
}
