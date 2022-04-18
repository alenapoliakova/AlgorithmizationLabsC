#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct ZVENO {
    int value;  // Значение элемента
    ZVENO *next;  // Указатель на следующий элемент
};


// New - Создание нового списка
struct ZVENO *New(int value) {
    struct ZVENO *head=(struct ZVENO*)malloc(sizeof(struct ZVENO));
    head->value=value;
    head->next=NULL;
    return head;
}


// AddFirst - Добавление значения в начало списка
struct ZVENO *AddFirst(ZVENO* head, int value) {
    ZVENO* v = New(value);  // Создание пустого элемента
    v->value = value;  // Присвоение значения
    v->next = head;  // Присоединение к списку
    return v;  // Возвращаем указатель на новую "голову" списка
}

// AddLast - Добавление значения в конец списка
struct ZVENO *AddLast(ZVENO* head, int value) {
    ZVENO* v = New(value);  // Создание пустого элемента
    ZVENO* p = head;  // Текущий указатель, указывающий на первый элемент

    while (p->next != NULL)
        p = p->next;

    p->next = v;  // Привязка нового элемента
    v->value=value;  // Занесение значения
    v->next = NULL;  // Последний элемент

    return head;  // Возвращаем указатель на "голову" списка
}


// AddNext - Добавление значения после какого-то значения
struct ZVENO *AddNext(ZVENO* head, int value, int data) {
    ZVENO* p = head;  // Текущий указатель

    while (p->value == value && p->next != NULL)  // Ищем место для вставки элемента
        if (p->next == NULL) {  // Если дошли до последнего элемента => условие для вставки не выполнено
            return head;
        }
        p = p->next;  // Перемещаем текущий указатель

    ZVENO* v = New(data);

    v->value = data;
    v->next = p->next;  // Шаг 1
    p->next = v;  // Шаг 2

    return head;
}

// print - печать односвязного списка
void print(struct ZVENO* head) {
    while (head->next) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("%d ", head->value);
    putchar('\n');
}

// get_size - узнать длину списка
int get_size(ZVENO* head) {
    int length = 1;
    while (head->next) {
        length += 1;
        head = head->next;
    }

    return length;
}

// remove - удаление элемента из односвязного линейного списка
struct ZVENO *remove(ZVENO* head, int value) {
    // TODO: добавить обработку для ситуации, когда этот value первый/последний
    ZVENO *p = head;  // Текущий указатель
    ZVENO *v = head->next;

    if (p->value == value) {
        head = p->next;
        delete p;
        return head;
    }

    while (v && v->value != value) {
        v = v->next;
        p = p->next;
    }
    if (!v) {
        cout << "Can't remove value.\n";
        return head;
    }
    p->next = v->next;
    delete v;
    return head;
}


int main() {
    struct ZVENO *head=NULL;  // Объявили указатель на список

    head = AddFirst(head, 6);  // добавление элемента со значением 6 в начало списка
    print(head);

    head = AddLast(head, 7);  // добавление элемента со значением 7 в конец списка
    print(head);

    head = AddFirst(head, 900);
    print(head);

    head = AddLast(head, 700);
    print(head);

    head = AddLast(head, 222);
    print(head);

    head = AddNext(head, 6, 10);
    print(head);

    head = remove(head, 900);
    print(head);

    head = remove(head, 10);
    print(head);

    head = remove(head, 222);
    print(head);

    cout << get_size(head) << endl;

    return 0;
}
