	/**
	 * @class Vector
	 * @brief  A template dynamic array data structure
	 *
	 * Provides controlled access to a dynamic array with auto resizing.
	 * The vector grows automatically when capacity is reached using
	 * a growth factor of 1.5x. Includes bounds checking for safe access.
	 *
	 * Template type T must support copy assignment and default construction.\n
	 * Memory is managed automatically - no manual memory management required.\n
	 * Bounds checking is performed using assertions in debug mode.\n
	 */
#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>  //for bounds checking
#include <vector>
#include <cstddef>   //defines size_t


template <class T>
class Vector
{
public:

		/**
		 * @brief  Constructor sets starting capacity
		 *
		 * Creates a new vector with specified initial capacity.
		 * Default capacity is 10 if not specified.
		 *
		 * @param  capacity - Initial size of the vector
		 * @return void
		 * @pre Capacity must be positive integer
		 * @post Vector is initialized with specified capacity
		 */
        Vector();

		/**
		 * @brief  Subscript operator for non-const access
		 *
		 * Provides read-write access to elements. Includes bounds checking.
		 *
		 * @param  index - Index to access
		 * @return T& - Reference to element at index
		 * @pre index must be in range 0 to size()-1
		 * @post Allows modification of element at specified index
		 */
	     T& operator[](int index);

		/**
		 * @brief  Subscript operator for const access
		 *
		 * Provides read-only access to elements. Includes bounds checking.
		 *
		 * @param  index - Index to access
		 * @return const T& - Const reference to element at index
		 * @pre index must be in range 0 to size()-1
		 */
	     const T& operator[](int index) const;

		/**
		 * @brief  Get number of element present
		 *
		 * Returns the current number of elements stored in the vector.
		 *
		 * @return int - Number of elements in vector
		 */
	     int size() const;


		/**
		 * @brief  Add element to end of vector
		 *
		 * Appends element to the end of vector. Automatically grows
		 * the vector if capacity is reached.
		 *
		 * @param  element - element to add
		 * @return void
		 * @post Vector size increases by 1, may trigger growth
		 */
	     void pushBack(const T& element);

		/**
		 * @brief  Check if vector is empty
		 *
		 * Determines if the vector contains any elements.
		 *
		 * @return bool - true if vector is empty, otherwise false
		 */
	     bool isEmpty() const;

private:


	     std::vector<T> m_vector; ///< STL vector as internal storage

};
//=================
// IMPLEMENTATION
//=================

/**
* @brief  Constructor creates vector with specified capacity
*
* @param  capacity - Initial capacity of vector
* @return void
*/

template <class T>
Vector<T>::Vector()
:m_vector()
{}

/**
* @brief  Subscript operator for non-const access - allows modification of elements
*
* @param  index - Index of element to access
* @return T& - Reference to element at index
*/

template <class T>
T& Vector<T>::operator[](int index)
{
    //chnaged from int to size_t because m_vector.size() returns an unsigned type and to eliminate compiler warning for type safety
    assert(index >= 0 && static_cast<size_t>(index) < m_vector.size());
    return m_vector[static_cast<size_t>(index)];
}

/**
* @brief  Subscript operator for const access, read-only element access
*
* @param  index - Index of element to access
* @return const T& - Const reference to element at index
*/

template <class T>
const T& Vector<T>::operator[](int index) const
{
    //chnaged from int to size_t because m_vector.size() returns an unsigned type and to eliminate compiler warning for type safety
    assert(index >= 0 && static_cast<size_t>(index) < m_vector.size());
    return m_vector[static_cast<size_t>(index)];
}

/**
* @brief  Return current number of elements in the vector
*
* @return int - Number of elements in vector
*/

template <class T>
int Vector<T>::size() const
{
    //chnaged from int to size_t because m_vector.size() returns an unsigned type and to eliminate compiler warning for type safety
    return static_cast<int>(m_vector.size());
}

template <class T>
void Vector<T>::pushBack(const T& element)
{
    m_vector.push_back(element);
}

/**
 * @brief  Check if vector cotains any elements
 *
 * @return bool - true if vector is empty, false otherwise
*/

template <class T>
bool Vector<T>::isEmpty() const
{
    return m_vector.empty();
}

#endif // VECTOR_H
