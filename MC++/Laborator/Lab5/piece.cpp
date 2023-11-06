module piece;

quarto::Piece::Piece(Body body, Color color, Height height, Shape shape)
	: m_body{body}
	, m_color{color}
	, m_height{height}
	, m_shape{shape}
{
	static_assert(sizeof(*this) <= 1, "This class should be 4 bits in size, not that much...");
}

const quarto::Piece::Body& quarto::Piece::GetBody() const
{
	return m_body;
}
const quarto::Piece::Color& quarto::Piece::GetColor() const
{
	return m_color;
}
const quarto::Piece::Height& quarto::Piece::GetHeight() const
{
	return m_height;
}
const quarto::Piece::Shape& quarto::Piece::GetShape() const
{
	return m_shape;
}

std::ostream& quarto::operator<<(std::ostream& out, const Piece& piece)
{
	return out << std::format("{}{}{}{}",
	static_cast<int>(piece.GetBody()),
	static_cast<int>(piece.GetColor()),
	static_cast<int>(piece.GetHeight()),
	static_cast<int>(piece.GetShape())
	);

}