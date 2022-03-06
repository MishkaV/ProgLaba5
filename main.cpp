#include <iostream>
#include <functional>
#include <string>
#include <map>

using namespace std;
const int start = 3, fin = 28;
const int restriction1 = 14, restriction2 = 20;

int main() {
    int breanchCount = 0;

    // Task #1
    function<int(int, string)> calc1 = [&calc1, &breanchCount](int x, string way) {
        breanchCount++;
        if (x < fin)
            return calc1(x + 1, way + " +1") + calc1(x * 3, way + " *3");
        else if (x == fin) {
            cout << "Way" << way << endl;
            return 1;
        }
        return 0;
    };
    cout << "Forward\n";
    cout << "Count:\n" << calc1(start, "") << endl;
    cout << "breanchCount: " << breanchCount << endl;


    // Task #2
    breanchCount = 0;
    function<int(int, int, string)> calc2 = [&calc2, &breanchCount](int x, int flag, string way) {
        breanchCount++;
        if (x < fin) {
            if (x == restriction1 || x == restriction2)
                flag = 1;
            return calc2(x + 1, flag, way + " +1") + calc2(x * 3, flag, way + " *3");
        } else if (x == fin && flag) {
            cout << "Way" << way << endl;
            return 1;
        }
        return 0;
    };
    cout << "\nWith restrictions\n";
    cout << "Count:\n" << calc2(start, 0, "") << endl;
    cout << "breanchCount: " << breanchCount << endl;

    // Task #3
    breanchCount = 0;
    function<int(int, string)> calc3 = [&calc3, &breanchCount](int x, string way) {
        breanchCount++;
        if (x > start) {
            int count = calc3(x - 1, way + " -1");
            if (x % 3 == 0)
                count += calc3(x / 3, way + "/ 3");
            return count;
        } else if (x == start) {
            cout << "Way" << way << endl;
            return 1;
        }
        return 0;
    };
    cout << "\nBack\n";
    cout << "Count:\n" << calc3(fin, "") << endl;
    cout << "breanchCount: " << breanchCount << endl;

    // Task #4
    breanchCount = 0;
    map<int, int> Space;

    function<int(int)> calc4 = [&Space, &calc4, &breanchCount](int x) {
        breanchCount++;
        if (Space.count(x)) return Space[x];
        if (x == fin) {
            Space[x] = 1;
            return 1;
        }
        if (x < fin) {
            Space[x] = calc4(x + 1) + calc4(x * 2);
            return Space[x];
        }
        return 0;
    };

    cout << "\nOR\n";
    cout << "Count:\n" << calc4(start) << endl;
    cout << "breanchCount: " << breanchCount << endl;

    for (auto i: Space)
        cout << i.first << " " << i.second << endl;

    return (0);
}