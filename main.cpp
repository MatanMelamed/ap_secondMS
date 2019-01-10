
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

    std::unordered_set<State<Cell>> set;
    State<Cell> state1({1, 1}, 1);
    State<Cell> state2({2, 2}, 2);
    State<Cell> state3({3, 3}, 3);
    State<Cell> state4({4, 4}, 4);
    State<Cell> state5({5, 5}, 5);

    set.insert(state1);
    set.insert(state2);
    set.insert(state3);
    set.insert(state4);
    set.insert(state5);

    std::unordered_set<State<Cell>>::iterator it;
    it = set.find(state2);
    if (it != set.end()) {
        std::cout << (*it) << std::endl;
    };

    std::cout << set.size();


    return 0;
}
