#include<iostream>
#include<mutex>

using namespace std;

class Singleton{

public:
    static Singleton* GetInstance() {
        static std::mutex mt;
        if (nullptr != inst) return inst;
        std::lock_guard<std::mutex> lockg(mt);
        if (nullptr == inst)
            inst = new Singleton();

        return inst;
    }

    void print() {
        cout << "hello" << endl;
    }
private:
    static Singleton* inst;
};

Singleton* Singleton::inst = nullptr;

int main() {
    Singleton::GetInstance()->print();
}
