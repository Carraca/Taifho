#include "Game_object.h"


Game_object::Game_object(void) {
}


Game_object::~Game_object(void) {
}

int Game_object::get_ownership()
{
	return m_ownership;
}

void Game_object::set_ownership(int p)
{
	m_ownership = p;
}

