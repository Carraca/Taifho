#pragma once

#include <memory>

#include "Game_object.h"
#include <vector>

class Cell_g {
public:
	Cell_g(Game_object *content = nullptr);
	~Cell_g(void);

	void render_contents(GLenum mode); 
	bool has_pawn();
	
	std::shared_ptr<Game_object> get_game_object();
	void set_game_object(std::shared_ptr<Game_object> game_o);
	void remove_game_object();
	
private:
	std::shared_ptr<Game_object> game_object;
};

