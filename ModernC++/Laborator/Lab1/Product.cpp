#include "Product.h"

Product::Product(std::uint16_t id, std::uint8_t TVA, std::string_view name, ProductType type, double price)
: m_id{id}
, m_TVA{TVA}
, m_name{name}
, m_type{type}
, m_price{price}
{

}

Product::Product(std::uint16_t id, std::uint8_t TVA, std::string_view name, std::string_view date, double price) 
: m_id{id}
, m_TVA{TVA}
, m_name {name}
, m_expDate{date}
, m_price{price}
{

}
