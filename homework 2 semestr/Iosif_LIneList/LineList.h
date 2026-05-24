#pragma once
#include <iostream>
using namespace std;

class ListException {};

template <class T>
class ListNode
{
    T         value;
    ListNode* next;

    ListNode(const T& val, ListNode* nxt) : value(val), next(nxt) {}

    template <class U> friend class LineList;

public:
    const T&  getValue() const { return value; }
    ListNode* getNext()        { return next;  }
};

template <class T>
class LineList
{
    ListNode<T>* head;
    int          count;

    LineList(const LineList&);

public:
    LineList() : head(nullptr), count(0) {}

    ~LineList()
    {
        while (head)
        {
            ListNode<T>* tmp = head->next;
            delete head;
            head = tmp;
        }
    }

    ListNode<T>* getStart() const { return head;  }
    int          size()     const { return count; }

    void insertFirst(const T& val)
    {
        head = new ListNode<T>(val, head);
        ++count;
    }

    void insertAfter(ListNode<T>* pos, const T& val)
    {
        if (!pos) throw ListException();
        pos->next = new ListNode<T>(val, pos->next);
        ++count;
    }

    void deleteFirst()
    {
        if (!head) throw ListException();
        ListNode<T>* tmp = head->next;
        delete head;
        head = tmp;
        --count;
    }

    void deleteAfter(ListNode<T>* pos)
    {
        if (!pos || !pos->next) throw ListException();
        ListNode<T>* tmp = pos->next;
        pos->next        = tmp->next;
        delete tmp;
        --count;
    }

    template <class U>
    friend ostream& operator<<(ostream& out, const LineList<U>& lst);
};

template <class T>
ostream& operator<<(ostream& out, const LineList<T>& lst)
{
    ListNode<T>* cur = lst.head;
    if (!cur) { out << "EMPTY"; return out; }
    while (cur) { out << cur->value << ' '; cur = cur->next; }
    return out;
}
