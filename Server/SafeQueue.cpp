#include "SafeQueue.hpp"

using namespace std;

SafeQueue::SafeQueue()
{

}

SafeQueue::~SafeQueue()
{

}

std::queue<Query> SafeQueue::queries(int quantity)
{
    std::queue<Query> queries;

    lock_guard<mutex> lock(m_mutex);
    if(quantity < 0){
        queries = m_queries;
        _clear();
        return queries;
    }

    while(!m_queries.empty() && quantity > 0){
        queries.push(m_queries.front());
        m_queries.pop();
        quantity--;
    }

    return queries;
}

void SafeQueue::_clear()
{
    while(!m_queries.empty()){
        m_queries.pop();
    }
}

void SafeQueue::push(Query query)
{
    // lock_guard will lock mutex while execution is in the current lock scope {}
    lock_guard<mutex> lock(m_mutex);
    m_queries.push(query);
}

