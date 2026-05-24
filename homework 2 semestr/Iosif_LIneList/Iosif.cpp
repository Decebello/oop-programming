#include <iostream>
#include <ctime>
#include "LineList.h"

using namespace std;

int solve(int n, int k)
{
    LineList<int> list;

    for (int i = n; i >= 1; i--)
        list.insertFirst(i);

    ListNode<int>* prev = list.getStart();
    while (prev->getNext())
        prev = prev->getNext();

    ListNode<int>* cur = list.getStart();

    while (list.size() > 1)
    {
        for (int i = 1; i < k; i++)
        {
            prev = cur;
            cur  = cur->getNext();
            if (!cur) cur = list.getStart();
        }

        ListNode<int>* next = cur->getNext();
        if (!next) next = list.getStart();

        if (cur == list.getStart())
            list.deleteFirst();
        else
            list.deleteAfter(prev);

        cur = next;
    }

    return list.getStart()->getValue();
}

int main()
{
    int n, k;
    cout << "N = "; cin >> n;
    cout << "k = "; cin >> k;

    clock_t t1  = clock();
    int     ans = solve(n, k);
    clock_t t2  = clock();

    cout << "Ответ: " << ans << endl;
    cout << "Время: " << (double)(t2 - t1) / CLOCKS_PER_SEC << " сек" << endl;

    return 0;
}
