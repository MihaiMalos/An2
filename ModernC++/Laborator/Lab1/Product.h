#pragma once
#include<cstdint>
#include<iostream>
#include<string_view>


enum class ProductType
{
	PersonalHygiene,
	SmallAppliences,
	Clothing
};


class Product
{
public:

	Product(std::uint16_t, std::uint8_t, double, std::string_view, std::string_view);
	Product(std::uint16_t, std::uint8_t, double, std::string_view, ProductType);
	double PriceWithTVA();
	bool NonperishableProducts();
	std::string GetName();


private:
	std::uint16_t m_id;
	std::uint8_t m_tva;
	double m_price;
	std::string m_name, m_exp_date;
	ProductType m_type;
};
