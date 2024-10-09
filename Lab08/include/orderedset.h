#pragma once
#include <array_list.h>
#include <sstream>
#include <queue.h>


namespace ssuds
{
	enum TraversalType { PREORDER, INORDER, POSTORDER };

	template <class T>
	class OrderedSet
	{
	protected:
		class Node
		{
		public:
			T mData;
			Node* mLeft;
			Node* mRight;

			Node(const T& val) : mData(val), mLeft(nullptr),
				mRight(nullptr)
			{
				// empty.
			}

			bool insert_recursive(const T& val)
			{
				if (mData == val)
				{
					// I am holding this value.  No need to go further -- they
					// gave us a duplicate.  Just return false to indicate we didn't
					// add anything
					return false;
				}
				else if (val < mData)
				{
					// This value should go to my left.
					if (mLeft == nullptr)
					{
						// I don't have a left child.  Make one that holds this new
						// value
						mLeft = new Node(val);
						return true;
					}
					else
					{
						// Let the left child handle the rest of the process
						return mLeft->insert_recursive(val);
					}
				}
				else
				{
					// This value is greater than us.  It should go to my right.
					if (mRight == nullptr)
					{
						// We don't have a right child -- make ont
						mRight = new Node(val);
						return true;
					}
					else
					{
						// We do have a right child -- let it finish the process
						return mRight->insert_recursive(val);
					}
				}
			}

			void traverse_preorder(ArrayList<T>& result)
			{
				result.append(mData);

				if (mLeft != nullptr)
					mLeft->traverse_preorder(result);

				if (mRight != nullptr)
					mRight->traverse_preorder(result);
			}

			void traverse_inorder(ArrayList<T>& result)
			{
				if (mLeft != nullptr)
					mLeft->traverse_inorder(result);

				result.append(mData);

				if (mRight != nullptr)
					mRight->traverse_inorder(result);
			}

			void traverse_postorder(ArrayList<T>& result)
			{
				if (mLeft != nullptr)
					mLeft->traverse_postorder(result);

				if (mRight != nullptr)
					mRight->traverse_postorder(result);

				result.append(mData);
			}
		};

		Node* balance(ssuds::ArrayList<T>& sortedList, int start, int end)
		{
			if (start > end)
				return nullptr;

			int mid = start + (end - start) / 2;
			Node* newNode = new Node(sortedList[mid]);

			newNode->mLeft = balance(sortedList, start, mid - 1);
			newNode->mRight = balance(sortedList, mid + 1, end);

			return newNode;
		}

		void clearRecursive(Node* node)
		{
			if (node == nullptr)
				return;

			clearRecursive(node->mLeft);
			clearRecursive(node->mRight);
			delete node;
		}

		bool contains_recursive(Node* node, const T& val) const
		{
			if (node == nullptr)
			{
				return false;
			}
			else if (node->mData == val)
			{
				return true;
			}
			else if (val < node->mData)
			{
				return contains_recursive(node->mLeft, val);
			}
			else
			{
				return contains_recursive(node->mRight, val);
			}
		}

		int calculate_height(Node* node) const
		{
			if (node == nullptr)
			{
				return 0;
			}
			else
			{
				int left_height = calculate_height(node->mLeft);
				int right_height = calculate_height(node->mRight);

				return std::max(left_height, right_height) + 1;
			}
		}

		Node* mRoot;
		unsigned int mSize;

	public:
		OrderedSet() : mRoot(nullptr), mSize(0)
		{
			// empty
		}

		~OrderedSet()
		{
			clear();
		}


		// Note: returns true if this value was added, false if not
		//   (because it was a duplicate)
		bool insert(const T& val)
		{
			if (mSize == 0)
			{
				// This set is empty.  Make the new value the 
				// root node
				mRoot = new Node(val);
				mSize = 1;
				return true;
			}
			else
			{
				// This new node (if not a duplicate) will go somewhere
				// below the current root.
				bool inserted = mRoot->insert_recursive(val);
				if (inserted) {
					mSize++;
				}
				return inserted;
			}
		}

		ssuds::ArrayList<T> traversal(TraversalType type)
		{
			ssuds::ArrayList<T> result;
			if (mRoot != nullptr)
			{
				switch (type)
				{
				case PREORDER:
					mRoot->traverse_preorder(result);
					break;
				case INORDER:
					mRoot->traverse_inorder(result);
					break;
				case POSTORDER:
					mRoot->traverse_postorder(result);
					break;
				}
			}
			return result;
		}

		friend std::ostream& operator<<(std::ostream& os, const OrderedSet& set)
		{
			ssuds::ArrayList<T> result = set.traversal(INORDER);
			for (const auto& val : result)
			{
				os << val << " ";
			}
			return os;
		}

		void rebalance()
		{
			ssuds::ArrayList<T> sortedList = traversal(INORDER);
			clear(); 

			mRoot = balance(sortedList, 0, sortedList.size() - 1);
			mSize = sortedList.size();
		}

		unsigned int size() const
		{
			return mSize;
		}

		void clear()
		{
			clearRecursive(mRoot);
			mRoot = nullptr;
			mSize = 0;
		}

		bool contains(const T& val) const
		{
			return contains_recursive(mRoot, val);
		}

		int get_height() const
		{
			return calculate_height(mRoot);
		}

		bool erase(const T& val)
		{
			Node* parent = nullptr;
			Node* current = mRoot;

			while (current != nullptr && current->mData != val)
			{
				parent = current;

				if (val < current->mData)
				{
					current = current->mLeft;
				}
				else
				{
					current = current->mRight;
				}
			}

			if (current == nullptr)
			{
				return false;
			}

			// Case 1: No child
			if (current->mLeft == nullptr && current->mRight == nullptr)
			{
				if (current != mRoot)
				{
					if (parent->mLeft == current)
					{
						parent->mLeft = nullptr;
					}
					else
					{
						parent->mRight = nullptr;
					}
				}
				else
				{
					mRoot = nullptr;
				}

				delete current;
			}
			// Case 2: One child
			else if (current->mLeft == nullptr || current->mRight == nullptr)
			{
				Node* child = (current->mLeft != nullptr) ? current->mLeft : current->mRight;

				if (current != mRoot)
				{
					if (parent->mLeft == current)
					{
						parent->mLeft = child;
					}
					else
					{
						parent->mRight = child;
					}
				}
				else
				{
					mRoot = child;
				}

				delete current;
			}
			// Case 3: Two children
			else
			{
				Node* successor = current->mRight;
				Node* succParent = nullptr;

				while (successor->mLeft != nullptr)
				{
					succParent = successor;
					successor = successor->mLeft;
				}

				if (succParent != nullptr)
				{
					succParent->mLeft = successor->mRight;
				}
				else
				{
					current->mRight = successor->mRight;
				}

				current->mData = successor->mData;
				delete successor;
			}

			--mSize;
			return true;
		}

		std::string tree_string() const 
		{
			if (mRoot == nullptr) 
			{
				return "Tree is empty.";
			}

			std::stringstream ss;
			ssuds::queue<Node*> q;
			q.enqueue(mRoot);

			while (!q.empty()) {
				int levelSize = q.size();

				for (int i = 0; i < levelSize; ++i) 
				{
					Node* current = q.head();
					ss << "    " << current->mData;
					q.dequeue();

					if (current == nullptr) 
					{
						ss << " - ";
					}
					else {

						if (current->mLeft != nullptr || current->mRight != nullptr) 
						{
							if (current->mLeft != nullptr) 
							{
								ss << " L:" << current->mLeft->mData;
								q.enqueue(current->mLeft);
							}
							else 
							{
								ss << " L:-";
							}
							if (current->mRight != nullptr) 
							{
								ss << " R:" << current->mRight->mData;
								q.enqueue(current->mRight);
							}
							else 
							{
								ss << " R:-";
							}
						}
						else
						{
							ss << " L:-";
							ss << " R:-";
						}
					}
				}
				ss << "\n";
			}

			return ss.str();
		}

	};
}
