/*!
 * @file treemap.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Nov 6, 2014
 */


#ifndef CORE_INCLUDE_CONTAINER_TREEMAP_H_
#define CORE_INCLUDE_CONTAINER_TREEMAP_H_

#include "utilities.h"

/**
 * @namespace crap
 * @brief Libraries namespace
 */
namespace crap
{

/**
 * @class tree
 * @brief A red-black tree indexed based implementation
 *
 * The data is kept packed, the tree is connected
 * by using indices.
 */
template <typename K, typename V>
class tree_map
{
private:

	/**
	 * @struct nested struct used as index
	 */
    struct tree_map_node
    {
    	/**
    	 * @enum names for the index array
    	 */
        enum
        {
            parent=0,
            left=1,
            right=2
        };

        /// sub nodes
        uint32_t sub_nodes[3];

        /**
         * @brief Constructor
         */
        tree_map_node( void )
        {
            sub_nodes[0] = INVALID;
            sub_nodes[1] = INVALID;
            sub_nodes[2] = INVALID;
        }

        /**
         * @brief copy constructor
         */
        tree_map_node( const tree_map_node& other )
        {
            sub_nodes[0] = other.sub_nodes[0];
            sub_nodes[1] = other.sub_nodes[1];
            sub_nodes[2] = other.sub_nodes[2];
        }

        /**
         * @brief assignment operator
         */
        tree_map_node& operator=( const tree_map_node& other )
        {
            sub_nodes[0] = other.sub_nodes[0];
            sub_nodes[1] = other.sub_nodes[1];
            sub_nodes[2] = other.sub_nodes[2];

            return *this;
        }
    };

    /// pointer to indices
    pointer_t<tree_map_node>  _indices;

    /// pointer to keys
    pointer_t<K>            _keys;

    /// pointer to data
    pointer_t<V>            _values;

    /// root index
    uint32_t                _root;

    /// weight of tree (negative left, positive right)
    int32_t					_weight;

    /// current size
    uint32_t                _size;

    /// maximum size
    uint32_t                _size_max;

    void delete_recursive( uint32_t node_index );

    //! @brief Copy constructor
    CRAP_INLINE tree_map( const tree_map& other );

    //! @brief Finds key and returns free spot
    uint32_t find_free(const K& key, int32_t* direction ) const;

    /**
     * @brief Helper function getting node with lowest value from index
     * @param index Index to start searching from
     * @return index with lowest value or INVALID
     */
    CRAP_INLINE
	uint32_t first_from( uint32_t index ) const;

    /**
     * @brief Helper function getting node with highest value from index
     * @param index Index to start searching from
     * @return index with highest value or INVALID
     */
    CRAP_INLINE
	uint32_t last_from( uint32_t index ) const;

public:

    /// an invalid key
    static const uint32_t INVALID = UINT32_MAX;

	/**
	 * @brief Constructor
	 * @param memory pointer to memory
	 * @param size size of provided memory
	 */
    CRAP_INLINE
	explicit tree_map( void* memory, uint32_t size );

	/**
	 * @brief destructor
	 */
    CRAP_INLINE
	~tree_map( void );

	/**
	 * @brief Finds key and returns index
	 * @param key The key value to find
	 * @return index of key or INVALID
	 */
    CRAP_INLINE
    uint32_t find( const K& key ) const;

	/**
	 * @brief Inserting key if unique and returns index
	 * @param key The key value to insert
	 * @return index of key or INVALID
	 */
    CRAP_INLINE
    uint32_t insert( const K& key, const V& value );

	/**
	 * @brief Removes key at given index
	 * @param index The index value to remove
	 */
    CRAP_INLINE
    void erase_at( uint32_t index );

	/**
	 * @brief Find key and remove element
	 * @param key The key value to remove
	 */
    CRAP_INLINE
    void erase( const K& key );

	/**
	 * @brief Finds the smalles element and returns index
	 * @return index to smalles node
	 */
    CRAP_INLINE
    uint32_t begin( void ) const;

	/**
	 * @brief Finds the biggest element and returns index
	 * @return index to biggest node
	 */
    CRAP_INLINE
    uint32_t last( void ) const;

	/**
	 * @brief Returns invalid element
	 * @return constant INVALID
	 */
    CRAP_INLINE
    uint32_t end( void ) const;

    /**
     * @brief get following index
     * @param index current index
     * @return next index
     */
    CRAP_INLINE
	uint32_t next( uint32_t index ) const;

    /**
     * @brief get previous index
     * @param index current index
     * @return previous index
     */
    CRAP_INLINE
	uint32_t previous( uint32_t index ) const;

    /**
     * @brief returns pointer of given index
     * @param index Index of element
     * @return pointer to element or 0
     */
    CRAP_INLINE
    K* get_key( uint32_t index );

    /**
     * @brief returns pointer of given index
     * @param index Index of element
     * @return pointer to element or 0
     */
    CRAP_INLINE
    const K* get_key( uint32_t  index ) const;

    /**
     * @brief returns pointer of given index
     * @param index Index of element
     * @return pointer to element or 0
     */
    CRAP_INLINE
    V* get_value( uint32_t index );

    /**
     * @brief returns pointer of given index
     * @param index Index of element
     * @return pointer to element or 0
     */
    CRAP_INLINE
    const V* get_value( uint32_t  index ) const;

    /**
     * @brief index operator
     * @param index to element
     * @return refernce to element
     */
    CRAP_INLINE
    V& operator[]( const K& index );

    /**
     * @brief index operator
     * @param index to element
     * @return refernce to element
     */
    CRAP_INLINE
    const V& operator[]( const K& index ) const;

	/**
	 * @brief Tree number of stored nodes
	 * @return current size
	 */
    CRAP_INLINE
    uint32_t size(void) const;

    /**
     * @brief Tree number of max stored nodes
     * @return maximum size
     */
    CRAP_INLINE
    uint32_t max_size(void) const;

    /**
     * @brief returns pointer to memory
     * @return pointer to memory
     */
    CRAP_INLINE
    pointer_t<void> memory( void ) const;

    /**
     * @brief returns necessary memory for given number of elements
     * @param number Number of elements
     * @return amount of memory
     */
    CRAP_INLINE static uint32_t size_of_elements( uint32_t number );
};

/*
 * Protected Methods
 */

template <typename K, typename V>
void tree_map<K,V>::delete_recursive( uint32_t node_index )
{
    if(node_index == INVALID)
		return;

    delete_recursive( _indices.as_type[node_index].sub_nodes[tree_map_node::left] );
    delete_recursive( _indices.as_type[node_index].sub_nodes[tree_map_node::right] );

    erase_at(node_index);
}

template <typename K, typename V>
//! @brief Finds key and returns free spot
uint32_t tree_map<K,V>::find_free(const K& key, int32_t* direction ) const
{
	uint32_t last_index = INVALID;
    uint32_t current_index = _root;
    *direction = 0;

    while( current_index != INVALID )
    {
        tree_map_node* current_node = &(_indices.as_type[current_index]);

        if( _keys.as_type[current_index] == key )
            return INVALID;

        last_index = current_index;

        if( _keys.as_type[current_index] > key )
        {
            current_index = current_node->sub_nodes[tree_map_node::left];
            if( *direction == 0 )
            	*direction = -1;
        }
        else if( _keys.as_type[current_index] < key )
        {
            current_index = current_node->sub_nodes[tree_map_node::right];
            if( *direction == 0 )
            	*direction = 1;
        }
    }

    return last_index;
}

template <typename K, typename V>
uint32_t tree_map<K,V>::first_from( uint32_t index ) const
{
	uint32_t return_index = index;

	while( _indices.as_type[return_index].sub_nodes[tree_map_node::left] != INVALID )
	{
		return_index = _indices.as_type[return_index].sub_nodes[tree_map_node::left];
	}

	return return_index;
}

template <typename K, typename V>
uint32_t tree_map<K,V>::last_from( uint32_t index ) const
{
	uint32_t return_index = index;

	while( _indices.as_type[return_index].sub_nodes[tree_map_node::right] != INVALID )
	{
		return_index = _indices.as_type[return_index].sub_nodes[tree_map_node::right];
	}

	return return_index;
}

/*
 * Public methods
 */

template <typename K, typename V>
tree_map<K,V>::tree_map( void* memory, uint32_t size ) :
	_size(0), _size_max( size / (sizeof(tree_map_node)+sizeof(K)+sizeof(V)) ), _root(INVALID)
{
    _indices = memory;
    _keys.as_void = _indices.as_type + _size_max;
    _values.as_void = _keys.as_type + _size_max;
}

template <typename K, typename V>
tree_map<K,V>::~tree_map( void )
{
	delete_recursive( _root );
}

template <typename K, typename V>
uint32_t tree_map<K,V>::find( const K& key ) const
{
    uint32_t current_index = _root;

    while( current_index != INVALID )
    {
        tree_map_node* current_node = _indices.as_type + current_index;

        if( _keys.as_type[current_index] == key )
            return current_index;

        if( _keys.as_type[current_index] > key )
            current_index = current_node->sub_nodes[tree_map_node::left];

        if( _keys.as_type[current_index] < key )
            current_index = current_node->sub_nodes[tree_map_node::right];
    }

    return current_index;
}


template <typename K, typename V>
uint32_t tree_map<K,V>::insert( const K& key, const V& value )
{
	if( _size < _size_max )
	{
		new ( _indices.as_type + _size ) tree_map_node();
		copy_construct_object( &key , _keys.as_type + _size );
		copy_construct_object( &value , _values.as_type + _size );

		int32_t direction;
		uint32_t free_index = find_free( key, &direction );

		if( free_index == INVALID )
		{
			_root = _size;
		}
		else
		{
			uint32_t insert_direction = ( _keys.as_type[free_index] < key ) ? tree_map_node::right : tree_map_node::left;

			_indices.as_type[free_index].sub_nodes[insert_direction] = _size;
	        _indices.as_type[_size].sub_nodes[tree_map_node::parent] = free_index;
		}

		_weight += direction;
		return _size++;
	}

    return  INVALID;
}

template <typename K, typename V>
void tree_map<K,V>::erase_at( uint32_t index )
{
	if( index < _size )
	{
		const uint32_t parent_index = _indices.as_type[index].sub_nodes[tree_map_node::parent];
		const uint32_t left_index = _indices.as_type[index].sub_nodes[tree_map_node::left];
		const uint32_t right_index = _indices.as_type[index].sub_nodes[tree_map_node::right];

		//root node
		if( parent_index == INVALID )
		{
			if( right_index == INVALID )
			{
				_root = left_index;
				_weight++;
			}
			else if( left_index == INVALID )
			{
				_root = right_index;
				_weight--;
			}
			else if( left_index != INVALID && right_index != INVALID )
			{
				if( _weight <= 0 )
				{
					const uint32_t last_index = last_from( left_index );
					_indices.as_type[left_index].sub_nodes[tree_map_node::parent] = INVALID;
					_indices.as_type[right_index].sub_nodes[tree_map_node::parent] = last_index;
					_indices.as_type[last_index].sub_nodes[tree_map_node::right] = right_index;
					_root = left_index;
					_weight++;
				}
				else
				{
					const uint32_t last_index = first_from( right_index );
					_indices.as_type[right_index].sub_nodes[tree_map_node::parent] = INVALID;
					_indices.as_type[left_index].sub_nodes[tree_map_node::parent] = last_index;
					_indices.as_type[last_index].sub_nodes[tree_map_node::left] = left_index;
					_root = right_index;
					_weight--;
				}
			}
			else
				_root = INVALID;
		}
		else
		{
			if( _indices.as_type[parent_index].sub_nodes[tree_map_node::left] == index )
			{
				if( left_index == INVALID && right_index == INVALID )
				{
					_indices.as_type[parent_index].sub_nodes[ tree_map_node::left ] = INVALID;
				}
				else if( left_index == INVALID )
				{
					_indices.as_type[parent_index].sub_nodes[ tree_map_node::left ] = right_index;
				}
				else if( right_index == INVALID )
				{
					_indices.as_type[parent_index].sub_nodes[ tree_map_node::left ] = left_index;
				}
				else
				{
					const uint32_t closest_index = first_from( right_index );
					_indices.as_type[closest_index].sub_nodes[ tree_map_node::left ] = left_index;
					_indices.as_type[left_index].sub_nodes[ tree_map_node::parent ] = closest_index;
					_indices.as_type[parent_index].sub_nodes[ tree_map_node::left ] = right_index;
				}
			}
			else if( _indices.as_type[parent_index].sub_nodes[tree_map_node::right] == index )
			{
				if( left_index == INVALID && right_index == INVALID )
				{
					_indices.as_type[parent_index].sub_nodes[ tree_map_node::right ] = INVALID;
				}
				else if( left_index == INVALID )
				{
					_indices.as_type[parent_index].sub_nodes[ tree_map_node::right ] = right_index;
				}
				else if( right_index == INVALID )
				{
					_indices.as_type[parent_index].sub_nodes[ tree_map_node::right ] = left_index;
				}
				else
				{
					const uint32_t closest_index = last_from( left_index );
					_indices.as_type[closest_index].sub_nodes[ tree_map_node::right ] = right_index;
					_indices.as_type[right_index].sub_nodes[ tree_map_node::parent ] = closest_index;
					_indices.as_type[parent_index].sub_nodes[ tree_map_node::right ] = left_index;

				}
			}

			//weight..
			uint32_t check_index = _indices.as_type[index].sub_nodes[ tree_map_node::parent ];
			while( check_index != INVALID )
			{
				if( _indices.as_type[check_index].sub_nodes[ tree_map_node::left ] == check_index  && check_index == _root )
				{
					_weight++;
					break;
				}
				if( _indices.as_type[check_index].sub_nodes[ tree_map_node::right] == check_index  && check_index == _root )
				{
					_weight--;
					break;
				}

				check_index = _indices.as_type[check_index].sub_nodes[ tree_map_node::parent ];
			}
		}

	    destruct_object( _keys.as_type + index );
	    destruct_object( _values.as_type + index );

	    //keep stuff packed
	    if( index != _size-1 )
	    {
	    	const uint32_t last_index = _size-1;

	    	const uint32_t last_parent =  _indices.as_type[last_index].sub_nodes[tree_map_node::parent];
	    	const uint32_t last_left =  _indices.as_type[last_index].sub_nodes[tree_map_node::left];
	    	const uint32_t last_right =  _indices.as_type[last_index].sub_nodes[tree_map_node::right];

	    	if( last_parent != INVALID )
	    	{
	    		if( _indices.as_type[last_parent].sub_nodes[tree_map_node::left] == last_index )
	    			_indices.as_type[last_parent].sub_nodes[tree_map_node::left] = index;
	    		else
	    			_indices.as_type[last_parent].sub_nodes[tree_map_node::right] = index;
	    	}

	    	if( last_left != INVALID )
	    	{
	    		_indices.as_type[last_left].sub_nodes[tree_map_node::parent] = index;
	    	}

	    	if( last_right != INVALID )
	    	{
	    		_indices.as_type[last_right].sub_nodes[tree_map_node::parent] = index;
	    	}

	    	_indices.as_type[index].sub_nodes[tree_map_node::parent] = last_parent;
	    	_indices.as_type[index].sub_nodes[tree_map_node::left] = last_left;
	    	_indices.as_type[index].sub_nodes[tree_map_node::right] = last_right;

	    	_indices.as_type[last_index].sub_nodes[tree_map_node::parent] = INVALID;
	    	_indices.as_type[last_index].sub_nodes[tree_map_node::left] = INVALID;
	    	_indices.as_type[last_index].sub_nodes[tree_map_node::right] = INVALID;

	        copy_construct_object( _keys.as_type + last_index, _keys.as_type + index );
	        copy_construct_object( _values.as_type + last_index, _values.as_type + index );
	        destruct_object( _keys.as_type + last_index );
	        destruct_object( _values.as_type + last_index );
	    }

	    //destroy former last node
	    --_size;
	}
}

template <typename K, typename V>
void tree_map<K,V>::erase( const K& key )
{
    uint32_t used_index = find( key );

    if( used_index == INVALID )
        return;

    erase_at( used_index );

    return;
}


template <typename K, typename V>
uint32_t tree_map<K,V>::begin( void ) const
{
	uint32_t return_index = _root;

	while( _indices.as_type[return_index].sub_nodes[tree_map_node::left] != INVALID )
	{
		return_index = _indices.as_type[return_index].sub_nodes[tree_map_node::left];
	}

	return return_index;
}

template <typename K, typename V>
uint32_t tree_map<K,V>::last( void ) const
{
	uint32_t return_index = _root;

	while( _indices.as_type[return_index].sub_nodes[tree_map_node::right] != INVALID )
	{
		return_index = _indices.as_type[return_index].sub_nodes[tree_map_node::right];
	}

	return return_index;
}

template <typename K, typename V>
uint32_t tree_map<K,V>::end( void ) const
{
	return INVALID;
}

template <typename K, typename V>
uint32_t tree_map<K,V>::next( uint32_t index ) const
{
	if( index < _size )
	{
		if( _indices.as_type[index].sub_nodes[tree_map_node::right] != INVALID )
		{
			uint32_t return_index = _indices.as_type[index].sub_nodes[tree_map_node::right];
			while( _indices.as_type[return_index].sub_nodes[tree_map_node::left] != INVALID )
			{
				return_index = _indices.as_type[return_index].sub_nodes[tree_map_node::left];
			}
			return return_index;
		}

		uint32_t return_index = _indices.as_type[index].sub_nodes[tree_map_node::parent];
		uint32_t previous_index = index;

		while( return_index != INVALID && previous_index == _indices.as_type[return_index].sub_nodes[tree_map_node::right] )
		{
			previous_index = return_index;
			return_index = _indices.as_type[previous_index].sub_nodes[tree_map_node::parent];
		}

		return return_index;
	}

	return INVALID;
}

template <typename K, typename V>
uint32_t tree_map<K,V>::previous( uint32_t index ) const
{
	if( index < _size )
	{
		if( _indices.as_type[index].sub_nodes[tree_map_node::left] != INVALID )
		{
			uint32_t return_index = _indices.as_type[index].sub_nodes[tree_map_node::left];
			while( _indices.as_type[return_index].sub_nodes[tree_map_node::right] != INVALID )
			{
				return_index = _indices.as_type[return_index].sub_nodes[tree_map_node::right];
			}
			return return_index;
		}

		uint32_t return_index = _indices.as_type[index].sub_nodes[tree_map_node::parent];
		uint32_t previous_index = index;

		while( return_index != INVALID && previous_index == _indices.as_type[return_index].sub_nodes[tree_map_node::left] )
		{
			previous_index = return_index;
			return_index = _indices.as_type[previous_index].sub_nodes[tree_map_node::parent];
		}

		return return_index;
	}

	return INVALID;
}

template <typename K, typename V>
uint32_t tree_map<K,V>::size(void) const
{
	return _size;
}

template <typename K, typename V>
uint32_t tree_map<K,V>::max_size(void) const
{
    return _size_max;
}

template <typename K, typename V>
K* tree_map<K,V>::get_key( uint32_t index )
{
	if( index < _size )
	{
		return _keys.as_type + index;
	}

	return 0;
}

template <typename K, typename V>
const K* tree_map<K,V>::get_key( uint32_t index ) const
{
	if( index < _size )
	{
		return _keys.as_type + index;
	}

	return 0;
}

template <typename K, typename V>
V* tree_map<K,V>::get_value( uint32_t index )
{
	if( index < _size )
	{
		return _values.as_type + index;
	}

	return 0;
}

template <typename K, typename V>
const V* tree_map<K,V>::get_value( uint32_t index ) const
{
	if( index < _size )
	{
		return _values.as_type + index;
	}

	return 0;
}

template <typename K, typename V>
V& tree_map<K,V>::operator[]( const K& index )
{
    return *( find(index) );
}

template <typename K, typename V>
const V& tree_map<K,V>::operator[]( const K& index ) const
{
    return *( find(index) );
}

template <typename K, typename V>
pointer_t<void> tree_map<K,V>::memory( void ) const
{
    return _indices.as_void;
}

template <typename K, typename V>
uint32_t tree_map<K,V>::size_of_elements( uint32_t number )
{
    return (sizeof(tree_map_node)+sizeof(K)+sizeof(V)) * number;
}

}	// namespace crap

#endif /* CORE_INCLUDE_CONTAINER_TREEMAP_H_ */
