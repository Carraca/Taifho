#include "turnEvent.h"

TurnEvent::TurnEvent()
{

}

TurnEvent::TurnEvent( int p )
{
	player = p;
}

bool TurnEvent::isTurn()
{
	return true;
}

int TurnEvent::getPlayer()
{
	return player;
}
