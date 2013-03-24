#include "WinEvent.h"

WinEvent::WinEvent()
{

}

WinEvent::WinEvent( int p )
{
	player = p;
}

bool WinEvent::isWin()
{
	return true;
}

int WinEvent::getPlayer()
{
	return player;
}
