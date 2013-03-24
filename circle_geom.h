#include "Piece.h"

class circle_geom : public Piece {
public:
	circle_geom(int ownership, int x,int y);

	void render(GLenum mode);
	void static create_geometry(float scale);
};

