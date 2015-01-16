/*!
 * @file guimanager.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 12, 2015
 */
#pragma once

#ifndef VIDEO_INCLUDE_2D_RENDERER2D_H_
#define VIDEO_INCLUDE_2D_RENDERER2D_H_

#include "utilities.h"
#include "container/arraymap.h"
#include "container/indexedarray.h"
#include "memory.h"
#include "strings.h"
#include "gui/guiobject.h"
#include "delegates.h"

#ifdef CRAP_NO_DEBUG
#define RENDERER2D_MEMORY SimpleGeneralMemory
#else
#define RENDERER2D_MEMORY BoundGeneralMemory
#endif

struct NVGcontext;

namespace crap
{

typedef NVGcontext 	Context2D;
typedef uint32_t	Image2D;

class Renderer;

class Renderer2D
{
public:

	typedef array_map<string_hash,Image2D > Image2DMap;
	typedef delegate< void(Context2D*)>		RenderCall;
	typedef indexed_array<RenderCall>		RenderArray;

	Renderer2D( Renderer* renderer, uint32_t max_images, uint32_t max_elements );
	~Renderer2D( void );

	void addImage2D( string_hash, Image2D );
	Image2D getImage2D( string_hash );
	void removeImage2D( string_hash );

	template< class C, void (C::*F)( Context2D* ) >
	uint32_t addRencerCall( C* instance  );

	template< void (*F)( Context2D* ) >
	void addRenderCall( void );

	CRAP_INLINE void removeRenderCall( uint32_t id ){ _renderCalls.erase_at(id); }

	CRAP_INLINE Context2D* getContext( void ) { return _context2D; }

	CRAP_INLINE void render( void )
	{
		for( uint32_t i=_renderCalls.begin(); i != _renderCalls.end(); i = _renderCalls.next(i) )
		{
			_renderCalls.get(i)->invoke( _context2D );
		}
	}

private:
	RENDERER2D_MEMORY				_allocator;
	Image2DMap			 			_images;
	RenderArray						_renderCalls;
	Context2D*						_context2D;
	Renderer*						_renderer;
};

template< class C, void (C::*F)( Context2D* ) >
uint32_t Renderer2D::addRencerCall( C* instance  )
{
	RenderCall call;
	call.bind<C,F>(instance);
	return _renderCalls.push_back( call );
}

template< void (*F)( Context2D* ) >
void Renderer2D::addRenderCall( void )
{
	RenderCall call;
	call.bind<F>();
	return _renderCalls.push_back( call );
}


} /* namespace crap */

#endif /* VIDEO_INCLUDE_2D_RENDERER2D_H_ */