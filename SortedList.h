#ifndef SORTEDLIST_H
#define SPRTEDLIST_H

#include <iostream>

namespace mtm
{

    template<class T>
    class SortedList
    {

        private: 
        template<class T> 
        class Node
        {
            private:  
            T data;     //////////////////////////?? T*? אין בנאי חסר פרמטרים
            Node<T> *next;
            
            // public:
            // Node();
            // ~Node()

            // Node(const Node& node);  //may be the same one , copy before free!
            // {
            //     //?new element new node ? how to copy data
            // }
            // Node& operator=(const Node& node);
        };

        Node<T>* head;
        Node<T>* tail;
        public:
        SortedList()
        {
            head=nullptr;
            tail=nullptr; 
        }
        ~SortedList();  //defaule ? destructor of node ?
        SortedList(const SortedList& list);       ////////?
        SortedList& operator=(const SortedList& list); ///////////?
        void insert(T element)
        {
            if(head==nullptr) //list is empty
            {
                head= new Node<T>;
                head->next=nullptr;
                head->data=T ; ///? what ?/////////////////////////////////////////////////////////////////////////////////////////
                tail=head;
            }
        }



        void remove(const_iterator iterator);
        int length()const;
        
        template<class predicate>
        SortedList filter(predicate condition) const;  //predicate ? ? 

        template<class apply>
        SortedList apply(apply change)const;
        const_iterator begin()const;
        const_iterator end()const;

        class const_iterator
        {
            private:
            int index;

            public:
            const_iterator();
            ~const_iterator();
            const_iterator(const const_iterator& iterator) = default;  //const ? 
            const_iterator& operator=(const const_iterator& iterator) const;  //const ?
            const_iterator& operator++();    //++ iterator
            const_iterator operator++(int);  //iterator++
            bool operator==(const const_iterator& iterator) const; //const ? 
            T operator*(const_iterator& iterator)const;  //const ? 
            friend class SortedList;  ///????????????? is it friend ?

            
        } ///to implement



    };

};



#endif