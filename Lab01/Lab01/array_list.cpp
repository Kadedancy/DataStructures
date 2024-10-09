#include "include/array_list.h"
#include <string>


ssuds::ArrayList::ArrayList()
{
	mData = nullptr;
	mSize = 0;
}

ssuds::ArrayList::~ArrayList()
{
	if(mData)
	{
		delete[] mData;
	}
}

void ssuds::ArrayList::resize()
{
	std::string* tempArray = new std::string[mSize + 1];

	for (int i = 0; i < mSize; i++)
	{
		tempArray[i] = mData[i];
	}

	delete[] mData;
	mData = tempArray;
}

void ssuds::ArrayList::append(std::string s)
{
	resize();
	mData[mSize++] = s;
}

unsigned int ssuds::ArrayList::size()
{
	return mSize;
}

int ssuds::ArrayList::find(std::string s, int start_pos)
{
	for(int i = start_pos; i < mSize; i++)
	{
		if (mData[i] == s)
		{
			return i;
		}
	}
	return -1;
}

std::string ssuds::ArrayList::get(int index)
{
	return mData[index];
}

void ssuds::ArrayList::clear()
{
	if (mData)
	{
		delete[] mData;
	}
	mData = nullptr;
	mSize = 0;
}

void ssuds::ArrayList::insert(std::string s, int index)
{
	resize();

	for (int i = mSize; i > index; i--)
	{
		mData[i] = mData[i - 1];
	}

	mData[index] = s;
	mSize++;
}

std::string ssuds::ArrayList::remove(int index)
{
	std::string result = mData[index];

	for (int i = index; i < mSize - 1; i++)
	{
		mData[i] = mData[i + 1];
	}

	std::string* tempArray = new std::string[mSize - 1];

	for (int i = 0; i < mSize - 1; i++)
	{
		tempArray[i] = mData[i];
	}

	delete[] mData;
	mData = tempArray;
	mSize--;

	return result;
}

 int ssuds::ArrayList::remove_all(std::string s)
{
	int i = 0;
	int boolvar = 0;
	while (i >= 0 && i < mSize)
	{
		i = find(s, i);
		if (i >= 0)
		{
			remove(i);
		}
	}
	if (mSize == 0)
	{
		boolvar = 1;
	}
	return boolvar;
}