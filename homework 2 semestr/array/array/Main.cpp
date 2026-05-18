#include <iostream>
using namespace std;

int main() {
    try {
        Array arr(5);

        for (int i = 0; i < 5; i++) {
            arr.insert(i * 10);
        }

        cout << "Initial array:" << endl;
        cout << arr << endl;

        arr.insert(99, 2);
        cout << "After insert 99 at index 2:" << endl;
        cout << arr << endl;

        arr.remove(4);
        cout << "After removing index 4:" << endl;
        cout << arr << endl;

        cout << "Element at index 0: " << arr[0] << endl;

    }
    catch (const ArrayException&) {
        cout << "Error: Array index out of range!" << endl;
    }

    return 0;
}
