/*
 * cell.h
 */

#ifndef CELL_H_
#define CELL_H_

#include <boost/shared_ptr.hpp>

class Game_piece;

#include "game_piece.h"

class Cell {
public:
	Cell(Game_piece* piece = NULL);
	const boost::shared_ptr<Game_piece>& get_contents() const;
	void set_content(boost::shared_ptr<Game_piece> piece);
private:
	boost::shared_ptr<Game_piece> m_contents;
};

#endif /* CELL_H_ */
