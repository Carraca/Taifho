/*
 * move.cpp
 *
 *  Created on: 13 de Abr de 2012
 *      Author: Ana
 */

#include "move.h"

Move::Move() {}
Move::Move(Vector_2D initial, Vector_2D final) {
	m_initial = initial;
	m_final = final;
}

Vector_2D Move::initial() const {
	return m_initial;
}

void Move::initial(Vector_2D initial) {
	m_initial = initial;
}

Vector_2D Move::final() const {
	return m_final;
}

void Move::final(Vector_2D final) {
	m_final = final;
}

