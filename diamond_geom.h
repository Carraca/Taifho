#include "Piece.h"

class diamond_geom : public Piece {
public:
	diamond_geom(int ownership, int x,int y);

	void render(GLenum mode);
	void static create_geometry(float scale);
};

