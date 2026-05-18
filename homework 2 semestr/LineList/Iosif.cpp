#include "LineList.h"
#include <iostream>
#include <ctime>
using namespace std;

LineListElem<int>* nextElem(LineListElem<int>* node, LineList<int>& lst) {
    return node->getNext() ? node->getNext() : lst.getStart();
}

int solveJosephus(int N, int k) {
    LineList<int> circle;
    for (int i = N; i >= 1; --i)
        circle.insertFirst(i);

    LineListElem<int>* pos = circle.getStart();

    for (int remaining = N; remaining > 1; --remaining) {
        LineListElem<int>* pre = pos;
        for (int jump = 1; jump < k - 1; ++jump)
            pre = nextElem(pre, circle);

        LineListElem<int>* victim = nextElem(pre, circle);
        LineListElem<int>* after  = nextElem(victim, circle);

        if (victim == circle.getStart()) {
            circle.deleteFirst();
        } else {
            circle.deleteAfter(pre);
        }

        pos = (remaining > 2) ? after : circle.getStart();
    }

    return circle.getStart()->getData();
}

int main() {
    int sizes[] = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };
    int k = 2;

    cout << "N\tOtvet\tVremya (sek)" << endl;
    for (int n : sizes) {
        clock_t t1 = clock();
        int res = solveJosephus(n, k);
        clock_t t2 = clock();
        cout << n << "\t" << res << "\t"
             << static_cast<double>(t2 - t1) / CLOCKS_PER_SEC << endl;
    }
    return 0;
}
