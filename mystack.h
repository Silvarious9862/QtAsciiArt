#pragma once
#ifndef _MYSTACK
#define _MYSTACK

#include <iostream>
#define EMPTY -1

namespace my
{
    template<typename T>
    class Stack
    {
    private:
        template<typename T1>
        class Node
        {
        public:
            T1 data;
            Node *pNext;

            Node(T1 data = T1(), Node *pNext = nullptr)
            {
                this->data = data;
                this->pNext = pNext;
            }

        };
        Node<T> *head;
        int size;

    public:
        Stack();
        ~Stack();
        int getsize();
        void push(T data);
        void pop();
        T& top();
        void clear();
        bool empty();
    };
}



    template<typename T>
    my::Stack<T>::Stack()
    {
        size = 0;
        head = nullptr;
    }

    template <typename T>
    my::Stack<T>::~Stack()
    {
        clear();
    }

    template <typename T>
    int my::Stack<T>::getsize()
    {
        return size;
    }

    template <typename T>
    void my::Stack<T>::push(T data)
    {
        head = new Node<T>(data, head);
        size++;
    }

    template <typename T>
    void my::Stack<T>::pop()
    {
        try{
            if (size == 0) throw EMPTY;
            Node<T> *tmp = head;
            head = head->pNext;
            delete tmp;
            size--;
        }
        catch(int a)
        {
            std::cout << "Stack is empty!" << std::endl;
        }
    }

    template <typename T>
    T& my::Stack<T>::top()
    {
        try
        {
            if (size == 0) throw EMPTY;
            return head->data;
        }
        catch(int a)
        {
            std::cout << "Stack is empty!" << std::endl;
        }
    }

    template <typename T>
    void my::Stack<T>::clear()
    {
        while(size) pop();
    }

    template<typename T>
    bool my::Stack<T>::empty()
    {
        return getsize() == 0;
    }


#endif
