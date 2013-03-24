#include "PassEvent.h"

PassEvent::PassEvent()
{

}

PassEvent::PassEvent( int player )
{
	this->player = player;
}

bool PassEvent::isPass()
{
	return true;
}
