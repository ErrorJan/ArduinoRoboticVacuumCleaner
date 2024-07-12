#ifndef LinkedList_HPP
#define LinkedList_HPP

#include <Arduino.h>

template <typename T>
struct LinkedListEntry
{
    LinkedListEntry<T>* nextEntry = nullptr;
    LinkedListEntry<T>* previousEntry = nullptr;
    T* objPtr;

    LinkedListEntry( T* objPtr, LinkedListEntry<T>* previousEntry )
    {
        this->objPtr = objPtr;
        this->previousEntry = previousEntry;
    }

    ~LinkedListEntry()
    {
        free( objPtr );

        if ( nextEntry != nullptr )
            delete nextEntry;
    }
};

template <typename T>
class LinkedList
{
    public:
        void push_back( T obj )
        {
            if ( listLength == 0 )
            {
                firstEntry = new LinkedListEntry<T>( copyObj( obj ), nullptr );
                lastEntry = firstEntry;
                listLength++;
            }
            else
            {
                lastEntry->nextEntry = new LinkedListEntry<T>( copyObj( obj ), lastEntry );
                lastEntry = lastEntry->nextEntry;
                listLength++;
            }
        }

        size_t size()
        {
            return listLength;
        }

        T& operator[]( size_t index )
        {
            LinkedListEntry<T>* nextEntry;

            if ( index < listLength * 0.5 )
            {
                nextEntry = firstEntry;

                for ( size_t j = 0; j < index; j++ )
                {
                    nextEntry = nextEntry->nextEntry;
                }
            }
            else
            {
                nextEntry = lastEntry;

                for ( size_t j = listLength - 1; j > index; j-- )
                {
                    nextEntry = nextEntry->previousEntry;
                }
            }

            return *nextEntry->objPtr;
        }

        ~LinkedList()
        {
            if ( firstEntry != nullptr )
                delete firstEntry;
        }

    private:
        size_t listLength = 0;
        LinkedListEntry<T>* firstEntry = nullptr;
        LinkedListEntry<T>* lastEntry = nullptr;

        T* copyObj( const T& ref )
        {
            T* memAddress = ( T* ) malloc( sizeof( T ) );
            memcpy( memAddress, &ref, sizeof( T ) );

            return memAddress;
        }

        // Entry<T>* getLastEntry()
        // {
        //     Entry<T>* currentEntry = firstEntry;
        //     Entry<T>* nextEntry = lastEntry;

        //     if ( lastEntry != nullptr )
        //         nextEntry = lastEntry;
        //     else
        //         nextEntry = firstEntry;

        //     while ( nextEntry != nullptr )
        //     {
        //         currentEntry = nextEntry;
        //         nextEntry = currentEntry->nextEntry;
        //     }

        //     lastEntry = currentEntry;

        //     return currentEntry;
        // }
};

#endif