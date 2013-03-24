#include "Piece.h"

class square_geom : public Piece {
public:
	square_geom(int ownership, int x,int y);

	void render(GLenum mode);
	void static create_geometry(float scale);
};

