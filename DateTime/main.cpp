#include <iostream>
#include "datetime.h"
 
using namespace std;
 
int main() {
    setlocale(LC_ALL, "Russian");
    DateTime dt1(2021, 12, 21, 7, 54, 34);
 
    cout << "\nКорректность даты: "
         << (dt1.isValid() ? "корректна" : "НЕКОРРЕКТНА") << "\n";
 
    cout << "\nФорматы вывода:\n";
    cout << "  Формат 1 (d.MM.yyyy)        : "; dt1.printFormat1(); cout << '\n';
    cout << "  Формат 2 (d месяц yyyy)     : "; dt1.printFormat2(); cout << '\n';
    cout << "  Формат 3 (dd.MM.yy)         : "; dt1.printFormat3(); cout << '\n';
    cout << "  ISO      (yyyy-MM-ddThh:mm:ss): "; dt1.printISO();   cout << '\n';
 
    cout << "\nДень недели: "
         << dt1.dayOfWeekName()
         << " (номер: " << dt1.dayOfWeek() + 1 << ")\n";
 
    DateTime dt2(2000, 1, 1, 0, 0, 0);
    cout << "\nОпорная дата: "; dt2.printISO(); cout << '\n';
    cout << "Разница: " << dt1.diffDays(dt2) << " дней\n";
 
    DateTime bad(2023, 2, 30);
    cout << "\nПроверка некорректной даты 2023-02-30: "
         << (bad.isValid() ? "корректна" : "НЕКОРРЕКТНА") << "\n";
 
    cout << "\nДаты Пасхи (2021–2025):\n";
    for (int y = 2021; y <= 2025; ++y) {
        DateTime easter = DateTime::calculateEaster(y);
        cout << "  " << y << " г.: ";
        easter.printFormat2();
        cout << "  [";
        easter.printFormat1();
        cout << "]  " << easter.dayOfWeekName() << '\n';
    }

    cin.get();
    return 0;
}