/*!
 * @file guimanager.cpp
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

#include "renderwindow.h"
#include "elements2d.h"
#include "renderer2d.h"

namespace crap
{

Renderer2D::Renderer2D( RenderWindow* window, uint32_t max_images, uint32_t max_fonts, uint32_t max_elements ) :
	_allocator( Image2DMap::size_of_elements(max_images ) + Font2DMap::size_of_elements(max_fonts) + RenderArray::size_of_elements(max_elements) *2 ),
		_images( _allocator.allocate(Image2DMap::size_of_elements(max_images),4),
				Image2DMap::size_of_elements(max_images) ),
		_fonts( _allocator.allocate(Font2DMap::size_of_elements(max_fonts),4),
				Image2DMap::size_of_elements(max_fonts) ),
		_renderCalls( _allocator.allocate( RenderArray::size_of_elements(max_elements), 4 ),
				RenderArray::size_of_elements(max_elements) ),
		_window(window)
{
	_context2D = createContext2D(1, 0);
}

Renderer2D::~Renderer2D( void )
{
	destroyContext2D( _context2D );
	_allocator.deallocate(_renderCalls.memory().as_void);
	_allocator.deallocate(_fonts.memory().as_void);
	_allocator.deallocate(_images.memory().as_void );
}

void Renderer2D::drawBegin( void )
{
	draw2DBegin( _context2D, _window->getWidth(), _window->getHeight(), 1.f );
}

void Renderer2D::drawEnd( void )
{
	draw2DEnd( _context2D );
}

void Renderer2D::addImage2D( string_hash name, Image2D id )
{
	_images.push_back( name, id );
}

Image2D Renderer2D::getImage2D( string_hash name )
{
	const uint32_t index = _images.find( name );
	if( index != Image2DMap::INVALID )
	{
		return *_images.get_value(index);
	}
	return Image2DMap::INVALID;
}

void Renderer2D::removeImage2D( string_hash name )
{
	const uint32_t index = _images.find( name );
	if( index != Image2DMap::INVALID )
	{
		destroyImage2D( _context2D, *_images.get_value(index) );
		_images.erase_at(index);
	}
}

void Renderer2D::addFont2D( string_hash name, Font2D id )
{
	_fonts.push_back( name, id );
}

Image2D Renderer2D::getFont2D( string_hash name )
{
	const uint32_t index = _fonts.find( name );
	if( index != Font2DMap::INVALID )
	{
		return *_fonts.get_value(index);
	}
	return Font2DMap::INVALID;
}

void Renderer2D::removeFont2D( string_hash name )
{
	const uint32_t index = _fonts.find( name );
	if( index != Font2DMap::INVALID )
	{
		destroyFont2D( _context2D, *_fonts.get_value(index) );
		_fonts.erase_at(index);
	}
}

} /* namespace crap */
