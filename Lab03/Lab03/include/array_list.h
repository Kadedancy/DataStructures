#pragma once
#include <string>
#include <ostream>

namespace ssuds
{
	/// An ArrayList is an array-based data structure. 
	template <class T>
	class ArrayList
	{
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ ATTRIBUTES                              @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	protected:
		/// The default (and minimum) capacity of an ArrayList
		static const int msMinCapacity = 5;

		/// The current number of "slots" AVAILABLE in mData (i.e. the array size)
		int mCapacity;

		/// How many slots are we USING?  This will always be less than or equal to mCapacity
		int mSize;

		/// The array of data we're currently holding
		T* mData;


		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ OPERATOR OVERLOADS                      @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:

		/// <summary>
		/// Overloads the stream operator for ArrayLists.
		/// </summary>
		/// <param name="os">an ostream object (ofstream, stringstream, cout, etc.) </param>
		/// <param name="alist">the ArrayList</param>
		/// <returns>the (possibly modified) os that was given to us</returns>
		friend std::ostream& operator <<(std::ostream& os, const ArrayList<T>& alist)
		{
			os << "[";
			for (int i = 0; i < alist.size(); i++)
			{
				os << alist[i];
				if (i < alist.size() - 1)
					os << ", ";
			}
			os << "]";
			return os;
		}

		/// <summary>
		/// Gets the data item at the given index.  This will throw an std::out_of_bounds exception if index is invalid (less than 0 or >= size)
		/// </summary>
		/// <param name="index">the index of the thing to return</param>
		/// <returns>a reference to the value at the given index</returns>
		T& operator[](int index) const
		{
			if (index >= mSize || index < 0)
				throw std::out_of_range("Invalid index: " + std::to_string(index));

			return mData[index];
		}


		ArrayList<T>& operator= (const ArrayList<T>& other)
		{
			clear();
			mData = new T[other.mCapacity];
			for (int i = 0; i < other.mSize; i++)
				mData[i] = other[i];
			mCapacity = other.mCapacity;
			mSize = other.mSize;
			return *this;
		}


		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ CONSTRUCTORS / DESTRUCTORS              @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:
		/// Default constructor
		ArrayList() : mSize(0), mCapacity(0), mData(nullptr)
		{
			// intentionally empty
		};

		/// Copy-constructor
		ArrayList(const ArrayList& other) : mCapacity(other.mCapacity), mSize(other.mSize)
		{
			mData = new T[mCapacity];
			for (int i = 0; i < other.size(); i++)
				mData[i] = other[i];
		}

		/// Destructor
		~ArrayList()
		{
			if (mData)
				delete[] mData;
		}


		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ OTHER METHODS (alphabetical)            @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:
		/// <summary>
		///  Inserts a new element at the end of the array
		/// </summary>
		/// <param name="val">the new value to add</param>
		void append(const T val)
		{
			// check to see if we need to increase our capacity
			grow();

			// Stick our new element in the last slot and (sneakily) increase our size in the process
			mData[mSize] = val;
			mSize++;
		}

		/// <summary>
		/// Clears the array back to its original state
		/// </summary>
		void clear()
		{
			if (mData)
				delete[] mData;
			mData = nullptr;
			mSize = 0;
			mCapacity = 0;
		}

		/// <summary>
		/// Finds the index of the first occurrence of the given value
		/// </summary>
		/// <param name="val">the value to search for</param>
		/// <param name="start_index">the index to start searching at</param>
		/// <returns></returns>
		int find(const T val, int start_index = 0) const
		{
			if (start_index >= mSize || start_index < 0)
				throw std::out_of_range("Invalid index: " + std::to_string(start_index));

			for (int i = start_index; i < mSize; i++)
			{
				if (mData[i] == val)
					return i;
			}

			// We didn't find it
			return -1;
		}



		/// <summary>
		/// Inserts a new data item at a given index
		/// </summary>
		/// <param name="val">the new value to insert</param>
		/// <param name="index">the index at which to insert (must be >= 0 and <= size) </param>
		void insert(T val, int index)
		{
			if (index > mSize)
				throw std::out_of_range("Invalid index: " + std::to_string(index));

			// check to see if we need to increase capacity first
			grow();

			// Move all the elements that come *after* index up one spot
			for (int i = mSize; i > index; i--)
				mData[i] = mData[i - 1];

			// Put our new elements in spot index and increase our size
			mData[index] = val;
			mSize++;
		}

		/// <summary>
		/// Removes a data item at the given index
		/// </summary>
		/// <param name="index">the index of the thing to remove (will return a std::out_of_bounds exception if invalid (<0 or >= size)</param>
		/// <param name="resize_if_necessary">if true, the array will be resized if it is now below half capacity</param>
		/// <returns>the data item that was just removed</returns>
		T remove(int index, bool resize_if_necessary = true)
		{
			if (index >= mSize || index < 0)
				throw std::out_of_range("Invalid index: " + std::to_string(index));

			// Get the value we'll return at the end (the element removed)
			T result = mData[index];

			// Move all elements that come after index down one spot
			for (int i = index; i < mSize - 1; i++)
				mData[i] = mData[i + 1];

			// Decrement our size
			mSize--;

			// Shrink, if applicable and requested
			if (resize_if_necessary)
				shrink();

			// Return the result
			return result;
		}

		/// <summary>
		/// Removes all occurrences of a given value.  Uses find and remove internally to do the removal
		/// </summary>
		/// <param name="val">the value to remove</param>
		/// <param name="resize_if_necessary">if true, the array will be resized if it is now below half capacity</param>
		/// <returns>the number of occurrences of that data item that were removed</returns>
		int remove_all(const T val, bool resize_if_necessary = true)
		{
			int cur_index = 0;
			int num_removed = 0;
			while (cur_index >= 0 && cur_index < mSize)
			{
				// Find the next occurrence of val, starting at the current position
				cur_index = find(val, cur_index);
				if (cur_index >= 0)
				{
					// We found one!
					remove(cur_index, false);
					num_removed++;
				}
			}

			if (resize_if_necessary)
				shrink();

			return num_removed;
		}

		/// <summary>
		/// Returns the size of the internal array (i.e.) how many things are being stored in the ArrayList
		/// </summary>
		/// <returns>the size of the ArrayList</returns>
		int size() const
		{
			return mSize;
		}


	protected:
		/// <summary>
		/// An internal method to resize the array if we are currently at capacity (if we are not, nothing is done)
		/// </summary>
		void grow()
		{
			if (mSize == mCapacity)
			{
				// Allocate what will become the new array
				T* new_array = nullptr;
				if (mCapacity == 0)
					new_array = new T[msMinCapacity];
				else
					new_array = new T[mCapacity * 2];

				// Copy over data from the old array (if any)
				if (mData != nullptr)
				{
					for (int i = 0; i < mSize; i++)
						new_array[i] = mData[i];

					// Destroy the old array
					delete[] mData;
				}

				// Make the new array *the* array
				mData = new_array;

				// Note that our capacity is now double what it used to be
				if (mCapacity == 0)
					mCapacity = msMinCapacity;
				else
					mCapacity *= 2;
			}
		}


		/// <summary>
		/// An internal method to see if the array can be shrunk (capacity reduced by half, down to msMinCapacity)
		/// </summary>
		void shrink()
		{
			if (mSize < mCapacity / 2 && mCapacity >= msMinCapacity * 2)
			{
				// Allocate what will become the new array
				T* new_array = new T[mCapacity / 2];

				// Copy over data from the old array (if any)
				for (int i = 0; i < mSize; i++)
					new_array[i] = mData[i];


				// Destroy the old array
				delete[] mData;

				// Make the new array *the* array
				mData = new_array;

				// Note that our capacity is now double what it used to be
				mCapacity /= 2;
			}
		}
	public:
		/// Iterator class
		class Iterator
		{
		public:
			Iterator(T* ptr, int index) : ptr_(ptr + index) {}

			Iterator& operator++()
			{
				++ptr_;
				return *this;
			}

			Iterator& operator--()
			{
				--ptr_;
				return *this;
			}

			T& operator*() const
			{
				return *ptr_;
			}

			bool operator!=(const Iterator& other) const
			{
				return ptr_ != other.ptr_;
			}

		private:
			T* ptr_;
		};
		Iterator begin()
		{
			return Iterator(mData, 0);
		}

		Iterator end()
		{
			return Iterator(mData, mSize);
		}
	};
}
namespace testing
{
	/// Just a silly class to test that our data structures are fully templatized
	/// and accept non-trivial classes
	class Foo
	{
	protected:
		/// The integer value of the Foo object
		int value;

		/// The string name of the Foo object
		std::string name;
	public:
		/// The default constructor
		Foo();

		/// The fully-qualified constructor
		Foo(int v, std::string n);

		/// <summary>
		///  Gets the value of the value attribute
		/// </summary>
		/// <returns>current value of the value attribute</returns>
		int get_value() const;

		/// <summary>
		/// Sets the value of the value attribute
		/// </summary>
		/// <param name="v">New value for the value attribute</param>
		void set_value(int v);

		/// <summary>
		/// Gets the value of the name attribute
		/// </summary>
		/// <returns>The value of the name attribute</returns>
		std::string get_name() const;

		/// <summary>
		/// Sets the value of the name attribute
		/// </summary>
		/// <param name="s">The new value for the name attribute</param>
		void set_name(std::string s);
	};

	/// <summary>
	///  Overload the stream operator for Foo objects
	/// </summary>
	/// <param name="os">the output stream (cout, fp, stringstream, etc.)</param>
	/// <param name="f">the Foo object we're outputting to the stream</param>
	/// <returns>the (unchanged) ostream we were given (to support stream "chaining")</returns>
	std::ostream& operator<<(std::ostream& os, const Foo& f);
}
