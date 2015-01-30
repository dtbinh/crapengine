/*!
 * @file transformation2d.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 16, 2015
 */

#define CRAP_DL 1

#include <cstdio>
#include "transformation2d.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"

namespace crap
{

Transformation2D::Transformation2D( void)
{
	_data.position[0] = 0.f;
	_data.position[1] = 0.f;
	_data.rotation = 0.f;
	_data.scale = 1.f;
	_data.damping = 0.f;
	_data.friction = 0.f;
	_data.restitution = 0.f;
	_data.torque = 0.f;
	_data.velocity[0] = 0.f;
	_data.velocity[1] = 0.f;

	REGISTER_COMPONENT_MEMBER( Transformation2D, posX, float32_t )
	REGISTER_COMPONENT_MEMBER( Transformation2D, posY, float32_t )
	REGISTER_COMPONENT_MEMBER( Transformation2D, rotation, float32_t )
	REGISTER_COMPONENT_MEMBER( Transformation2D, scale, float32_t )
	REGISTER_COMPONENT_MEMBER( Transformation2D, damping, float32_t )
	REGISTER_COMPONENT_MEMBER( Transformation2D, friction, float32_t )
	REGISTER_COMPONENT_MEMBER( Transformation2D, restitution, float32_t )
	REGISTER_COMPONENT_MEMBER( Transformation2D, torque, float32_t )
	REGISTER_COMPONENT_MEMBER( Transformation2D, velocityX, float32_t )
	REGISTER_COMPONENT_MEMBER( Transformation2D, velocityY, float32_t )
}

Transformation2D::~Transformation2D( void )
{

}

void Transformation2D::init( System* system )
{

}

void Transformation2D::deinit( System* system )
{

}


} /* namespace crap */
