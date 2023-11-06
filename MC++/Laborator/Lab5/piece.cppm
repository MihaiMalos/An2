module;

#include <cstdint>

export module piece;
import <iostream>;
import <format>;


namespace quarto 
{
	export class Piece 
	{

	public:
		enum class Body:uint8_t {Full, Hollow};
		enum class Color:uint8_t {Dark, Light};
		enum class Height:uint8_t {Short, Tall};
		enum class Shape:uint8_t {Round, Square};

		Piece(Body body, Color color, Height height, Shape shape);

		const Body& GetBody() const;
		const Color& GetColor() const;
		const Height& GetHeight() const;
		const Shape& GetShape() const;

	private:
		Body m_body:1; // se aloca un singur bit
		Color m_color:1;
		Height m_height:1;
		Shape m_shape:1;

	}; // aici se termina clasa Piece
	export std::ostream& operator<<(std::ostream& out, const Piece& piece);
}