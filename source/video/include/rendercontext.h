/*!
 * @file renderwindow.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  Steffen Kopany
 * @date 	Nov 19, 2014
 */
#pragma once

#ifndef VIDEO_INCLUDE_RENDERCONTEXT_H_
#define VIDEO_INCLUDE_RENDERCONTEXT_H_

#include "utilities.h"

namespace bgfx
{
struct VertexDecl;
struct InstanceDataBuffer;
}

namespace crap
{

typedef struct bgfx::VertexDecl VertexDeclaration;
typedef bgfx::InstanceDataBuffer InstanceBuffer;
typedef uint16_t RenderHandle;

struct Attribute
{
	enum Enum // corresponds to vertex shader attribute:
	{
		position,  // a_position
		normal,    // a_normal
		tangent,   // a_tangent
		color0,    // a_color0
		color1,    // a_color1
		indices,   // a_indices
		weight,    // a_weight
		texCoord0, // a_texcoord0
		texCoord1, // a_texcoord1
		texCoord2, // a_texcoord2
		texCoord3, // a_texcoord3
		texCoord4, // a_texcoord4
		texCoord5, // a_texcoord5
		texCoord6, // a_texcoord6
		texCoord7, // a_texcoord7

		count
	};
};

struct AttributeType
{
	enum Enum
	{
		uint8,
		int16,
		half, // Availability depends on: BGFX_CAPS_VERTEX_ATTRIB_HALF.
		flt32,

		count
	};
};

struct VertexAttribute
{
	Attribute::Enum 	attribute;
	AttributeType::Enum	attributeType;
	uint8_t				num;
	bool				normailzed;
	bool				as_int;
};

extern bgfx::VertexDecl ms_decl;

RenderHandle createStaticVertexBuffer(pointer_t<void> memory, uint32_t size, VertexDeclaration* declaration );

void destroyStaticVertexBuffer( RenderHandle staticBuffer );

RenderHandle createStaticIndexBuffer( pointer_t<void> memory, uint32_t size );

void destroyStaticIndexBuffer( RenderHandle staticBuffer );

RenderHandle createShader( pointer_t<void> memory, uint32_t size );

RenderHandle createProgram( RenderHandle vs, RenderHandle fs );

RenderHandle createProgram( RenderHandle gs, RenderHandle vs, RenderHandle fs );

void destroyShader( RenderHandle shader );

void destroyProgram( RenderHandle program );

InstanceBuffer* createInstanceBuffer( uint32_t elementSize, uint32_t elementNumber );

void setInstanceBufferData( InstanceBuffer* buffer, pointer_t<void> data, uint32_t size );

void setVertexAttribute( VertexAttribute& attributes, Attribute::Enum  _attrib, uint8_t _num, AttributeType::Enum _type, bool _norm = false, bool _asInt = false );

void setVertexDeclarationAttributes(VertexDeclaration& declaration, VertexAttribute* attributes, uint32_t number );

void setProgram( RenderHandle handle );

void setVertexBuffer( RenderHandle handle );

void setIndexBuffer( RenderHandle handle );

}

#endif /* VIDEO_INCLUDE_RENDERCONTEXT_H_ */