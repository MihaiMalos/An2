#pragma once
#include "Product.h"

enum class NonperishableProductType
{
	Clothing,
	SmallAppliences,
	PersonalHygiene,
};

class NonperishableProduct : public Product
{
public:
	NonperishableProduct(uint16_t id, std::string_view name, float rawPrice, NonperishableProductType type);
	NonperishableProductType GetType();
	int32_t GetVAT() const override;
	float GetPrice() const override;
private:
	static const uint8_t VAT = 19;
	NonperishableProductType m_type;

};

