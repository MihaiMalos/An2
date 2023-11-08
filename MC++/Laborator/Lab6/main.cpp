import SpreadSheet;
import <iostream>;
import logging;

int main()
{
	Logger(std::cout, Logger::Level::Info);
	SpreadSheetCell<int> cell{2};
	std::cout << cell.GetData().value_or(0) << std::endl;
	SpreadSheetCell<long> cell2{cell};
	std::cout << cell2.GetData().value_or(0) << std::endl;
	
	std::cout << add<int, long>(cell, cell2) << std::endl;
	std::cout << add(cell, cell2) << std::endl;
	std::cout << add2(cell, cell2) << std::endl;

}

