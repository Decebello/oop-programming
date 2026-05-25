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
    const T&  getValue() const;
    ListNode* getNext();
};

template <class T>
const T& ListNode<T>::getValue() const { return value; }

template <class T>
ListNode<T>* ListNode<T>::getNext() { return next; }

template <class T>
class LineList
{
    ListNode<T>* head;
    int          count;
    LineList(const LineList&);
public:
    LineList();
    ~LineList();
    ListNode<T>* getStart() const;
    int          size()     const;
    void insertFirst(const T& val);
    void insertAfter(ListNode<T>* pos, const T& val);
    void deleteFirst();
    void deleteAfter(ListNode<T>* pos);

    template <class U>
    friend ostream& operator<<(ostream& out, const LineList<U>& lst);
};

template <class T>
LineList<T>::LineList() : head(nullptr), count(0) {}

template <class T>
LineList<T>::~LineList()
{
    while (head)
    {
        ListNode<T>* tmp = head->next;
        delete head;
        head = tmp;
    }
}

template <class T>
ListNode<T>* LineList<T>::getStart() const { return head; }

template <class T>
int LineList<T>::size() const { return count; }

template <class T>
void LineList<T>::insertFirst(const T& val)
{
    head = new ListNode<T>(val, head);
    ++count;
}

template <class T>
void LineList<T>::insertAfter(ListNode<T>* pos, const T& val)
{
    if (!pos) throw ListException();
    pos->next = new ListNode<T>(val, pos->next);
    ++count;
}

template <class T>
void LineList<T>::deleteFirst()
{
    if (!head) throw ListException();
    ListNode<T>* tmp = head->next;
    delete head;
    head = tmp;
    --count;
}

template <class T>
void LineList<T>::deleteAfter(ListNode<T>* pos)
{
    if (!pos || !pos->next) throw ListException();
    ListNode<T>* tmp = pos->next;
    pos->next        = tmp->next;
    delete tmp;
    --count;
}

template <class T>
ostream& operator<<(ostream& out, const LineList<T>& lst)
{
    ListNode<T>* cur = lst.head;
    if (!cur) { out << "EMPTY"; return out; }
    while (cur) { out << cur->value << ' '; cur = cur->next; }
    return out;
}
