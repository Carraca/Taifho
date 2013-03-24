#include "Mqueue.h"

void Mqueue::push( BoardEvent* e )
{
	{
		boost::mutex::scoped_lock lock_it( this->mut ) ;
		this->events.push(e);
	}
}

bool Mqueue::empty()
{
	{
		boost::mutex::scoped_lock lock_it( this->mut ) ;
		return this->events.empty();
	}
}

BoardEvent* Mqueue::pop()
{
	{
		boost::mutex::scoped_lock lock_it( this->mut ) ;

		if(!this->events.empty()){
			BoardEvent *e = this->events.front();
			this->events.pop();
			return e;
		}

		return NULL;
	}
}

