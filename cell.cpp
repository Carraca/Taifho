/*
 * cell.cpp
 *
 *  Created on: 14 de Abr de 2012
 *      Author: Ana
 */

#include "cell.h"


Cell::Cell(Game_piece* piece) : m_contents(piece) {}

const boost::shared_ptr<Game_piece>& Cell::get_contents() const {
	return m_contents;
}

void Cell::set_content(boost::shared_ptr<Game_piece> piece) {
	m_contents = piece;
}
