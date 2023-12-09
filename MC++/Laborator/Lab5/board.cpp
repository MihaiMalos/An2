module board;

using namespace quarto;


const std::optional<Piece>& Board::operator[](const Position& position) const
{
	const auto& [line, column] = position;
	return m_board[line * kWidth + column];
}


std::optional<Piece>& Board::operator[](const Position& position)
{
	return const_cast<std::optional<Piece>&>(std::as_const(*this)[position]);
}

std::ostream& quarto::operator<<(std::ostream& out, const Board& board)
{
	std::string_view kEmptyBoardCell{"____"};
	Board::Position position;
	auto& [line, column] = position;

	for (; line < Board::kHeight; ++line)
	{
		for (column = 0; column < Board::kWidth; ++column)
		{
			if (const auto& pieceOpt{ board[position] }; pieceOpt.has_value())
				out << pieceOpt.value();
			else
				out << kEmptyBoardCell;
			out << " ";
		}
		out << std::endl;
	}
	return out;
}