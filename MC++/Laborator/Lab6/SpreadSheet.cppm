export module SpreadSheet;

import <optional>;
import <iostream>;

export template <class T = int> // default e int
class SpreadSheetCell
{
public:
	SpreadSheetCell() = default;
	SpreadSheetCell(const T& data)
		: m_data{ data }
	{

	}

	SpreadSheetCell(const SpreadSheetCell& other) = default;
	template <class E>
	SpreadSheetCell(const SpreadSheetCell<E>& other)
		: m_data(other.GetData())
	{

	}
	~SpreadSheetCell() = default;

	std::optional<T> GetData() const noexcept
	{
		return m_data;
	}

private:
	std::optional<T> m_data;

};

export template <class T>
std::ostream& operator<<(std::ostream& out, const SpreadSheetCell<T>& cell)
{
	if (cell.GetData().has_value())
		out << cell.GetData().value();
	else
		out << "Cell is empty\n";
	return out;
}

export template <class T, class W>
auto add(const SpreadSheetCell<T>& cell1, const SpreadSheetCell<W>& cell2)
{
	return cell1.GetData().value() + cell2.GetData().value();

}

export auto add2(const auto& cell1, const auto& cell2)
{
	return cell1.GetData().value() + cell2.GetData().value();

}