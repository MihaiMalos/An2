#include <vector>
#include <fstream>
#include <regex>
#include <iostream>
#include <algorithm>

#include "IPriceable.h";
#include "NonperishableProduct.h"
#include "PerishableProduct.h"


NonperishableProductType StringToType(std::string type)
{
		if (type == "PersonalHygiene")     return NonperishableProductType::PersonalHygiene;
		else if (type == "SmallAppliences") return NonperishableProductType::SmallAppliences;
		else if (type == "Clothing")       return NonperishableProductType::Clothing;
}

bool Comparator(IPriceable* p1, IPriceable* p2)
{
	return p1->GetPrice() < p2->GetPrice();
}

int main()
{
	std::vector<IPriceable*> products;

	std::uint16_t id, VAT;
	std::string name, expirationDateOrType;
	float rawPrice;

	for (std::ifstream fin{"product.prodb"}; !fin.eof(); /*empty*/)
	{
		fin >> id >> name  >> rawPrice>>  VAT >> expirationDateOrType;
		std::regex date{ R"(\d\d\d\d-\d\d-\d\d)" };
		if (std::regex_match(expirationDateOrType, date))
			products.push_back(new PerishableProduct(id, name, rawPrice, expirationDateOrType));
		else
			products.push_back(new NonperishableProduct(id, name, rawPrice, StringToType(expirationDateOrType)));

	}

	for (auto product : products)
	{
		auto nonPerishableProduct = dynamic_cast<NonperishableProduct*>(product);
		if (nonPerishableProduct)
		{
			std::cout << nonPerishableProduct->GetName() << " " << nonPerishableProduct->GetPrice() << std::endl;
		}
	}
	std::cout << std::endl;
	auto lambdaComparator = [](const IPriceable* p1, const IPriceable* p2)
	{
		return p1->GetPrice() < p2->GetPrice();
	};
	std::sort(products.begin(), products.end(), lambdaComparator);
	for (auto product : products)
	{
		auto currentProduct = dynamic_cast<Product*>(product);
		std::cout << currentProduct->GetName() << " " << currentProduct->GetPrice() << std::endl;
	}

	for (auto product : products)
	{
		delete product;
	}

	return 0;
	
}