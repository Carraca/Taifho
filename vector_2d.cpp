/*
 * vector_2d.cpp
 */

#include "vector_2d.h"


Vector_2D::Vector_2D() {}

Vector_2D::Vector_2D(int x, int y) {
  this->m_x = x;
  this->m_y = y;
}

int Vector_2D::x() const {
  return m_x;
}

void Vector_2D::x(int x) {
  this->m_x = x;
}

int Vector_2D::y() const {
  return m_y;
}

void Vector_2D::y(int y) {
  this->m_y = y;
}

bool Vector_2D::operator == (const Vector_2D& a) const{
	return a.x() == x() && a.y() == y();
}

std::ostream& operator<<(std::ostream &out, const Vector_2D& a) {
	out << a.x()  << " " << a.y();
	return out; 
}
