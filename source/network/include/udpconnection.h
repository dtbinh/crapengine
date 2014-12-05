/*!
 * @file connection.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 2, 2014
 */
#pragma once

#ifndef NETWORK_INCLUDE_UDPCONNECTION_H_
#define NETWORK_INCLUDE_UDPCONNECTION_H_

#include "container/arraymap.h"
#include "delegates.h"
#include "sockets.h"
#include "packetlayer.h"

namespace crap
{

class UdpConnection
{
public:

	struct Event
	{
		enum Enum
		{
			LOGIN,
			LOGOUT,
			SYNC,
			RESYNC,
			DATA
		};
	};


	typedef array_map<uint32_t, ConnectionInformation> ConnectionMap;
	typedef delegate< void(Event::Enum, uint32_t, ConnectionInformation* )> EventFunction;
	typedef array<EventFunction> EventArray;

	UdpConnection( port_t port, uint32_t packetSize,
			pointer_t<void> connectionMemory, uint32_t connectionSize,
			pointer_t<void> eventMemory, uint32_t eventSize );
	~UdpConnection( void );

	void connect( ipv4_t address, port_t port );
	bool receive( void );
	bool sendData( uint32_t user_id, pointer_t<void> data, uint32_t size );

	template< class C, void (C::*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
	bool registerForEvents( C* instance );

	template< void (*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
	bool registerForEvents( void );

	template< class C, void (C::*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
	bool unregisterFromEvents( C* instance );

	template< void (*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
	bool unregisterFromEvents( void );

	template< class C, bool (C::*F)( uint32_t, pointer_t<void>, uint32_t) >
	bool setDataFunction( C* instance );

	template< bool (*F)( uint32_t, pointer_t<void>, uint32_t ) >
	bool setDataFunction( void );

private:

	bool compareChecksum( ConnectionHeader* CRAP_RESTRICT header ) const;
	bool userLogin( ConnectionHeader* CRAP_RESTRICT header, ConnectionInformation& info );
	bool userLogout( uint32_t user_id );
	bool userSync( uint32_t user_id );
	bool userResync( uint32_t user_id );

	bool sendLogin( ipv4_t address, port_t port );
	bool sendLogout( ipv4_t address, port_t port );
	bool sendSync( ipv4_t address, port_t port );
	bool sendResync( ipv4_t address, port_t port );

	delegate<bool( uint32_t, pointer_t<void>, uint32_t )> _dataFunction;

	ConnectionMap   _connections;
	EventArray		_eventArray;

	uint32_t _session_id;
	socket_t _socket;
	uint16_t _port;
	uint32_t _packet_size;
};

template< class C, void (C::*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
bool UdpConnection::registerForEvents( C* instance  )
{
	EventFunction func;
	func.bind<C, F>( instance );

	uint32_t index = _eventArray.push_back( func );
	return index != EventArray::INVALID;
}

template< class C, void (C::*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
bool UdpConnection::unregisterFromEvents( C* instance )
{
	EventFunction func;
	func.bind<C, F>( instance );

	uint32_t index = _eventArray.find( func );
	if( index != EventArray::INVALID )
	{
		_eventArray.erase_at( index );
		return true;
	}
	return false;
}

template< void (*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
bool UdpConnection::registerForEvents( void )
{
	EventFunction func;
	func.bind<F>();

	uint32_t index = _eventArray.push_back( func );
	return index != EventArray::INVALID;
}

template< void (*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
bool UdpConnection::unregisterFromEvents( void )
{
	EventFunction func;
	func.bind<F>();

	uint32_t index = _eventArray.find( func );
	if( index != EventArray::INVALID )
	{
		_eventArray.erase_at( index );
		return true;
	}
	return false;
}

template< class C, bool (C::*F)( uint32_t, pointer_t<void>, uint32_t) >
bool UdpConnection::setDataFunction( C* instance )
{
	_dataFunction.bind<C,F>(instance);
}

template< bool (*F)( uint32_t, pointer_t<void>, uint32_t ) >
bool UdpConnection::setDataFunction( void )
{
	_dataFunction.bind<F>();
}

}

#endif /* NETWORK_INCLUDE_UDPCONNECTION_H_ */
