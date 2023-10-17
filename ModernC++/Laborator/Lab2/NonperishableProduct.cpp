#include "NonperishableProduct.h"

NonperishableProduct::NonperishableProduct(uint16_t id, std::string_view name, float rawPrice, NonperishableProductType type)
{

}

NonperishableProductType NonperishableProduct::GetType()
{

}

int32_t NonperishableProduct::GetVAT() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

float NonperishableProduct::GetPrice() const
{
	throw std::logic_error("The method or operation is not implemented.");
}
