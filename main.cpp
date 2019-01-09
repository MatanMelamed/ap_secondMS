
#include <iostream>

template <class T>
T Get(T t){
    std::cout << t;
    return t;
}

int main() {
    int x=5;

    Get<int>(x);

    return 0;
}
