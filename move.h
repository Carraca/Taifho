/*
 * move.h
 */

#ifndef MOVE_H_
#define MOVE_H_

#include "vector_2d.h"
#include <vector>


class Move {
public:
  Move(Vector_2D initial, Vector_2D final);
  Move(int xi, int yi, int xf, int yf);
  Move();

  Vector_2D initial() const;
  void initial(Vector_2D initial);

  Vector_2D final() const;
  void final(Vector_2D final);

private:
  Vector_2D m_initial;
  Vector_2D m_final;
};


#endif /* MOVE_H_ */
