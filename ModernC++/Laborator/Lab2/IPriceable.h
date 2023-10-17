#pragma once
#include <cstdint>

struct IPriceable
{
	virtual int32_t GetVAT() const = 0;
	virtual float GetPrice() const = 0;
};