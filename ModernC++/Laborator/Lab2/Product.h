#pragma once
#include "IPriceable.h"

#include <string_view>

class Product : public IPriceable
{

public:
	Product(uint16_t id, std::string_view name, float rawPrice);
	uint16_t GetID() const;
	const std::string& GetName() const;
	float GetRawPrice() const;

protected:
	uint16_t m_id;
	std::string m_name;
	float m_rawPrice;
};

