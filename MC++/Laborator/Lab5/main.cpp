import <iostream>;
import piece;

int main()
{
	using namespace quarto;
	Piece firstPiece(Piece::Body::Full, Piece::Color::Light, Piece::Height::Short, Piece::Shape::Square);
	std::cout << firstPiece;
	return 0;
}