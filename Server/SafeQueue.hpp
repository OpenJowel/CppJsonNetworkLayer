/*
  This class implements a concurrent-safe implementation of a queue
  in order to be accessed by multiple threads
*/

#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include <string>
#include <queue>
#include <mutex>

#include "QueryResponseStructs.hpp"

class SafeQueue
{
public:
    // Constructor / Destructor
	SafeQueue();
	~SafeQueue();

    // returns a given quantity of client queries
    // -1 to get the whole queue
    std::queue<Query> queries(int quantity = -1);

    // Inserts new query in the queue
    void push(Query);


private:

    // Empties the queue
    void _clear(); // Private because not thread-safe !

    // Attributes
    std::queue<Query> m_queries;
    mutable std::mutex m_mutex;

};

#endif	// SAFEQUEUE_H

