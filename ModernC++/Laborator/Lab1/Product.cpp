#include"Product.h"

Product::Product(std::uint16_t id, std::uint8_t tva, double price, std::string_view name, std::string_view exp_date)
	: m_id(id)
	, m_tva(tva)
	, m_price(price)
	, m_name(name)
	, m_exp_date(exp_date)
{ }

Product::Product(std::uint16_t id, std::uint8_t tva, double price, std::string_view name, ProductType type)
	: m_id(id)
	, m_tva(tva)
	, m_price(price)
	, m_name(name)
	, m_type{ type }
{
	// int x(10); - la un moment dat, intr-o situatie complexa, o sa primesc un error sintax fiindca seamana cu un apel de functie
	// REZOLVARE:
	// int x{10}; - se numeste o initializare uniforma, adica nu mai apare acel error sintax. 
}

double Product::PriceWithTVA()
{
	return double(m_price) + 10.0 * (m_tva / 100.0);
}

bool Product::NonperishableProducts()
{
	if (m_type == ProductType::PersonalHygiene || m_type == ProductType::SmallAppliences || m_type == ProductType::Clothing)
		return true;
	return false;
}

std::string Product::GetName()
{
	return m_name;
}
