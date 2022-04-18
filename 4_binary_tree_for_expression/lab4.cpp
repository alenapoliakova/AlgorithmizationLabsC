// Полякова Алёна. Бинарное дерево для выражения.
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>


struct Node {
    float num;
    char sign;
    Node *left;
    Node *right;
};


// New - Создание узла
Node* New(int num, char sign) {
    Node* V;
    V = (Node*)malloc(sizeof(Node));
    V->num = num;
    V->sign = sign;
    V->left = V->right = nullptr;
    return V;  // Возвращаем указатель
}


// Prior - Приоритет операций
int Prior(char symbol) {
    if (symbol == '+' || symbol == '-') {
        return 2;
    }
    else if (symbol == '*' || symbol == '/') {
        return 5;
    }
    else if (symbol >= '0' && symbol <= '9') {
        return 10;
    }
    else {
        return 100;  // Чтобы не возникало ошибки
    }
}


// MakeTree - Создать дерево
Node* MakeTree (int first, int last, char* mass) {  // Без скобок
    Node* Tree = New(0, '0');  // Создать новую вершину
    int MinPrior = 10, i, k, prt;
    if (first == last) {  // Конечная вершина: число
        Tree->num = mass[first] - '0';  // Чтобы перевести строку (номер символа) в число
        Tree->left = NULL;
        Tree->right = NULL;
        return Tree;  // Выход из рекурсии
    }

    // Ищем последнюю операцию с наименьшим приоритетом
    for (i = first; i < last; i++) {
        prt = Prior(mass[i]);
        // printf("%i %i %c\n", prt, i, mass[i]);
        if (prt <= MinPrior) {
            MinPrior = prt;
            k = i;
            // printf("k=%i\n", k);
        }
    }
    Tree->sign = mass[k];  // Внутренняя вершина (операция)
    Tree->left = MakeTree(first, k - 1, mass);  // Рекурсивно строим поддеревья
    Tree->right = MakeTree(k + 1, last, mass); 
    return Tree;
}

// CalcTree - функция для подсчёта выражения
float CalcTree (Node* Tree) {
    if (Tree->left ==NULL)  // Если нет потомков, вернули число
        return Tree->num;
    float num1 = CalcTree(Tree->left);  // Вычисление поддеревьев
    float num2 = CalcTree(Tree->right);
    // printf("num1=%f num2=%f\n", num1, num2);
    
    switch (Tree->sign) {  // Выполнение операции
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            return num1 / num2;
    }
    return 32767;
}

// Pre_order - Прямой обход дерева в глубину (корень-лево-право)
void Pre_order(Node *tree) {
    if (tree!=nullptr) {  // Лист - окончание рекурсии (идём, пока не встретится пустой узел)
        // Вывод информации о вершине
        if (tree->num != 0) {  // Вывод числа
            printf("%f ", tree->num);
        }
        else if (tree->num == 0 && tree->sign != '0') {  // Вывод знака
            printf("%c ", tree->sign);
        }

        Pre_order(tree->left);  // Рекурсивный обход левого поддерева
        Pre_order(tree->right);  // Рекурсивный обход правого поддерева
    }
}

// In_order - Поперечный обход дерева в глубину (лево-корень-право)
void In_order(Node *tree) {
    if (tree!=nullptr) {  // Лист - окончание рекурсии (идём, пока не встретится пустой узел)
        In_order(tree->left);  // Рекурсивный обход левого поддерева
        
        // Вывод информации о вершине
        if (tree->num != 0) {  // Вывод числа
            printf("%f ", tree->num);
        }
        else if (tree->num == 0 && tree->sign != '0') {  // Вывод знака
            printf("%c ", tree->sign);
        }

        In_order(tree->right);  // Рекурсивный обход правого поддерева
    }
}

// Post_order - Обратный обход дерева в глубину (лево-право-корень)
void Post_order(Node *tree) {
    if (tree!=nullptr) {  // Лист - окончание рекурсии (идём, пока не встретится пустой узел)
        Post_order(tree->left);  // Рекурсивный обход левого поддерева
        Post_order(tree->right);  // Рекурсивный обход правого поддерева
        
        // Вывод информации о вершине
        if (tree->num != 0) {  // Вывод числа
            printf("%f ", tree->num);
        }
        else if (tree->num == 0 && tree->sign != '0') {  // Вывод знака
            printf("%c ", tree->sign);
        }
    }
}


int main() {
    char expression[8];  // Строка, в которую мы считаем данные из файла
    FILE *file_ptr;  // Указатель на файл, который будем считывать
    Node* V= nullptr;

    file_ptr = fopen("text_for_lab4.txt", "r");

    if (file_ptr != NULL) {  // Если удалось открыть файл
        printf("File was successfully opened\n");

        fgets(expression, 8, file_ptr);  // Считывание строки
        printf("Expression from file: %s\n", expression);

        fclose(file_ptr);
    }
    else {
        printf("File was not opened\n");
        return 1;
    }

    // char expression[8] = "1+2*3+4";
    Node *Root = nullptr;
    Root = MakeTree(0, 6, expression);

    // printf("\nExpression: %s\n", expression);

    float result = CalcTree(Root);
    printf("Result: %f\n", result);

    printf("\nPre_order: ");
    Pre_order(Root);

    printf("\nIn_order: ");
    In_order(Root);

    printf("\nPost_order: ");
    Post_order(Root);
}
