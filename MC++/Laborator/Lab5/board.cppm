export module board;

import std;
export import piece;


namespace quarto
{
	export class Board
	{
	public:
		static const size_t kWidth{4}, kHeight{4};
		static const size_t kSize{kWidth* kHeight};

		using Position = std::pair<size_t, size_t>;
		Board() = default;
		const std::optional<Piece>& operator[](const Position& position) const;
		std::optional<Piece>& operator[](const Position& position);

	private:
		std::array<std::optional<Piece>, kSize> m_board;
	};

	export std::ostream& operator<<(std::ostream& out, const Board& board);

}