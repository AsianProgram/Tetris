#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <random>
#include <iostream>
#include <algorithm>
using namespace std;

enum pieceType {
	SQUARE,
	LINE,
	TPIECE,
	LPIECE,
	JPIECE,
	ZPIECE,
	SPIECE,
};
class Cell {
	public:
		bool occupied = false;
		sf::Color color;
};

class Board {
	private:
		int rows = 20;
		int columns = 10;

		Cell grid[20][10];
	public:

	int getNumRows() {
		return rows;
	}

	int getNumColumns() {
		return columns;
	}

	void setCellState(int r, int c, bool o) {
		grid[r][c].occupied = o;
	}

	bool getCellState(int r, int c) {
		return grid[r][c].occupied;
	}

	void setCellColor(int r, int c, sf::Color col) {
		grid[r][c].color = col;
	}

	sf::Color getCellColor(int r, int c) {
		return grid[r][c].color;
	}

	bool checkRowFilled(int r) {
		int occ = true;
		for (int i = 0; i < 10; i++) {
			if (getCellState(r, i) == false) {
				occ = false;
			}
		}

		return occ;
	}
	bool checkRowEmpty(int r) {
		int empty = true;
		for (int i = 0; i < 10; i++) {
			if (getCellState(r,i) == true) {
				empty = false;
			}
		}
		return empty;
	}

	void clearRow(int r) {
		for (int i = 0; i < 10; i++) {
			setCellState(r, i, false);
			setCellColor(r, i, sf::Color::Transparent);
		}
	}
};

class Piece {
	public:
		pieceType type;
		int state;
		int rotation = 0;
		sf::Vector2f anchor;
		sf::Vector2f pos[4];
		sf::Vector2f newPos[4];
		sf::RectangleShape pieces[4]; 

	
		void drawPiece(Piece &p, int startX, int startY) {
			switch (p.type) {
				case (SQUARE):
					//piece.pos[]
					for (int i = 0; i < 4; i++) {
						if (i <= 1) {
							p.pieces[i].setSize(sf::Vector2f(25,25));
							p.pieces[i].setPosition(sf::Vector2f(startX+(i*35), startY));
							p.pieces[i].setFillColor(sf::Color::Yellow);
							p.pieces[i].setOutlineColor(sf::Color::White);

							p.pos[i] = sf::Vector2f((p.pieces[i].getPosition().x - 245) / 35, (p.pieces[i].getPosition().y - 205) / 35);
						} 
						else {	
							p.pieces[i].setSize(sf::Vector2f(25,25));
							p.pieces[i].setPosition(sf::Vector2f(startX+((i-2)*35), (startY+35)));
							p.pieces[i].setFillColor(sf::Color::Yellow);
							p.pieces[i].setOutlineColor(sf::Color::White);

							p.pos[i] = sf::Vector2f((p.pieces[i].getPosition().x - 245) / 35, (p.pieces[i].getPosition().y - 205) / 35);
						}
						
					}
					
					
					break;
				case (LINE):
					for (int i = 0; i < 4; i++) {
						p.pieces[i].setSize(sf::Vector2f(25,25));
						p.pieces[i].setPosition(sf::Vector2f((startX-35)+(i*35), startY));
						p.pieces[i].setFillColor(sf::Color::Cyan);
						p.pieces[i].setOutlineColor(sf::Color::White);

						//piece.pos[i] = (sf::Vector2f(350+(i*35), 205));
						p.pos[i] = sf::Vector2f((p.pieces[i].getPosition().x - 245) / 35, (p.pieces[i].getPosition().y - 205) / 35);
						
					}
					break;
				case (TPIECE):
					for (int i = 0; i < 4; i++) {

						if (i == 0) {
							p.pieces[i].setSize(sf::Vector2f(25,25));
							p.pieces[i].setPosition(sf::Vector2f(startX+(i*35), startY));
							p.pieces[i].setFillColor(sf::Color::Magenta);
							p.pieces[i].setOutlineColor(sf::Color::White);

							p.pos[i] = sf::Vector2f((p.pieces[i].getPosition().x - 245) / 35, (p.pieces[i].getPosition().y - 205) / 35);
						}
						else {
							p.pieces[i].setSize(sf::Vector2f(25,25));
							p.pieces[i].setPosition(sf::Vector2f((startX - 35)+((i-1)*35), (startY+35)));
							p.pieces[i].setFillColor(sf::Color::Magenta);
							p.pieces[i].setOutlineColor(sf::Color::White);

							p.pos[i] = sf::Vector2f((p.pieces[i].getPosition().x - 245) / 35, (p.pieces[i].getPosition().y - 205) / 35);
						}
						
					}
					break;
				case (LPIECE):
					for (int i = 0; i < 4; i++) {

						if (i == 0) {
							p.pieces[i].setSize(sf::Vector2f(25,25));
							p.pieces[i].setPosition(sf::Vector2f((startX+35)+(i*35), startY));
							p.pieces[i].setFillColor(sf::Color(255,175,0,255));
							p.pieces[i].setOutlineColor(sf::Color::White);

							p.pos[i] = sf::Vector2f((p.pieces[i].getPosition().x - 245) / 35, (p.pieces[i].getPosition().y - 205) / 35);
						}
						else {
							p.pieces[i].setSize(sf::Vector2f(25,25));
							p.pieces[i].setPosition(sf::Vector2f((startX-35)+((i-1)*35), (startY+35)));
							p.pieces[i].setFillColor(sf::Color(255,175,0,255));
							p.pieces[i].setOutlineColor(sf::Color::White);

							p.pos[i] = sf::Vector2f((p.pieces[i].getPosition().x - 245) / 35, (p.pieces[i].getPosition().y - 205) / 35);
						}
						
					}

					break;
				case (JPIECE):
					for (int i = 0; i < 4; i++) {

						if (i == 0) {
							p.pieces[i].setSize(sf::Vector2f(25,25));
							p.pieces[i].setPosition(sf::Vector2f((startX-35)+(i*35), startY));
							p.pieces[i].setFillColor(sf::Color(0,0,255,255));
							p.pieces[i].setOutlineColor(sf::Color::White);

							p.pos[i] = sf::Vector2f((p.pieces[i].getPosition().x - 245) / 35, (p.pieces[i].getPosition().y - 205) / 35);
						}
						else {
							p.pieces[i].setSize(sf::Vector2f(25,25));
							p.pieces[i].setPosition(sf::Vector2f((startX-35)+((i-1)*35), (startY+35)));
							p.pieces[i].setFillColor(sf::Color(0,0,255,255));
							p.pieces[i].setOutlineColor(sf::Color::White);

							p.pos[i] = sf::Vector2f((p.pieces[i].getPosition().x - 245) / 35, (p.pieces[i].getPosition().y - 205) / 35);
						}
						
					}
					
					break;
				case (ZPIECE):
					for (int i = 0; i < 4; i++) {

						if (i <= 1) {
							p.pieces[i].setSize(sf::Vector2f(25,25));
							p.pieces[i].setPosition(sf::Vector2f((startX-35)+(i*35), startY));
							p.pieces[i].setFillColor(sf::Color(255,0,0,255));
							p.pieces[i].setOutlineColor(sf::Color::White);

							p.pos[i] = sf::Vector2f((p.pieces[i].getPosition().x - 245) / 35, (p.pieces[i].getPosition().y - 205) / 35);
						}
						else {
							p.pieces[i].setSize(sf::Vector2f(25,25));
							p.pieces[i].setPosition(sf::Vector2f((startX-35)+((i-1)*35), (startY+35)));
							p.pieces[i].setFillColor(sf::Color(255,0,0,255));
							p.pieces[i].setOutlineColor(sf::Color::White);

							p.pos[i] = sf::Vector2f((p.pieces[i].getPosition().x - 245) / 35, (p.pieces[i].getPosition().y - 205) / 35);
						}
						
					}
					break;
				case (SPIECE):
					for (int i = 0; i < 4; i++) {

						if (i <= 1) {
							p.pieces[i].setSize(sf::Vector2f(25,25));
							p.pieces[i].setPosition(sf::Vector2f(startX+(i*35), startY));
							p.pieces[i].setFillColor(sf::Color(0,255,0,255));
							p.pieces[i].setOutlineColor(sf::Color::White);

							p.pos[i] = sf::Vector2f((p.pieces[i].getPosition().x - 245) / 35, (p.pieces[i].getPosition().y - 205) / 35);
						}
						else {
							p.pieces[i].setSize(sf::Vector2f(25,25));
							p.pieces[i].setPosition(sf::Vector2f((startX-35)+((i-2)*35), (startY+35)));
							p.pieces[i].setFillColor(sf::Color(0,255,0,255));
							p.pieces[i].setOutlineColor(sf::Color::White);

							p.pos[i] = sf::Vector2f((p.pieces[i].getPosition().x - 245) / 35, (p.pieces[i].getPosition().y - 205) / 35);
						}
						
					}
					break;
				default:
					break;

			}
			//return p;
		}

};

int main()
{

	int r,c;

	Board board;
	Piece piece;

	Piece holdPiece;

	vector<pieceType> bag = {SQUARE, LINE, TPIECE, LPIECE, JPIECE, ZPIECE, SPIECE};
	int pieceIndex = 0;

	int spawnX = 385;
	int spawnY = 205;

	bool hold = true;
	bool holdEmpty = true;
	
	//pieceType bag[7] = {SQUARE, LINE, TPIECE, LPIECE, JPIECE, ZPIECE, SPIECE};
	

	//std:queue<pieceType> selection;


	bool valid = true;
	bool placing = false;
	bool placed = true;
	bool spawn = true;

	int hold1 = 0;
	bool swapPiece = false;

	r = board.getNumRows();
	c = board.getNumColumns();

	sf::Clock clock;
	float placeTimer = 0.f;
	

	std::vector<int> rowsToClear;

	std::random_device rd; 
	std::mt19937 gen(rd()); 
    //std::uniform_int_distribution<int> distr(0, 6); 

	std::shuffle(bag.begin(), bag.end(), gen);

	std::cout << bag.at(0) << " ";
	std::cout << bag.at(1) << " ";
	std::cout << bag.at(2) << " ";
	std::cout << bag.at(3) << " ";
	std::cout << bag.at(4) << " ";
	std::cout << bag.at(5) << " ";
	std::cout << bag.at(6) << "\n";

	sf::RenderWindow window( sf::VideoMode( { 960, 1080 } ), "Tetris!" );


	sf::RectangleShape cell;
	sf::RectangleShape holdCell;
	sf::RectangleShape nextPiecesCell;


	cell.setSize(sf::Vector2f(35,35));
	cell.setFillColor(sf::Color::Transparent);
	cell.setOutlineColor(sf::Color::White);
	cell.setOutlineThickness(2.f);

	holdCell.setSize(sf::Vector2f(140,70));
	holdCell.setFillColor(sf::Color::Transparent);
	holdCell.setOutlineColor(sf::Color::White);
	holdCell.setOutlineThickness(2.f);
	holdCell.setPosition(sf::Vector2f(35,200));

	nextPiecesCell.setSize(sf::Vector2f(140,210));
	nextPiecesCell.setFillColor(sf::Color::Transparent);
	nextPiecesCell.setOutlineColor(sf::Color::White);
	nextPiecesCell.setOutlineThickness(2.f);
	nextPiecesCell.setPosition(sf::Vector2f(650,200));
	
	float fallTimer = 0.f;

	while ( window.isOpen() )
	{
		//sf::Event event;
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() ) {
				window.close();
			}

			if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->code == sf::Keyboard::Key::Left) {

					valid = true;
					for (int i = 0; i < 4; i++) {

						if (((piece.pos[i].x - 1) < 0)) {
							valid = false;
							break;
						}
						else if (board.getCellState(piece.pos[i].y,piece.pos[i].x - 1)) {
							valid = false;
							break;
						}
					}
					if (valid) {
						piece.pieces[0].move(sf::Vector2f(-35.f, 0.f));
						piece.pieces[1].move(sf::Vector2f(-35.f, 0.f));
						piece.pieces[2].move(sf::Vector2f(-35.f, 0.f));
						piece.pieces[3].move(sf::Vector2f(-35.f, 0.f));
						placing = false;
						placeTimer = 0;
					}
					else {
					}

				}

				if (keyPressed->code == sf::Keyboard::Key::Right) {

					valid = true;
					for (int i = 0; i < 4; i++) {

						if (((piece.pos[i].x + 1) > 9)) {
							valid = false;
							break;
						}
						else if (board.getCellState(piece.pos[i].y,piece.pos[i].x + 1)) {
							valid = false;
							break;
						}
					}
					if (valid) {
						piece.pieces[0].move(sf::Vector2f(35.f, 0.f));
						piece.pieces[1].move(sf::Vector2f(35.f, 0.f));
						piece.pieces[2].move(sf::Vector2f(35.f, 0.f));
						piece.pieces[3].move(sf::Vector2f(35.f, 0.f));
						placing = false;
						placeTimer = 0;

					}
					else {
					}

				}		
				if (keyPressed->code == sf::Keyboard::Key::Down) {

					valid = true;
					for (int i = 0; i < 4; i++) {

						if (((piece.pos[i].y + 1) > 19)) {
							valid = false;
							break;
						}
						else if (board.getCellState(piece.pos[i].y + 1,piece.pos[i].x)) {
							valid = false;
							break;
						}
					}
					if (valid) {
						piece.pieces[0].move(sf::Vector2f(0.f, 35.f));
						piece.pieces[1].move(sf::Vector2f(0.f, 35.f));
						piece.pieces[2].move(sf::Vector2f(0.f, 35.f));
						piece.pieces[3].move(sf::Vector2f(0.f, 35.f));
						placing = false;
						placeTimer = 0;

					}
					else {
						placing = true;
					}
			
				}
				if (keyPressed->code == sf::Keyboard::Key::Up) {
					//rotate

					int newX1, newX2, newX4;
					int newY1, newY2, newY4;
					

					switch (piece.type) {
						case (SQUARE):
						
							
							
							break;
						case (LINE):
							if (piece.rotation == 0) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(2,-2);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(1,-1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(-1,1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(70.f, -70.f));
									piece.pieces[1].move(sf::Vector2f(35.f, -35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(-35.f, 35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
								

							}
							else if (piece.rotation == 1) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(2,2);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(1,1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(-1,-1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(70.f, 70.f));
									piece.pieces[1].move(sf::Vector2f(35.f, 35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(-35.f, -35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
							}

							else if (piece.rotation == 2) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(-2,2);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(-1,1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(1,-1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(-70.f, 70.f));
									piece.pieces[1].move(sf::Vector2f(-35.f, 35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(35.f, -35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
							}
							else if (piece.rotation == 3) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(-2,-2);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(-1,-1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(1,1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(-70.f, -70.f));
									piece.pieces[1].move(sf::Vector2f(-35.f, -35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(35.f, 35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation = 0;
									placing = false;
									placeTimer = 0;
								}
							}

							break;
						case (TPIECE):

							if (piece.rotation == 0) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(1,1);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(1,-1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(-1,-1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(35.f, 35.f));
									piece.pieces[1].move(sf::Vector2f(35.f, -35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(-35.f, 35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
								

							}
							else if (piece.rotation == 1) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(-1,1);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(1,1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(-1,-1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(-35.f, 35.f));
									piece.pieces[1].move(sf::Vector2f(35.f, 35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(-35.f, -35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
							}

							else if (piece.rotation == 2) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(-1,-1);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(-1,1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(1,-1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(-35.f, -35.f));
									piece.pieces[1].move(sf::Vector2f(-35.f, 35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(35.f, -35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
							}
							else if (piece.rotation == 3) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(1,-1);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(-1,-1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(1,1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(35.f, -35.f));
									piece.pieces[1].move(sf::Vector2f(-35.f, -35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(35.f, 35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation = 0;
									placing = false;
									placeTimer = 0;
								}
							}


							
							break;
						case (LPIECE):
							if (piece.rotation == 0) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(0,2);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(1,-1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(-1,1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(0.f, 70.f));
									piece.pieces[1].move(sf::Vector2f(35.f, -35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(-35.f, 35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
								

							}
							else if (piece.rotation == 1) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(-2,0);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(1,1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(-1,-1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(-70.f, 0.f));
									piece.pieces[1].move(sf::Vector2f(35.f, 35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(-35.f, -35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
							}

							else if (piece.rotation == 2) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(0,-2);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(-1,1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(1,-1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(0.f, -70.f));
									piece.pieces[1].move(sf::Vector2f(-35.f, 35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(35.f, -35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
							}
							else if (piece.rotation == 3) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(2,0);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(-1,-1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(1,1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(70.f, 0.f));
									piece.pieces[1].move(sf::Vector2f(-35.f, -35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(35.f, 35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation = 0;
									placing = false;
									placeTimer = 0;
								}
							}

							break;
						case (JPIECE):
						if (piece.rotation == 0) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(2,0);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(1,-1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(-1,1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(70.f, 0.f));
									piece.pieces[1].move(sf::Vector2f(35.f, -35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(-35.f, 35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
								

							}
							else if (piece.rotation == 1) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(0,2);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(1,1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(-1,-1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(0.f, 70.f));
									piece.pieces[1].move(sf::Vector2f(35.f, 35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(-35.f, -35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
							}

							else if (piece.rotation == 2) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(-2,0);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(-1,1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(1,-1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(-70.f, 0.f));
									piece.pieces[1].move(sf::Vector2f(-35.f, 35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(35.f, -35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
							}
							else if (piece.rotation == 3) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(0,-2);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(-1,-1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(1,1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(0.f, -70.f));
									piece.pieces[1].move(sf::Vector2f(-35.f, -35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(35.f, 35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation = 0;
									placing = false;
									placeTimer = 0;
								}
							}

							
							
							break;
						case (ZPIECE):
							if (piece.rotation == 0) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(2,0);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(1,1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(-1,1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(70.f, 0.f));
									piece.pieces[1].move(sf::Vector2f(35.f, 35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(-35.f, 35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
								

							}
							else if (piece.rotation == 1) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(-1,2);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(0,1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(-1,-1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(-35.f, 70.f));
									piece.pieces[1].move(sf::Vector2f(0.f, 35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(-35.f, -35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
							}

							else if (piece.rotation == 2) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(-1,0);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(-2,-1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(1,-1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(-35.f, 0.f));
									piece.pieces[1].move(sf::Vector2f(-70.f, -35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(35.f, -35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
							}
							else if (piece.rotation == 3) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(0,-2);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(1,-1);
								piece.newPos[3] = piece.pos[3] + sf::Vector2f(1,1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[3].x < 0) || (piece.newPos[3].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[3].y < 0) || (piece.newPos[3].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[3].y, piece.newPos[3].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(0.f, -70.f));
									piece.pieces[1].move(sf::Vector2f(35.f, -35.f));
									piece.pieces[2].move(sf::Vector2f(0.f, 0.f));
									piece.pieces[3].move(sf::Vector2f(35.f, 35.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[3] = piece.newPos[3];
									

									piece.rotation = 0;
									placing = false;
									placeTimer = 0;
								}

							}
							
							break;
						case (SPIECE):
							if (piece.rotation == 0) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(1,1);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(0,2);
								piece.newPos[2] = piece.pos[2] + sf::Vector2f(1,-1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[2].x < 0) || (piece.newPos[2].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[2].y < 0) || (piece.newPos[2].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[2].y, piece.newPos[2].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(35.f, 35.f));
									piece.pieces[1].move(sf::Vector2f(0.f, 70.f));
									piece.pieces[2].move(sf::Vector2f(35.f, -35.f));
									piece.pieces[3].move(sf::Vector2f(0.f, 0.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[2] = piece.newPos[2];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
								

							}
							else if (piece.rotation == 1) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(-1,1);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(-2,0);
								piece.newPos[2] = piece.pos[2] + sf::Vector2f(1,1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[2].x < 0) || (piece.newPos[2].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[2].y < 0) || (piece.newPos[2].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[2].y, piece.newPos[2].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(-35.f, 35.f));
									piece.pieces[1].move(sf::Vector2f(-70.f, 0.f));
									piece.pieces[2].move(sf::Vector2f(35.f, 35.f));
									piece.pieces[3].move(sf::Vector2f(0.f, 0.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[2] = piece.newPos[2];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
								

							}
							else if (piece.rotation == 2) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(-1,-2);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(0,-1);
								piece.newPos[2] = piece.pos[2] + sf::Vector2f(-1,1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[2].x < 0) || (piece.newPos[2].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[2].y < 0) || (piece.newPos[2].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[2].y, piece.newPos[2].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(-35.f, -70.f));
									piece.pieces[1].move(sf::Vector2f(0.f, -35.f));
									piece.pieces[2].move(sf::Vector2f(-35.f, 35.f));
									piece.pieces[3].move(sf::Vector2f(0.f, 0.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[2] = piece.newPos[2];
									

									piece.rotation += 1;
									placing = false;
									placeTimer = 0;
								}
								

							}
							else if (piece.rotation == 3) {
								piece.newPos[0] = piece.pos[0] + sf::Vector2f(1,0);
								piece.newPos[1] = piece.pos[1] + sf::Vector2f(2,-1);
								piece.newPos[2] = piece.pos[2] + sf::Vector2f(-1,-1);

								valid = true;

								if ((piece.newPos[0].x < 0) || (piece.newPos[0].x > 9) || (piece.newPos[1].x < 0) || (piece.newPos[1].x > 9) || (piece.newPos[2].x < 0) || (piece.newPos[2].x > 9)) {
									valid = false;
								}
								else if ((piece.newPos[0].y < 0) || (piece.newPos[0].y > 19) || (piece.newPos[1].y < 0) || (piece.newPos[1].y > 19) || (piece.newPos[2].y < 0) || (piece.newPos[2].y > 19)) {
									valid = false;
								}
								else if (board.getCellState(piece.newPos[0].y, piece.newPos[0].x) || board.getCellState(piece.newPos[1].y, piece.newPos[1].x) || board.getCellState(piece.newPos[2].y, piece.newPos[2].x)) {
									valid = false;
								}

								if (valid) {

									piece.pieces[0].move(sf::Vector2f(35.f, 0.f));
									piece.pieces[1].move(sf::Vector2f(70.f, -35.f));
									piece.pieces[2].move(sf::Vector2f(-35.f, -35.f));
									piece.pieces[3].move(sf::Vector2f(0.f, 0.f));

									piece.pos[0] = piece.newPos[0];
									piece.pos[1] = piece.newPos[1];
									piece.pos[2] = piece.newPos[2];
									

									piece.rotation = 0;
									placing = false;
									placeTimer = 0;
								}
								

							}
							
							break;
						default:
							break;

					}
				}
				if (keyPressed->code == sf::Keyboard::Key::Space) {
					
					//work on bottom to top appraoch later
					// int bottom = 19;

					// bool found = false;
				
					// while (!found && (bottom > -1)) {
					// 	// piece.pos[0]
					// 	// piece.pos[1]
					// 	// piece.pos[2]
					// 	// piece.pos[3]

					// 	// if (!found) {

					// 	// }
					// 	// for (int i = 0; i < 4; i++) {
					// 	// 	if (board.getCellState(bottom, piece.pos[i].x)) {
					// 	// 		valid = false;
					// 	// 	}
					// 	// }

						

					// 	if (!(board.getCellState(bottom, piece.pos[0].x)) 
					// 	&& !(board.getCellState(bottom, piece.pos[1].x)) 
					// 	&& !(board.getCellState(bottom, piece.pos[2].x)) 
					// 	&& !(board.getCellState(bottom, piece.pos[3].x)))
					// 	{
					// 		found = true;
					// 	}
					// 	else {
					// 		bottom -= 1;
					// 	}
					// 	//(piece.pos[0].x)
					// }


					//top to bottom approach
					
					valid = true;

					int offset = 1;
					
					while (valid) {
						for (int i = 0; i < 4; i++) {

							if (((piece.pos[i].y + offset) > 19)) {
								valid = false;
								break;
							}
							else if (board.getCellState(piece.pos[i].y + offset,piece.pos[i].x)) {
								valid = false;
								break;
							}
						}

						offset++;
					}
					offset -= 2;
					
					piece.pieces[0].move(sf::Vector2f(0.f, (35.f*offset)));
					piece.pieces[1].move(sf::Vector2f(0.f, (35.f*offset)));
					piece.pieces[2].move(sf::Vector2f(0.f, (35.f*offset)));
					piece.pieces[3].move(sf::Vector2f(0.f, (35.f*offset)));
					placing = false;

				}
				if (keyPressed->code == sf::Keyboard::Key::C) {
					// holdCount %= 2;
					// holdCount++;
					// if (holdCount == 1)

					//if press c for first time, turn to 0, 
					
					//if hold is 1, hold the piece
						//check if holdEmpty is 1
							//if 1 hodl the piece and go to next piece
							//if not empty, swap pieces

					// if (holdEmpty) {
					// 	holdEmpty = false;

					// 	if (hold) {
					// 		holdPiece = piece;
					// 		holdPiece.drawPiece(holdPiece, 70, 205);
					// 		pieceIndex++;

					// 		if (pieceIndex < 7) {
					// 			piece.type = bag.at(pieceIndex++);
					// 		}
					// 		else {	//end of bag, reset index, and reshuffle bag
					// 			pieceIndex = 0;
					// 			shuffle(bag.begin(), bag.end(), gen);

					// 			// std::cout << bag.at(0) << " ";
					// 			// std::cout << bag.at(1) << " ";
					// 			// std::cout << bag.at(2) << " ";
					// 			// std::cout << bag.at(3) << " ";
					// 			// std::cout << bag.at(4) << " ";
					// 			// std::cout << bag.at(5) << " ";
					// 			// std::cout << bag.at(6) << "\n";
					// 			piece.type = bag.at(pieceIndex++);
					// 		}
							
					// 		piece.drawPiece(piece, 385, 205);
					// 	}
					// }
					// else {

					// }

					if (hold) {

						if (holdEmpty) {
							holdEmpty = false;
							hold = false;

							holdPiece = piece;
							holdPiece.drawPiece(holdPiece, 70, 205);
							pieceIndex++;

							if (pieceIndex < 7) {
								piece.type = bag.at(pieceIndex++);
							}
							else {	//end of bag, reset index, and reshuffle bag
								pieceIndex = 0;
								shuffle(bag.begin(), bag.end(), gen);
								piece.type = bag.at(pieceIndex++);
							}

							piece.drawPiece(piece, 385, 205);
							//placed = true;

						}
						else {
							hold = false;

							Piece temp = holdPiece;

							holdPiece = piece;
							holdPiece.drawPiece(holdPiece, 70, 205);

							
							piece.pieces[0] = temp.pieces[0];
							piece.pieces[1] = temp.pieces[1];
							piece.pieces[2] = temp.pieces[2];
							piece.pieces[3] = temp.pieces[3];
							piece.type = temp.type;
							piece.rotation = 0;

							if (piece.type != SPIECE) {
								piece.anchor = piece.pos[2];
							}
							else if (piece.type == SPIECE) {
								piece.anchor = piece.pos[3];
							}

							// piece.anchor = temp.anchor;
							// piece.type = temp.type;
							piece.drawPiece(piece, 385, 205);
							
						}
					}
				}


				piece.pos[0] = sf::Vector2f((piece.pieces[0].getPosition().x - 245) / 35, (piece.pieces[0].getPosition().y - 205) / 35);
				piece.pos[1] = sf::Vector2f((piece.pieces[1].getPosition().x - 245) / 35, (piece.pieces[1].getPosition().y - 205) / 35);
				piece.pos[2] = sf::Vector2f((piece.pieces[2].getPosition().x - 245) / 35, (piece.pieces[2].getPosition().y - 205) / 35);
				piece.pos[3] = sf::Vector2f((piece.pieces[3].getPosition().x - 245) / 35, (piece.pieces[3].getPosition().y - 205) / 35);
				
				if (piece.type != SPIECE) {
					piece.anchor = piece.pos[2];
				}
				else if (piece.type == SPIECE) {
					piece.anchor = piece.pos[3];
				}
				
			}
		}
		
		sf::Time deltaTime = clock.restart();
		float dt = deltaTime.asSeconds();

		fallTimer += dt;

		window.clear();
		//window.draw(player);
		//window.draw( shape );
		//cell.setPosition(sf::Vector2f(480,540));
		
		// if (!swapPiece) {

		// 	if (!hold) {

		// 	}
		// }

		//if can't hold piece, check if u can swap or replace
		// if (!hold) {
		// 	if (swapPiece) {	//if swapping piece

		// 	}
		// 	else {	//if replacing
		// 		piece.type = bag.at(pieceIndex++);
		// 		piece.rotation = 0;

		// 		piece.drawPiece(piece, 385, 205);
		// 	}
		// }
		//when piece is placed, generate a new piece type
		while (placed) {	
			
			int lastidx = 19;
			int nextidx = 19;

			while (nextidx > -1) {
				
				if (board.checkRowFilled(nextidx)) {
					nextidx -= 1;
				} 
				else {

					for (int i  = 0; i < 10; i++) {
						board.setCellColor(lastidx, i, board.getCellColor(nextidx,i));
						board.setCellState(lastidx, i, board.getCellState(nextidx,i));
					}

					nextidx -= 1;
					lastidx -= 1;
					
				}
			} 
			
			//piece.type = static_cast<pieceType>(distr(gen));

			//if not at end of bag, grab piece and increment index
			if (pieceIndex < 7) {
				piece.type = bag.at(pieceIndex++);
			}
			else {	//end of bag, reset index, and reshuffle bag
				pieceIndex = 0;
				shuffle(bag.begin(), bag.end(), gen);

				std::cout << bag.at(0) << " ";
				std::cout << bag.at(1) << " ";
				std::cout << bag.at(2) << " ";
				std::cout << bag.at(3) << " ";
				std::cout << bag.at(4) << " ";
				std::cout << bag.at(5) << " ";
				std::cout << bag.at(6) << "\n";
				piece.type = bag.at(pieceIndex++);
			}

			//swapPiece = true;
			placed = false;
			spawn = true;
		}

		//creation and swpaning of new piece
		if (spawn) {

			hold = true;
			spawn = false;
			piece.rotation = 0;

			piece.drawPiece(piece, 385, 205);
			
		}
		

		//drawing the grid
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (board.getCellState(i,j)) {
					cell.setFillColor(board.getCellColor(i,j));
				}
				else {
					cell.setFillColor(sf::Color::Transparent);
				}
				cell.setPosition(sf::Vector2f(240+(j*35),200+(i*35)));
				window.draw(cell);
			}
		}

		window.draw(holdCell);
		window.draw(nextPiecesCell);





		//x borders 245-560

		//y borders 205-870

		if (fallTimer >= 2) {
			valid = true;
			for (int i = 0; i < 4; i++) {

				if (((piece.pos[i].y + 1) > 19)) {
					valid = false;
					break;
				}
				else if (board.getCellState(piece.pos[i].y + 1,piece.pos[i].x)) {
					valid = false;
					break;
				}
			}

			if (valid) {
				piece.pieces[0].move(sf::Vector2f(0.f, 35.f));
				piece.pieces[1].move(sf::Vector2f(0.f, 35.f));
				piece.pieces[2].move(sf::Vector2f(0.f, 35.f));
				piece.pieces[3].move(sf::Vector2f(0.f, 35.f));

				piece.pos[0].y += 1;
				piece.pos[1].y += 1;
				piece.pos[2].y += 1;
				piece.pos[3].y += 1;

				if (piece.type != SPIECE) {
					piece.anchor = piece.pos[2];
				}
				else if (piece.type == SPIECE) {
					piece.anchor = piece.pos[3];
				}
			}
			else {
				placing  = true;
			}
				

			fallTimer = 0;
		}

		//if piece can be placed, not locked in place yet
		if (placing) {
			placeTimer += dt;

			if (placeTimer >= 0.1) {
				placing = false;
				placed = true;
				
				board.setCellState(piece.pos[0].y, piece.pos[0].x, true);
				board.setCellState(piece.pos[1].y, piece.pos[1].x, true);
				board.setCellState(piece.pos[2].y, piece.pos[2].x, true);
				board.setCellState(piece.pos[3].y, piece.pos[3].x, true);

				board.setCellColor(piece.pos[0].y, piece.pos[0].x, piece.pieces[0].getFillColor());
				board.setCellColor(piece.pos[1].y, piece.pos[1].x, piece.pieces[1].getFillColor());
				board.setCellColor(piece.pos[2].y, piece.pos[2].x, piece.pieces[2].getFillColor());
				board.setCellColor(piece.pos[3].y, piece.pos[3].x, piece.pieces[3].getFillColor());

				placeTimer = 0;
				fallTimer = 0;

			}
		}

		for (int i = 0; i < 4; i++) {
			window.draw(holdPiece.pieces[i]);
		} 
		for (int i = 0; i < 4; i++) {
			window.draw(piece.pieces[i]);
		} 
		

		// std::cout << "position 0: (" << piece.pos[0].x << "," << piece.pos[0].y << ")\n";
		// std::cout << "position 1: (" << piece.pos[1].x << "," << piece.pos[1].y << ")\n";
		// std::cout << "position 2: (" << piece.pos[2].x << "," << piece.pos[2].y << ")\n";
		// std::cout << "position 3: (" << piece.pos[3].x << "," << piece.pos[3].y << ")\n";
		// std::cout << "valid: (" << valid << ")\n";
		// std::cout << "placing: (" << placing << ")\n";
		// std::cout << "placed: (" << placed << ")\n";
		
		// std::cout << bag.at(0) << " ";
		// std::cout << bag.at(1) << " ";
		// std::cout << bag.at(2) << " ";
		// std::cout << bag.at(3) << " ";
		// std::cout << bag.at(4) << " ";
		// std::cout << bag.at(5) << " ";
		// std::cout << bag.at(6) << "\n";

		//std::cout << "piece selected: " << bag.at(pieceIndex) << "\n";
		
		window.display();
	}
}
