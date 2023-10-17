#include <fstream>
#include <vector>
#include <regex>

#include "Product.h"


int main() {
	std::ifstream fin("product.prodb");
	std::vector<Product> products;

	std::uint16_t id;
	std::uint8_t TVA;
	std::string name, dateOrType;
	double price;
	std::regex datePattern("\d\d\d\d-\d\d-\d\d");


	while (!fin.eof())
	{

		fin >> id >> TVA >> name >> price >> TVA >> dateOrType;

		if (std::regex_match(dateOrType, datePattern))
		{
			products.push_back(Product{id, TVA, name, dateOrType, price});
		}
		else
		{
			
		}

	}
}