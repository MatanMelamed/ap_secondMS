
#include <iostream>
#include <unordered_set>
#include "StatePriQue.h"
#include "Cell.h"

void F() {
    StatePriQue<Cell> que;

    State<Cell> c1 = State<Cell>({1, 1}, 3);
    State<Cell> c2 = State<Cell>({2, 2}, 2);
    State<Cell> c3 = State<Cell>({3, 3}, 1);
    State<Cell> c4 = State<Cell>({4, 4}, 1);

    que.Push(&c1);
    que.Push(&c3);
    que.Push(&c2);
    que.Push(&c4);
    que.print();

    std::cout << std::endl;

    State<Cell> x = State<Cell>({3, 3}, 10);
    que.Update(&x);

    que.print();
}

void G() {
    StatePriQue<Cell> que;

    State<Cell> c1 = State<Cell>({1, 1}, 3);
    State<Cell> c2 = State<Cell>({2, 2}, 2);
    State<Cell> c3 = State<Cell>({3, 3}, 1);
    State<Cell> c4 = State<Cell>({4, 4}, 1);

    que.Push(&c1);
    que.Push(&c3);
    que.Push(&c2);
    que.Push(&c4);
    que.print();

    State<Cell> *s = que.PopMin();
    std::cout << *s << std::endl;

    s = que.PopMin();
    std::cout << *s << std::endl;


    que.print();
}

int main() {

    std::unordered_set<State<Cell> *> set;

    for (int i = 0; i < 1; ++i) {
        State<Cell> state2({1, 1}, 1);
        std::cout << &state2 << std::endl;
        set.insert(&state2);
    }
    std::cout << set.size() << std::endl;
    State<Cell> state2({1, 1}, 1);
    std::unordered_set<State<Cell> *>::iterator it;
    it = set.find(&state2);
    if (it != set.end()) {
        std::cout << &(*it) << std::endl << (*it);

    };

    return 0;
}
