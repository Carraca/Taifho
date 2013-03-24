#include "MoveEvent.h"

bool MoveEvent::isMove()
{
	return true;
}

MoveEvent::MoveEvent()
{

}

MoveEvent::MoveEvent( Vector_2D i, Vector_2D f )
{
	init=i;
	final=f;
}

Vector_2D MoveEvent::getInit()
{
	return init;
}

Vector_2D MoveEvent::getFinal()
{
	return final;
}
