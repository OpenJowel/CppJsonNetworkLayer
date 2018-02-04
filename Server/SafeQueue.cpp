#include "SafeQueue.hpp"

using namespace std;

SafeQueue::SafeQueue()
{

}

SafeQueue::~SafeQueue()
{

}

std::queue<Query> SafeQueue::elements(int quantity)
{
    std::queue<Query> elements;

    lock_guard<mutex> lock(m_mutex);
    if(quantity < 0){
        elements = m_elements;
        _clear();
        return elements;
    }

    while(!m_elements.empty() && quantity > 0){
        elements.push(m_elements.front());
        m_elements.pop();
        quantity--;
    }

    return elements;
}

void SafeQueue::_clear()
{
    while(!m_elements.empty()){
        m_elements.pop();
    }
}

void SafeQueue::push(Query query)
{
    // lock_guard will lock mutex while execution is in the current lock scope {}
    lock_guard<mutex> lock(m_mutex);
    m_elements.push(query);
}

