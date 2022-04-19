#include <iostream>
#include <string>
#include "stack.h"
using namespace std;


bool check_correct_brackets(string expression) {
    Stack<char> stack;

    for (char i : expression) {
        if (i == '(') { stack.push('('); }
        else if (i == ')') {
            if (!stack.is_empty()) { stack.pop(); }
            else { return false; }
        }
    }
    if (stack.is_empty()) { return true; }
    else { return false; }
}


float give_rezult(string expression) {
    float outcome = 0;
    Stack<float> stack;

    for (char i : expression) {
        outcome = 0;

        if (isdigit(i)) { stack.push(i - '0'); }
        else if (i == '+') {
            float a = stack.peek();
            stack.pop();

            float b = stack.peek();
            stack.pop();

            outcome = a + b;
            stack.push(outcome);
        }
        else if (i == '-') {
            float a = stack.peek();
            stack.pop();

            float b = stack.peek();
            stack.pop();

            outcome = b - a;
            stack.push(outcome);
        }
        else if (i == '*') {
            float a = stack.peek();
            stack.pop();

            float b = stack.peek();
            stack.pop();

            outcome = a * b;
            stack.push(outcome);
        }
        else if (i == '/') {
            float a = stack.peek();
            stack.pop();

            float b = stack.peek();
            stack.pop();

            outcome = b / a;
            stack.push(outcome);
        }
    }
    return stack.peek();
}


int main() {
    // setlocale(LC_ALL, "Russian");
    string new_expression;
    string polish_string;

    cout << "Write expression for check correct brackets: ";
    getline(cin, new_expression);
    cout << "Result: expression is " << ((check_correct_brackets(new_expression)) ? "correct" : "not correct") << endl << endl;

    cout << "Write Polish expression: ";
    getline(cin, polish_string);
    cout << "Result of Polish expression: " << give_rezult(polish_string) << endl;

    return 0;
}
