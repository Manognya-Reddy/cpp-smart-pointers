#include <iostream>
#include "smartptr.h"
using namespace std;

class Car {
public:
    string name;
    Car() {
        name = "default car";
        cout << "car made" << endl;
    }
    Car(string n) {
        name = n;
        cout << "car made " << name << endl;
    }
    ~Car() {
        cout << "car destroyed " << name << endl;
    }
};

int main() {

    cout << "----- unique ptr test -----" << endl;
    UniquePtr<Car> u1(new Car("uniqueCar1"));
    cout << u1->name << endl;

    UniquePtr<Car> u2 = move(u1);
    if(u1.get() == nullptr){
        cout << "u1 is null now" << endl;
    }
    cout << u2->name << endl;

    u2.reset(new Car("resettedCar"));
    cout << u2->name << endl;


    cout << "----- shared ptr test -----" << endl;
    SharedPtr<Car> a(new Car("sharedCar"));
    cout << "use count a: " << a.use_count() << endl;

    SharedPtr<Car> b = a;
    cout << "use count after copy: " << a.use_count() << endl;
    cout << "b name: " << b->name << endl;

    {
        SharedPtr<Car> c = b;
        cout << "use count inside block: " << c.use_count() << endl;
    }

    cout << "use count after block: " << a.use_count() << endl;


    cout << "----- make_unique / make_shared test -----" << endl;
    auto mu = make_unique<int>(42);
    cout << "mu val: " << *mu << endl;

    auto ms = make_shared<int>(99);
    cout << "ms val: " << *ms << endl;
    cout << "ms count: " << ms.use_count() << endl;

    return 0;
}
