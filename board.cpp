#include "board.h"
#include "empty_piece.h"
const unsigned int Board::K_BOARD_X_SIZE(10);
const unsigned int Board::K_BOARD_Y_SIZE(10);

Board::Board() {
	for (unsigned int j = 0; j < K_BOARD_Y_SIZE; j++) {
		for (unsigned int i = 0; i < K_BOARD_X_SIZE; i++) {
			m_cells.push_back(Cell(new Empty_piece(Vector_2D(i, j))));
		}
	}
	//set_cell(m_cells.at(5));
}

unsigned int Board::get_x_size() const {
	return Board::K_BOARD_X_SIZE;
}

unsigned int Board::get_y_size() const {
	return Board::K_BOARD_Y_SIZE;
}

const Cell& Board::get_cell(Vector_2D position) const {
	return m_cells[position.x() + get_x_size()*position.y()];
}

Player_ID Board::get_piece_ownership(Vector_2D position) {
	return get_cell_contents(position)->get_ownership();
}

boost::shared_ptr<Game_piece> Board::get_cell_contents(Vector_2D position) {
	return get_cell(position).get_contents();
}

void Board::print_board() {
	for (unsigned int y = 0; y < K_BOARD_Y_SIZE; ++y) {
		for (unsigned int x = 0; x < K_BOARD_Y_SIZE; ++x) {
			std::cout << get_cell_contents(Vector_2D(x, y))->get_textual_representation() << ' ';
		}
		std::cout << '\n';
	}
}

void Board::set_cell_contents(Vector_2D position, boost::shared_ptr<Game_piece> piece) {
	m_cells[position.x() + get_x_size()*position.y()].set_content(piece);
}

void Board::move_piece(Vector_2D initial, Vector_2D final) {
	boost::shared_ptr<Game_piece> piece = get_cell_contents(initial);
	piece->set_position(final);
	set_cell_contents(final, piece);
	boost::shared_ptr<Game_piece> empty = boost::shared_ptr<Game_piece>(new Empty_piece(initial));
	set_cell_contents(initial, empty);
}


Board Board::clone() {
	Board b;

	for(int y = 0; y < get_y_size(); ++y) {
		for(int x = 0; x < get_x_size(); ++x) {
			b.set_cell_contents(Vector_2D(x, y),
				boost::shared_ptr<Game_piece>(this->get_cell_contents(Vector_2D(x, y))->clone())
			);
		}
	}

	return b;
}

int Board::num_of_pieces(Player_ID player) {
	int num = 0;
	for (unsigned int j = 0; j < K_BOARD_Y_SIZE; j++) {
		for (unsigned int i = 0; i < K_BOARD_X_SIZE; i++) {
			if (get_piece_ownership(Vector_2D(i, j)) == player) {
				num ++;
			}
		}
	}
	return num;
}
