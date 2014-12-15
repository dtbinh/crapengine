
#pragma once

#ifndef CRAP_CORE_PLUGIN
#define CRAP_CORE_PLUGIN

#include "config/crap_types.h"
#include "config/crap_platform.h"
#include "config/crap_compiler.h"

#ifndef CRAP_DL_EXPORT
#define CRAP_DL_API CRAP_API_IMPORT
#else
#define CRAP_DL_API CRAP_API_EXPORT
#endif

namespace crap
{

class Plugin
{
public:

    virtual ~Plugin( void ){}

    virtual void init( void ) = 0;
    virtual void deinit( void ) = 0;

    virtual uint32_t id( void ) = 0;
};

#define CRAP_PLUGIN_CONSTRUCT( type )  Plugin* CRAP_DL_API createPlugin( void* memory ) { return new (memory) type(); }
#define CRAP_PLUGIN_DESTRUCT( type )  void CRAP_DL_API destroyPlugin( type* instance ) { instance->~type(); }
#define CRAP_PLUGIN_SIZE( type )  uint32_t CRAP_DL_API pluginSize( void ) { return sizeof(type); }
#define CRAP_PLUGIN_FACTORY( type ) extern "C" { CRAP_PLUGIN_CONSTRUCT(type) CRAP_PLUGIN_DESTRUCT( type ) CRAP_PLUGIN_SIZE( type ) }

#define CRAP_DECLARE_PLUGIN( type ) CRAP_PLUGIN_FACTORY( type ) class type : public crap::Plugin

} //namespace crap

#endif //CRAP_CORE_PLUGIN
