#include"Product.h"

#include<iostream>
#include<fstream>
#include<vector>
#include<regex>

ProductType Convert(std::string myString)
{
	if (myString == "PersonalHygiene")     return ProductType::PersonalHygiene;
	else if (myString == "SmallAppliences") return ProductType::SmallAppliences;
	else if (myString == "Clothing")       return ProductType::Clothing;
}

void SortByName(std::vector<Product>& products)
{

}

void SortByPrice(std::vector<Product>& products)
{

}


int main()
{
	std::uint16_t id;
	std::uint16_t tva;
	double price;
	std::string name, dateOrType;
	ProductType type;
	std::regex date{ R"(\d\d\d\d-\d\d-\d\d)" };

	std::ifstream fin("product.prodb");
	std::vector<Product> products;

	while (!fin.eof())
	{
		fin >> id >> name >> price >> tva >> dateOrType;
		if (std::regex_match(dateOrType, date))
			products.push_back(Product{ id, tva, price, name, dateOrType });
		else
			products.push_back(Product(id, tva, price, name, Convert(dateOrType)));
	}

	for (int i = 0; i < products.size(); i++)
	{
		if (products[i].NonperishableProducts())
			std::cout << products[i].GetName() << " Price: " << products[i].PriceWithTVA() << "\n";
	}
}