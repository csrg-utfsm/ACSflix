//
// Created by Rodolfo Castillo Mateluna on 9/27/16.
//

#ifndef PUBLISHER_BUFFER_H
#define PUBLISHER_BUFFER_H

//#include <utility> // c++11 swap
#include <algorithm> // < c++11 swap
#include <string>
#include <cstdlib>

class Buffer
{
	char* buffer;
	size_t bsize;
	size_t blength;

	/**
	 * Default constructor. Private
	 * just for move semantics
	 * @return
	 */
	Buffer();

public:
	/**
	 * Initializes buffer with size
	 * @param size buffer's size
	 * @return
	 */
	Buffer(size_t size);

	/**
	 * Copy constructor
	 * @param other
	 * @return
	 */
	Buffer(const Buffer& other);

	/**
	 * Destructor
	 */
	virtual ~Buffer();

	/**
	 * Swap function
	 * @param first
	 * @param second
	 */
	friend void swap(Buffer& first, Buffer& second);

	/**
	 * Copy assignment operator
	 * @param other
	 * @return
	 */
	Buffer& operator=(Buffer other);

	/**
	 * Size getter
	 * @return bsize
	 */
	size_t size() const;

	/**
	 * Length setter. This is the truly used size
	 * @param len should always be lesser than size
	 */
	void length(size_t len);

	/**
	 * Length getter
	 * @return blength
	 */
	size_t length() const;

	/**
	 * Element getter
	 * @param i index
	 * @return buffer[i]
	 */
	char& operator[](size_t i);

	/**
	 * Legacy access
	 * @return buffer
	 */
	operator char*();

	char* data() const;
};


#endif //PUBLISHER_BUFFER_H
