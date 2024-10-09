#pragma once
#include <iostream>
namespace ssuds
{
	enum class LinkedListIteratorType { forward, backward };

	template <class T>
	class LinkedList
	{
	protected:
		/// <summary>
		/// node class. contains node data and pointers.
		/// </summary>
		class Node
		{
		public:
			T mData;
			Node* mNext;
			Node* mPrev;
		};

		Node* mStart;
		Node* mEnd;
		unsigned int mSize;
		/// <summary>
		/// traverse method to go through list
		/// </summary>
		/// <param name="pos"></param>
		/// <returns></returns>
		Node* traverse(unsigned int pos)
		{
			Node* cur = mStart;
			for (unsigned int i = 0; i < pos && cur != nullptr; i++)
			{
				cur = cur->mNext;
			}
			return cur;
		}

	public:

		class LinkedListIterator
		{
		protected:
			/// <summary>
			/// A pointer to the controlling array list
			/// </summary>
			const LinkedList* mLinkedList;

			/// <summary>
			///  The current position / index in our traversal
			/// </summary>
			int mPosition;

			/// <summary>
			/// The type of traversal we're doing (forward or backwards)
			/// </summary>
			LinkedListIteratorType mType;

		public:
			/// <summary>
			///  The constructor (called indirectly by begin and rbegin in the LinkedList)
			/// </summary>
			/// <param name="arr">The array we're traversing</param>
			/// <param name="tp">The type of traversal to do</param>
			/// <param name="start_index">The starting index</param>
			LinkedListIterator(const LinkedList* arr, LinkedListIteratorType tp, int start_index) : mLinkedList(arr), mPosition(start_index), mType(tp)
			{
				// intentionally empty
			}

			/// Comparison with another iterator
			bool operator==(const LinkedListIterator& other) const
			{
				return mLinkedList == other.mLinkedList && mPosition == other.mPosition && mType == other.mType;
			}

			/// Not-comparison with another iterator
			bool operator!=(const LinkedListIterator& other) const
			{
				return mLinkedList != other.mLinkedList || mPosition != other.mPosition || mType != other.mType;
			}

			/// <summary>
			/// Advance operator.  Called by doing ++it
			/// </summary>
			void operator++()
			{
				if (mType == LinkedListIteratorType::forward)
					mPosition++;
				else
					mPosition--;
			}

			/// <summary>
			/// Advance operator.  Called by doing it++
			/// </summary>
			/// <param name=""></param>
			void operator++(int)
			{
				return (*this)++;
			}

			/// <summary>
			///  De-reference style operator
			/// </summary>
			/// <returns>A reference to the value at the current spot</returns>
			T& operator*()
			{
				return (*mLinkedList)[mPosition];
			}
			/// <summary>
			/// find node method
			/// </summary>
			/// <param name="val"></param>
			/// <returns></returns>
			LinkedListIterator find(const T& val) const
			{
				for (LinkedListIterator it = begin(); it != end(); it++)
				{
					if (*it == val)
					{
						return it;
					}
				}
				return end();
			}
			/// <summary>
			/// iterator beginning of list
			/// </summary>
			/// <returns></returns>
			LinkedListIterator begin() const
			{
				return LinkedListIterator(this, LinkedListIteratorType::forward, 0);
			}
			/// <summary>
			/// iterator end of list
			/// </summary>
			/// <returns></returns>
			LinkedListIterator end() const
			{
				return LinkedListIterator(this, LinkedListIteratorType::forward, size());
			}
			/// <summary>
			/// reverse iterator beginning of list
			/// </summary>
			/// <returns></returns>
			LinkedListIterator rbegin() const
			{
				return LinkedListIterator(this, LinkedListIteratorType::backward, size() - 1);
			}
			/// <summary>
			/// reverse iterator end of list
			/// </summary>
			/// <returns></returns>
			LinkedListIterator rend() const
			{
				return LinkedListIterator(this, LinkedListIteratorType::backward, -1);
			}
			/// <summary>
			/// index for position in list
			/// </summary>
			/// <returns></returns>
			LinkedListIterator index() const
			{
				return mPosition;
			}
		};
		/// <summary>
		/// default constructor
		/// </summary>
		LinkedList() : mStart(nullptr), mEnd(nullptr), mSize(0)
		{
			// empty, on purpose
		}
		/// <summary>
		/// deep copy constructor
		/// </summary>
		/// <param name="other"></param>
		LinkedList(const LinkedList& other) : mStart(nullptr), mEnd(nullptr), mSize(0)
		{
			for (unsigned int i = 0; i < other.size(); ++i) 
			{
				append(other[i]);
			}
		}
		/// <summary>
		/// initailizer_list constructor
		/// </summary>
		/// <param name="values"></param>
		LinkedList(std::initializer_list<T> values) : mStart(nullptr), mEnd(nullptr), mSize(0)
		{
			for (const T& val : values) 
			{
				append(val);
			}
		}

		~LinkedList()
		{
			clear();
		}
		/// <summary>
		/// operator overload to get node
		/// </summary>
		/// <param name="pos"></param>
		/// <returns></returns>
		T& operator[](unsigned int pos)
		{
			Node* node = traverse(pos);
			if (node != nullptr)
			{
				return node->mData;
			}
		}
		/// <summary>
		/// adds node to end of list
		/// </summary>
		/// <param name="new_val"></param>
		void append(const T& new_val)
		{
			// Make a new (disconnected) node
			Node* nnode = new Node;
			nnode->mNext = nnode->mPrev = nullptr;
			nnode->mData = new_val;

			if (mSize == 0)
			{
				// case1: empty list
				mStart = nnode;
				mEnd = nnode;
			}
			else
			{
				// case2: non-empty list
				nnode->mPrev = mEnd;  // b.
				mEnd->mNext = nnode;  // c.
				mEnd = nnode;		  // a.
			}
			mSize++;
		}
		/// <summary>
		/// adds node to beginning of list
		/// </summary>
		/// <param name="new_val"></param>
		void prepend(const T& new_val)
		{
			// Make a new (disconnected) node
			Node* nnode = new Node;
			nnode->mNext = nnode->mPrev = nullptr;
			nnode->mData = new_val;

			if (mSize == 0)
			{
				// case1: empty list
				mStart = nnode;
				mEnd = nnode;
			}
			else
			{
				// case2: non-empty list
				nnode->mNext = mStart;  // b.
				mStart->mPrev = nnode;  // c.
				mStart = nnode;		  // a.
			}
			mSize++;
		}

		/// <summary>
		/// insert method to insert node
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="val"></param>
		void insert(unsigned int pos, const T& val)
		{
			// if pos == mSize, call append
			if (pos == mSize)
			{
				append(val);
			}
			// if pos == 0, call prepend
			else if (pos == 0)
			{
				prepend(val);
			}
			// if pos > 0 and pos < mSize, should go in the middle...
			else if (pos < mSize && pos > 0)
			{
				Node* nodeBefore = traverse(pos - 1);

				// ... Make a new node (like append)
				Node* nnode = new Node;
				nnode->mData = val;
				nnode->mPrev = nnode->mNext = nullptr;

				nnode->mPrev = nodeBefore;		//a.
				nnode->mNext = nodeBefore->mNext;  // d.
				nodeBefore->mNext->mPrev = nnode;	// c.
				nodeBefore->mNext = nnode;		// b.

				mSize++;
			}
		}
		/// <summary>
		/// gets size of list
		/// </summary>
		/// <returns></returns>
		unsigned int size() const
		{
			return mSize;
		}
		/// <summary>
		/// clears list
		/// </summary>
		void clear()
		{
			while (mStart != nullptr)
			{
				Node* temp = mStart;
				mStart = mStart->mNext;
				delete temp;
			}
			mEnd = nullptr;
			mSize = 0;
		}
		/// <summary>
		/// operator overload for << 
		/// </summary>
		/// <param name="os"></param>
		/// <param name="alist"></param>
		/// <returns></returns>
		friend std::ostream& operator <<(std::ostream& os, const LinkedList<T>& alist)
		{
			os << "[";
			Node* cur = alist.mStart;
			for (unsigned int i = 0; i < alist.size(); i++)
			{
				os << alist[i];
				if (i < alist.size() - 1)
					os << ", ";
			}
			os << "]";
			return os;
		}
		/// <summary>
		/// operator overload for =
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		LinkedList& operator=(const LinkedList& other)
		{
			if (this != &other) {
				clear();

				for (unsigned int i = 0; i < other.size(); ++i) {
					append(other[i]);
				}
			}
			return *this;
		}

	};
}