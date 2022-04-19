#include <iostream>
using namespace std;


template <typename T>
class Stack {
private:
    int top = -1;  // Текущая позиция
    T all_stack[20];  // Сам стек
public:
    bool is_empty() {  // Проверка на пустоту стека
        if (top < 0) { return true; }
        else { return false; }
    }
    bool is_full() {  // Проверка на переполненность стека
        if (top >= 19) { return true; }
        else { return false; }
    }
    int size() { return top + 1; }  // Размерность стека

    void push(T a) {  // Добавление элемента в стек
        if (!is_full()) { ++top; all_stack[top]=a; }
        else { cout << "Stack is full!" << endl; }
    }
    void pop() {  // Удаление элемента из стека
        if (!is_empty()) { --top; }
        else { cout << "Stack is empty!" << endl; }
    }
    T peek() {  // Получение текущего элемента из стека
        if (!is_empty()) { return all_stack[top]; }
        else { cout << "Stack is empty!" << endl; }
    }
};
