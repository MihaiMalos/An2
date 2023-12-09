export module piece;

import std;

using std::uint8_t;

namespace quarto 
{
	export class Piece 
	{
	public:
		enum class Body:uint8_t {Full, Hollow, NoBody};
		enum class Color:uint8_t {Dark, Light, NoColor};
		enum class Height:uint8_t {Short, Tall, NoHeight};
		enum class Shape:uint8_t {Round, Square, NoShape};

		Piece();
		Piece(Body body, Color color, Height height, Shape shape);
		Piece(const Piece& other);
		~Piece();

		const Body& GetBody() const;
		const Color& GetColor() const;
		const Height& GetHeight() const;
		const Shape& GetShape() const;

	private:
		Body m_body:2; // se aloca un singur bit
		Color m_color:2;
		Height m_height:2;
		Shape m_shape:2;

	}; // aici se termina clasa Piece
	export std::ostream& operator<<(std::ostream& out, const Piece& piece);
}