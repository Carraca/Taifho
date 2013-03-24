/*
 * vector_2d.h
 */
#pragma once
#ifndef VECTOR_2D_H_
#define VECTOR_2D_H_

#include <ostream>

class Vector_2D {
public:
  Vector_2D(int x, int y);
  Vector_2D();

  int x() const;
  void x(int x);

  int y() const;
  void y(int y);

  bool operator == (const Vector_2D& a) const;

  friend std::ostream& operator<<(std::ostream &out, const Vector_2D& a);

private:
  int m_x;
  int m_y;
};


#endif /* VECTOR_2D_H_ */
