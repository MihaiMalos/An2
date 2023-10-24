#pragma once
#include "Product.h"

class PerishableProduct : public Product
{
public:
	PerishableProduct(uint16_t id, std::string_view name, float rawPrice, std::string_view expriationDate);
	const std::string_view& GetExpirationDate() const;
	int32_t GetVAT() const override;
	float GetPrice() const override;

private:
	static const uint8_t VAT = 9;
	std::string m_expirationDate;
};

