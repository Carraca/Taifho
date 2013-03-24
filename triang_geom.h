#include "Piece.h"

class trian_geom : public Piece {
public:
	trian_geom(int ownership, int x, int y);

	void render(GLenum mode);
	void static create_geometry(float scale);


};
