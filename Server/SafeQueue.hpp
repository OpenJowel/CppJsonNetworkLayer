#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include <string>
#include <queue>
#include <mutex>

#include "QueryResponseStructs.hpp"

class SafeQueue
{
public:

	SafeQueue();
	~SafeQueue();

    // negative quantity = get all
    std::queue<Query> elements(int quantity = -1);

    void push(Query);


private:
    void _clear(); // Private because not thread-safe !

    std::queue<Query> m_elements;
    mutable std::mutex m_mutex;

};

#endif	// SAFEQUEUE_H

