#pragma once
#include <linked_list.h>

namespace ssuds
{
    template <class T>
    class stack : public LinkedList<T>
    {
    public:
        void push(const T& val)
        {
            this->prepend(val);
        }

        void pop()
        {
            if (!this->empty())
            {
                this->remove(this->begin());
            }
            else
            {
                throw std::out_of_range("Stack is empty");
            }
        }

        T top()
        {
            if (!this->empty())
            {
                return *(this->begin());
            }
            else
            {
                throw std::out_of_range("Stack is empty");
            }
        }

        bool empty() const
        {
            return this->size() == 0;
        }

        unsigned int size() const
        {
            return LinkedList<T>::size();
        }

        typename LinkedList<T>::LinkedListIterator begin() const
        {
            return LinkedList<T>::begin();
        }

        typename LinkedList<T>::LinkedListIterator end() const
        {
            return LinkedList<T>::end();
        }
    };
}