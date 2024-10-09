#pragma once
#include <linked_list.h>

namespace ssuds
{
    template <class T>
    class queue
    {
    private:
        LinkedList<T> linkedList;

    public:
        void enqueue(const T& val)
        {
            linkedList.append(val);
        }

        void dequeue()
        {
            if (!this->empty())
            {
                linkedList.remove(linkedList.begin());
            }
            else
            {
                throw std::out_of_range("Queue is empty");
            }
        }

        T head()
        {
            if (!this->empty())
            {
                return *(this->begin());
            }
            else
            {
                throw std::out_of_range("Queue is empty");
            }
        }

        bool empty() const
        {
            return this->size() == 0;
        }

        unsigned int size() const
        {
            return linkedList.size();
        }

        typename LinkedList<T>::LinkedListIterator begin() const
        {
            return linkedList.begin();
        }

        typename LinkedList<T>::LinkedListIterator end() const
        {
            return linkedList.end();
        }
    };
}