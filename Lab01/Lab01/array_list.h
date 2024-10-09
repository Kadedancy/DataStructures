#pragma once
namespace ssuds
{
	class ArrayList
	{
	protected:
		// This is the number of ELEMENTS in the array of strings
		unsigned int mSize;
		std::string* mData;
	public:
		ArrayList();
		~ArrayList();
		void append(std::string s);
		unsigned int size();
	};
}