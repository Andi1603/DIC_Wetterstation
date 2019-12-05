/*
 CircularBuffer.h - Circular buffer library for Arduino.
 Copyright (c) 2017 Roberto Lo Giacco.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as 
 published by the Free Software Foundation, either version 3 of the 
 License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __CIRCULAR_BUFFER__
#define __CIRCULAR_BUFFER__
#include <inttypes.h>


// #ifndef CIRCULAR_BUFFER_XS
// #define __CB_ST__ uint16_t
// #else
#define __CB_ST__ uint8_t
// #endif

#ifdef CIRCULAR_BUFFER_DEBUG
#include <Print.h>
#endif

template<typename T, __CB_ST__ S> class CircularBuffer {
public:

	// CircularBuffer();

	CircularBuffer() : head(buffer), tail(buffer), count(0) {}

	~CircularBuffer() { }

	/**
	 * Adds an element to the beginning of buffer: the operation returns `false` if the addition caused overwriting an existing element.
	 */
	bool shift(T value)
	{
		if (head == buffer)
		{
			head = buffer + S;
		}
		*--head = value;
		if (count == S)
		{
			if (tail-- == buffer)
			{
				tail = buffer + S - 1;
			}
			return false;
		}
		else
		{
			if (count++ == 0)
			{
				tail = head;
			}
			return true;
		}
	}

	
	T unshift()
	{
		void(* crash) (void) = 0;
		if (count <= 0) crash();
		T result = *tail--;
		if (tail < buffer) {
			tail = buffer + S - 1;
		}
		count--;
		return result;
	}

	/**
	 * Returns the element at the beginning of the buffer.
	 */
	T inline first() {
		return *head;
	}

	/**
	 * Returns the element at the end of the buffer.
	 */
	T inline last() {
		return *tail;
	}

	/**
	 * Array-like access to buffer
	 */
	// T operator [] (__CB_ST__ index);

	T operator [](__CB_ST__ index) {
		return *(buffer + ((head - buffer + index) % S));
	}

	/**
	 * Returns how many elements are actually stored in the buffer.
	 */
	__CB_ST__ inline size() {
		return count;
	}

	/**
	 * Returns how many elements can be safely pushed into the buffer.
	 */
	__CB_ST__ inline available() {
		return S - count;
	}

	/**
	 * Returns how many elements can be potentially stored into the buffer.
	 */
	__CB_ST__ inline capacity() {
		return S;
	}

	/**
	 * Returns `true` if no elements can be removed from the buffer.
	 */
	bool inline isEmpty() {
		return count == 0;
	}

	/**
	 * Returns `true` if no elements can be added to the buffer without overwriting existing elements.
	 */
	bool inline isFull() {
		return count == S;
	}

	/**
	 * Resets the buffer to a clean status, dropping any reference to current elements
	 * and making all buffer positions available again.
	 */
	void inline clear() {
		memset(buffer, 0, sizeof(buffer));
		head = tail = buffer;
		count = 0;
	}

private:
	T buffer[S];
	T *head;
	T *tail;
	uint16_t count;
};

// #include <CircularBuffer.tpp>
#endif
