#include <iostream>
#include <regex>

int main() {
	std::regex myPattern(R"([-+]?\d+(\.\d+)?)");

	std::string myTestString = "+23.4";

	//std::cout << std::regex_match(myTestString, myPattern);

	std::cout << std::regex_replace("de ce ananas merge ananas", std::regex(R"((ananas)*)"), "******");

}