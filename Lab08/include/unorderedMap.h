#pragma once

namespace ssuds
{
    template <class K, class V>
    class UnorderedMap
    {
    protected:
        // Option1: an array of pair POINTERS
        std::pair<K, V>** mTable;

        // Other attributes (for either approach)
        unsigned int mSize;
        unsigned int mCapacity;
        std::hash<K> mHashGenerator;


        /// <summary>
        /// Iterator class
        /// </summary>
        class Iterator
        {
        private: 
            /// <summary>
            /// pointer to pair pointer for current pair
            /// </summary>
            std::pair<K, V>** current;

        public:
            /// <summary>
            /// Constructor
            /// </summary>
            /// <param name="ptr"></param>
            Iterator(std::pair<K, V>** ptr) : current(ptr)
            {

            }

            ////////////////////////////////////////////
            /// OPERATOR OVERLOADS FOR ITERATOR CLASS //
            ////////////////////////////////////////////

            Iterator& operator++()
            {
                ++current;
                while (*current == nullptr)
                {
                    ++current;
                }
                return *this;
            }

            Iterator operator++(int) 
            {
                Iterator temp = *this;
                ++(*this);
                return temp;
            }

            std::pair<K, V>& operator*() const 
            {
                return **current;
            }

            std::pair<K, V>* operator->() const 
            {
                return *current;
            }

            bool operator==(const Iterator& other) const
            {
                return current == other.current;
            }

            bool operator!=(const Iterator& other) const
            {
                return !(*this == other);
            }

        };

        /// <summary>
        /// grow method for resizing array, rehashing keys, handling collisions
        /// </summary>
        /// <param name="newCapacity"></param>
        void grow(unsigned int newCapacity)
        {
            // Create a new table with the new capacity
            std::pair<K, V>** newTable = new std::pair<K, V>* [newCapacity]();

            // Rehash existing key-value pairs into the new table
            for (unsigned int i = 0; i < mCapacity; ++i)
            {
                if (mTable[i] != nullptr)
                {
                    // Extract the pair from the current table
                    std::pair<K, V>* currentPair = mTable[i];
                    K key = currentPair->first;
                    V value = currentPair->second;

                    // Calculate the new index for the pair in the new table
                    unsigned int newIndex = mHashGenerator(key) % newCapacity;

                    // Handle collisions using linear probing
                    while (newTable[newIndex] != nullptr)
                    {
                        newIndex = (newIndex + 1) % newCapacity; // Linear probing to find the next empty slot
                    }

                    // Insert the pair into the new table
                    newTable[newIndex] = new std::pair<K, V>(key, value);
                }
            }

            // Delete the old table and update member variables
            delete[] mTable;
            mTable = newTable;
            mCapacity = newCapacity;
        }

    public:
        /// <summary>
        /// Constructor that initializes mSize, mCapacity, mTable
        /// </summary>
        /// <param name="capacity"></param>
        UnorderedMap(unsigned int capacity = 10) : mSize(0), mCapacity(capacity)
        {
            // Initialize the array of pair pointers
            mTable = new std::pair<K, V>* [mCapacity]();
            for (unsigned int i = 0; i < mCapacity; ++i)
            {
                mTable[i] = nullptr;
            }
        }

        /// <summary>
        /// Destructor
        /// </summary>
        ~UnorderedMap()
        {
            // Deallocate memory for the array of pair pointers
            if (mTable != nullptr)
            {
                for (unsigned int i = 0; i < mCapacity; ++i)
                {
                    delete mTable[i];
                }
                delete[] mTable;
            }
        }

        /// <summary>
        /// Iterator begin method
        /// </summary>
        /// <returns></returns>
        Iterator begin() 
        {
            return Iterator(mTable);
        }

        /// <summary>
        /// Iterator end method
        /// </summary>
        /// <returns></returns>
        Iterator end() 
        {
            return Iterator(mTable + mCapacity);
        }

        /// <summary>
        /// Operator overload, Handles hashing, getting/setting
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        V& operator[](const K& key)
        {
            unsigned long long int index = mHashGenerator(key) % mCapacity; // Mod it with the table size to get desired index
            while (mTable[index] != nullptr)
            {
                if (mTable[index]->first == key)
                {
                    return mTable[index]->second; // Return reference to value if key found
                }
                index = (index + 1) % mCapacity; // Move to the next slot using linear probing
            }

            mTable[index] = new std::pair<K, V>(key, V());
            mSize++; // Increase size of map

            // Check if resizing is needed
            if (mSize > mCapacity * 0.7) // When capacity is 70% full, grow
            {
                grow(mCapacity * 2);
                // After growing, recalculate the index for the key
                index = mHashGenerator(key) % mCapacity;
                while (mTable[index] != nullptr)
                {
                    if (mTable[index]->first == key)
                    {
                        return mTable[index]->second;
                    }
                    index = (index + 1) % mCapacity;
                }
            }

            return mTable[index]->second; // Return reference to the newly inserted value
        }

        /// <summary>
        /// Size getter
        /// </summary>
        /// <returns></returns>
        int size() const
        {
            return mSize;
        }

        /// <summary>
        /// Capacity getter
        /// </summary>
        /// <returns></returns>
        int capacity() const
        {
            return mCapacity;
        }

        /// <summary>
        /// Remove method
        /// </summary>
        /// <param name="key"></param>
        void remove(const K& key)
        {
            unsigned long long int index = mHashGenerator(key) % mCapacity; // Get index for removal
            while (mTable[index] != nullptr)
            {
                // Check if keys match at index
                if (mTable[index]->first == key)
                {
                    delete mTable[index]; // Delete index
                    mTable[index] = nullptr; // Set index to nullpter
                    mSize--; // Decrement size
                    return;
                }
                index = (index + 1) % mCapacity; // Move to the next slot using linear probing
            }
        }

        /// <summary>
        /// Operator overload for printing map entries
        /// </summary>
        /// <param name="os"></param>
        /// <param name="map"></param>
        /// <returns></returns>
        friend std::ostream& operator<<(std::ostream& os, const UnorderedMap<K, V>& map)
        {
            os << "{";
            bool firstEntry = true;
            for (unsigned int i = 0; i < map.mCapacity; ++i)
            {
                if (map.mTable[i] != nullptr)
                {
                    if (!firstEntry)
                    {
                        os << ", ";
                    }
                    os << map.mTable[i]->first << ":" << map.mTable[i]->second;
                    firstEntry = false;
                }
            }
            os << "}";
            return os;
        }

        /// <summary>
        /// Find method
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        Iterator find(const K& key)
        {
            for (Iterator it = begin(); it != end(); ++it)
            {
                if (it->first == key) // Check if key matches
                {
                    return it; // Return the key
                }
            }
            return end(); // Return iterator pointing to the end if key not found
        }
    };
}