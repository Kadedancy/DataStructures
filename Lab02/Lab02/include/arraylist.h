#include <ostream>

namespace ssuds
{
    template <class T>
    class ArrayList
    {
    protected:
        unsigned int mSize;
        unsigned int mCapacity;
        T* mData;

        void resize()
        {
            if (mSize == mCapacity)
            {
                T* tempArray = new T[mCapacity + 5];

                for (int i = 0; i < mSize; i++)
                {
                    tempArray[i] = mData[i];
                }

                delete[] mData;
                mData = tempArray;
                mCapacity += 5;
            }
        }


    public:
        ArrayList()
        {
            mData = nullptr;
            mSize = 0;
            mCapacity = 0;
        }

        ~ArrayList()
        {
            if (mData)
            {
                delete[] mData;
            }
        }

        void append(const T& s)
        {
            resize();
            mData[mSize++] = s;
        }

        unsigned int size() const
        {
            return mSize;
        }

        int find(const T& s, int start_pos = 0)
        {
            for (int i = start_pos; i < mSize; i++)
            {
                if (mData[i] == s)
                {
                    return i;
                }
            }
            return -1;
        }

        /// <summary>
        /// Updated get method
        /// </summary>
        const T& operator[](int index) const
        {
            return mData[index];
        }

        void clear()
        {
            if (mData)
            {
                delete[] mData;
            }
            mData = nullptr;
            mSize = 0;
            mCapacity = 0;
        }

        void insert(const T& s, int index)
        {
            resize();

            for (int i = mSize; i > index; i--)
            {
                mData[i] = mData[i - 1];
            }

            mData[index] = s;
            mSize++;
        }

        T remove(int index)
        {
            T result = mData[index];

            for (int i = index; i < mSize - 1; i++)
            {
                mData[i] = mData[i + 1];
            }

            T* tempArray = new T[mSize - 1];

            for (int i = 0; i < mSize - 1; i++)
            {
                tempArray[i] = mData[i];
            }

            delete[] mData;
            mData = tempArray;
            mSize--;

            return result;
        }

        int remove_all(T s)
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

        /// <summary>
        /// Overloaded << operator
        /// </summary>
        friend std::ostream& operator<<(std::ostream& os, const ArrayList& A)
        {
            os << "[";

            for (unsigned int i = 0; i < A.size(); ++i)
            {
                os << A[i];

                if (i < A.size() - 1)
                {
                    os << ", ";
                }
            }

            os << "]";
            return os;
        }

        /// <summary>
        /// Copy constructor for deep copy
        /// </summary>
        ArrayList(const ArrayList& other)
        {
            mSize = other.mSize;
            mCapacity = other.mCapacity;
            mData = new T[mCapacity];

            for (int i = 0; i < mSize; i++)
            {
                mData[i] = other.mData[i];
            }
        }

        /// <summary>
        /// Copy = operator for deep copy
        /// </summary>
        ArrayList& operator=(const ArrayList& other)
        {
            if (this != &other)
            {
                if (mData)
                {
                    delete[] mData;
                }

                mSize = other.mSize;
                mCapacity = other.mCapacity;
                mData = new T[mCapacity];

                for (int i = 0; i < mSize; i++)
                {
                    mData[i] = other.mData[i];
                }
            }

            return *this;
        }
    };
};

/// <summary>
/// namespace for foo class declarations
/// </summary>
namespace testing
{
    class Foo {
    private:
        int val;
        std::string str;

    public:

        Foo();
        Foo(int v, std::string n);

        // value getter and setter
        int getVal() const;
        void setVal(int v);

        // string getter and setter
        const std::string& getStr() const;
        void setStr(const std::string& n);
    };
}

