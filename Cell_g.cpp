#include "Cell_g.h"

Cell_g::Cell_g(Game_object *content) : game_object(content) {}

Cell_g::~Cell_g(void) {
}

void Cell_g::render_contents(GLenum mode) {
	if (this->has_pawn()) {
		game_object->render(mode);
	}
}

bool Cell_g::has_pawn() {
	return game_object != nullptr;
}

std::shared_ptr<Game_object> Cell_g::get_game_object()
{
	return game_object;
}

void Cell_g::set_game_object(std::shared_ptr<Game_object> game_o)
{
	game_object = game_o;
}

