#pragma once
#include <iostream>

struct ListError {};

template <typename T>
class LineList;

template <typename T>
class LineListElem {
    T               val;
    LineListElem<T>* link;

    LineListElem(const T& v, LineListElem<T>* n) : val(v), link(n) {}

    friend class LineList<T>;
public:
    const T&         getData() const { return val;  }
    LineListElem<T>* getNext() const { return link; }
};

template <typename T>
class LineList {
    LineListElem<T>* head;

    LineList(const LineList&);            
    LineList& operator=(const LineList&); 
public:
    LineList()  : head(nullptr) {}
    ~LineList() { while (head) deleteFirst(); }

    LineListElem<T>* getStart() const { return head; }

    void insertFirst(const T& v) {
        head = new LineListElem<T>(v, head);
    }

    void insertAfter(LineListElem<T>* pos, const T& v) {
        if (!pos) throw ListError{};
        pos->link = new LineListElem<T>(v, pos->link);
    }

    void deleteFirst() {
        if (!head) throw ListError{};
        LineListElem<T>* tmp = head;
        head = head->link;
        delete tmp;
    }

    void deleteAfter(LineListElem<T>* pos) {
        if (!pos || !pos->link) throw ListError{};
        LineListElem<T>* tmp = pos->link;
        pos->link = tmp->link;
        delete tmp;
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const LineList<U>& lst);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const LineList<T>& lst) {
    LineListElem<T>* cur = lst.head;
    if (!cur) { out << "EMPTY"; return out; }
    while (cur) { out << cur->val << ' '; cur = cur->link; }
    return out;
};