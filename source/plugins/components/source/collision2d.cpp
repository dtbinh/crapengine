/*!
 * @file collision2d.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Feb 2, 2015
 */

#define CRAP_DL 1

#include <cstdio>
#include "convert.h"
#include "collision2d.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "attributes2d.h"
#include "taskmanager.h"
#include "system.h"

namespace crap
{

Collision2D::Collision2D( void ) : _attributes(0)
{

}

Collision2D::~Collision2D( void )
{

}

void Collision2D::init( System* system )
{
	_attributes = (Attributes2D*)getNeighbour("Attributes2D");

	char buffer[64];
	sprintf( buffer, "%u", getGlobalID() );
	_taskID = buffer;

	TaskManager* tm = system->getSubSystem<TaskManager>("TaskManager");
	tm->addTask<Collision2D, &Collision2D::update>( buffer, this, 50, true );
}

void Collision2D::deinit( System* system )
{
	TaskManager* tm = system->getSubSystem<TaskManager>("TaskManager");
	tm->removeTask( _taskID );
}

bool Collision2D::update( uint32_t delta )
{
	if( _attributes->getData()->collision != 0 )
	{
		_node->sendChidren("Collision2D", 0 );
		_attributes->getData()->collision = 0;
		printf("PLUMPS\n");
	}

	return true;
}

} /* namespace crap */



