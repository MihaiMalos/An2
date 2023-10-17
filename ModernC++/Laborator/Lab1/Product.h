#include <string_view>

enum class ProductType {
	PersonalHygiene,
	SmallApliences,
	Clothing,
};

class Product {
	std::uint16_t m_id;
	std::uint8_t m_TVA;
	std::string m_name, m_expDate;
	ProductType m_type;
	double m_price;

public:
	Product(std::uint16_t id, std::uint8_t TVA, std::string_view name, ProductType type, double price);
	Product(std::uint16_t id, std::uint8_t TVA, std::string_view name, std::string_view date, double price);



};