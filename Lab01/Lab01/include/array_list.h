#pragma once
#include <string>

namespace ssuds
{
	class ArrayList
	{
	protected:
		///size of mData
		int mSize;

		///array of data 
		std::string* mData;

		/// <summary>
		/// make ArrayList increase by 1.
		/// </summary>
		void resize();

	public:
		///constructor
		ArrayList();

		/// Destructor
		~ArrayList();

		/// <summary>
		/// Adds string to ArrayList
		/// </summary>
		void append(std::string s);

		/// <summary>
		/// Returns the size of ArrayList
		/// </summary>
		unsigned int size();

		/// <summary>
		/// Finds the first instance of the string
		/// </summary>
		int find(std::string s, int start_pos = 0);

		/// <summary>
		/// Gets the data at the location value
		/// </summary>
		std::string get(int index);

		/// <summary>
		/// Clears ArrayList
		/// </summary>
		void clear();

		/// <summary>
		/// Inserts data at an location value
		/// </summary>
		void insert(std::string s, int index);

		/// <summary>
		/// Removes data at the location value
		/// </summary>
		std::string remove(int index);

		/// <summary>
		/// Removes all instances of a value.
		/// </summary>
		int remove_all(std::string s);

	};
}