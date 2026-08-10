// Map.h
#ifndef MAP_H
#define MAP_H

#include <map>

/**
 * @class Map
 * @brief A minimal wrapper around std::map that provides key-value association
 *
 * @tparam K Key type - must support comparison operations
 * @tparam V Value type
 *
 * This class provides a minimal interface for map operations while hiding
 * the underlying std::map implementation. No duplicate keys are allowed.
 */

template <class K, class V>
class Map {
public:
    /**
     * @brief Default constructor
     * @post Empty map is created
     */
    Map();

    /**
     * @brief Insert a key-value pair
     * @param key The key to insert
     * @param value The value to associate with the key
     * @return bool True if insertion was successful, false if key already exists
     * @pre Key type K must support comparison operations
     * @post If successful, map contains new key-value pair
     */
    bool inserts(const K& key, const V& value);

    /**
     * @brief Check if a key exists in the map
     * @param key The key to search for
     * @return bool True if key exists, false otherwise
     * @pre Key type K must support comparison operations
     * @post Map remains unchanged
     */
    bool contains(const K& key) const;

    /**
     * @brief Get value associated with a key
     * @param key The key to search for
     * @return V& Reference to the value associated with the key
     * @pre Key must exist in map
     * @post Map remains unchanged, returns reference to existing value
     */
     V& get(const K& key);

    /**
     * @brief Get value associated with a key (const version)
     * @param key The key to search for
     * @return const V& Const reference to the value associated with the key
     * @pre Key must exist in map
     * @post Map remains unchanged, returns const reference to existing value
     */
     const V& get(const K& key) const;

private:

    /**
     * @brief Underlying container used for key–value storage.
     *
     * Implements the actual associative mapping between keys (K) and values (V)
     * using the C++ Standard Library's std::map. Provides ordered key-based access
     * and efficient insert, search, and erase operations in O(log n) time.
     */
     std::map<K, V> data;
};

//================
// Implementation
//================

// Template declaration for a generic Map class with key type K and value type V
template <class K, class V>
Map<K, V>::Map()
:data()   // Member initializer list initializes the internal std::map<K, V> container as empty
{}

// Template declaration for the inserts() method
template <class K, class V>
bool Map<K, V>::inserts(const K& key, const V& value) {
    try {
        // Only insert when the key does not already exist
        if (data.count(key) > 0) {
            return false;
        }
        data.insert(std::make_pair(key, value));
        return true;
    }catch (const std::exception& e) {
        // Log the error and rethrow with more context
        std::cerr << "Error in Map::inserts: " << e.what();
        throw std::runtime_error("Failed to insert key-value pair into map");
    }catch (...) {
        // Handle any non-standard exceptions
        throw std::runtime_error("Unknown error during map insertion");
    }
}

// Template declaration for the contains() method
template <class K, class V>
bool Map<K, V>::contains(const K& key) const {
    try {
        return data.count(key) > 0;
    }catch (const std::exception& e) {
        // Log comparison errors during contains check
        std::cerr << "Error in Map::contains during key comparison: " << e.what();
        return false; // If we can't compare, key doesn't exist
    }
}

// Template declaration for the non-const get() method
template <class K, class V>
V& Map<K, V>::get(const K& key) {
    // Access the value associated with the given key using std::map::at
    // Throws std::out_of_range if the key does not exist
    try {
        // Access the value associated with the given key using std::map::at
        // Throws std::out_of_range if the key does not exist
        return data.at(key);
    }catch (const std::out_of_range& e) {
        // Re-throw with a more descriptive message
        std::cerr << "Map::get - Key not found: " << e.what() << std::endl;
        throw std::out_of_range("Key does not exist in map");
    }catch (const std::exception& e) {
        throw std::runtime_error("Failed to retrieve value from map");
    }

}

// Template declaration for the const get() method (read-only access)
template <class K, class V>
const V& Map<K, V>::get(const K& key) const {
    // Same as the non-const version, but returns a const reference
    // Ensures callers cannot modify the stored value
   try {
        // Same as the non-const version, but returns a const reference
        return data.at(key);
    }catch (const std::out_of_range& e) {
        std::cerr << "Map::get (const) - Key not found: " << e.what() << std::endl;
        throw std::out_of_range("Key does not exist in map");
    }catch (const std::exception& e) {
        throw std::runtime_error("Failed to retrieve value from map");
    }
}
  // Returns a const reference to the stored value


#endif // MAP_H
