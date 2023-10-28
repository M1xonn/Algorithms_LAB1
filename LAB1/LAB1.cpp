#include "LinkedList.h"
#include "ArrayList.h"
#include "StackChar.h"
#include "StackDouble.h"
#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;


int isVariable(char i) {
    switch (i) {
    case '+': case '-': case '*': case '/': case '^': case 's': case 'c': return 0;
    case ' ': return 1;
    default: return 2;
    }
}

void add(StackDouble* newStack) {
    double firstVar = newStack->pop();
    double secVar = newStack->pop();
    double result = firstVar + secVar;
    cout << firstVar << " + " << secVar << '\n';
    newStack->push(result);
}

void deduct(StackDouble* newStack) {
    double firstVar = newStack->pop();
    double secVar = newStack->pop();
    double result = secVar - firstVar;
    cout << secVar << " - " << firstVar << '\n';
    newStack->push(result);
}

void multiply(StackDouble* newStack) {
    double firstVar = newStack->pop();
    double secVar = newStack->pop();
    double result = firstVar * secVar;
    cout << firstVar << " * " << secVar << '\n';
    newStack->push(result);
}

void divide(StackDouble* newStack) {
    double firstVar = newStack->pop();
    double secVar = newStack->pop();
    double result = secVar / firstVar;
    cout << secVar << " / " << firstVar << '\n';
    newStack->push(result);
}

void degree(StackDouble* newStack) {
    double firstVar = newStack->pop();
    double secVar = newStack->pop();
    double result = pow(secVar, firstVar);
    cout << secVar << " ^ " << firstVar << '\n';
    newStack->push(result);
}

void calcSin(StackDouble* newStack) {
    double firstVar = newStack->pop();
    double result = sin(firstVar);
    cout << " sin( " << firstVar << " )\n";
    newStack->push(result);
}

void calcCos(StackDouble* newStack) {
    double firstVar = newStack->pop();
    double result = cos(firstVar);
    cout << " cos( " << firstVar << " )\n";
    newStack->push(result);
}

int priority(char i) {
    switch (i) {
    case '(': return 1;
    case '+': case '-': return 2;
    case '*': case '/': return 3;
    case '^': return 4;
    case 's': case 'c': return 5;
    default: return 0;
    }
}

bool isStrDigit(string digitBuffer) {
    for (int i = 0; i < digitBuffer.size(); i++) {
        if (!isdigit(digitBuffer[i]))
            return false;
    }
    return true;
}

int calculatePostfix(string postfix) {
    if (postfix.find(")") != -1 || postfix.find("(") != -1) {
        cout << "Неверное выражение, должны отсутсвовать скобки" << '\n';
        return 0;
    }
    StackDouble newStack;
    postfix += " ";
    string buffer = "";
    for (int i = 0; i < postfix.size(); i++) {
        switch (isVariable(postfix[i])) {
        case 1:
            if (buffer.size() != 0) {
                double a;
                istringstream(buffer) >> a;
                newStack.push(a);
                buffer = "";
            }
            break;
        case 2:
            buffer += postfix[i];
            break;
        case 0:
            if (newStack.size < 2) {
                cout << "Выражение некорректно" << '\n';
                return 0;
            }
            switch (postfix[i]) {
            case '+':
                if (!newStack.isEmpty()) {
                    add(&newStack);
                    break;
                }
            case '-':
                if (!newStack.isEmpty()) {
                    deduct(&newStack);
                    break;
                }
            case '*':
                if (!newStack.isEmpty()) {
                    multiply(&newStack);
                    break;
                }
            case '/':
                if (!newStack.isEmpty()) {
                    divide(&newStack);
                    break;
                }
            case '^':
                if (!newStack.isEmpty()) {
                    degree(&newStack);
                    break;
                }
            case 's':
                if (!newStack.isEmpty()) {
                    calcSin(&newStack);
                    break;
                }
            case 'c':
                if (!newStack.isEmpty()) {
                    calcCos(&newStack);
                    break;
                }
            }
            break;
        }
    }
    if (newStack.size > 1) {
        cout << "Неправильная расстановка операторов" << '\n';
        return 0;
    }
    cout << "Значение корректного выражения: " << newStack.top() << '\n';
    return 1;
}

int calculateInfix(string str) {
    StackChar stack;
    string postfix;
    for (int i = 0; i < str.size(); i++) {
        switch (priority(str[i])) {
        case 1:
            postfix += " ";
            stack.push(str[i]);
            break;
        case 0:
            if (str[i] == ')') {
                postfix += " ";
                while (!stack.isEmpty() && stack.top() != '(') {
                    postfix += " ";
                    postfix += stack.pop();
                    postfix += " ";
                }
                if (!stack.isEmpty()) {
                    postfix += " ";
                    stack.pop();
                }
                else {
                    cout << "Неправильное расположение скобок" << '\n';
                    return 0;
                }
            }
            else {
                if ((str[i] != ' ') && (!isdigit(str[i])) && (str[i] != 's' or str[i] != 'c') && str[i] != '.') {
                    cout << "Встречена переменная: " << str[i] << " иницилизируйте её" << '\n';
                    cout << "Значение переменной: ";
                    string StrForInit = " ";
                    while (!isStrDigit(StrForInit)) {
                        getline(cin, StrForInit);
                        if (!isStrDigit(StrForInit))
                            cout << "Вы ввели не число";
                    }
                    postfix += StrForInit;
                }
                else {
                    postfix += str[i];
                }
            }
            break;
        default:
            if (!stack.isEmpty()) {
                postfix += " ";
                while (!stack.isEmpty() && priority(stack.top()) >= priority(str[i])) {
                    postfix += stack.pop();
                    postfix += " ";
                }
                stack.push(str[i]);
            }
            else {
                postfix += " ";
                stack.push(str[i]);
            }
            break;
        }
    }
    if (!stack.isEmpty()) {
        postfix += " ";
        while (!stack.isEmpty()) {
            postfix += stack.pop();
            postfix += " ";
        }
    }
    while (postfix.find("  ") != -1) {
        postfix.replace(postfix.find("  "), 2, " ");
    }
    cout << "Преобразованное выражение в обратную польскую нотацию: " << postfix << '\n';
    calculatePostfix(postfix);
}


void printMenu() {
    system("cls");
    cout << "1. Двусвязный список\n";
    cout << "2. Динамический массив\n";
    cout << "3. Сортировачная станция\n";
    cout << "4. Выход\n";
}

void printLinkedList() {
    system("cls");
    cout << "1. Вставить новый элемент списка" << '\n';
    cout << "2. Удалить элемент списка" << '\n';
    cout << "3. Получить значение элемента списка" << '\n';
    cout << "4. Отсортировать список" << '\n';
    cout << "5. Вернуться назад" << '\n';
}

void printArrayList() {
    system("cls");
    cout << "1. Добавить элемент массива" << '\n';
    cout << "2. Удалить элемент массива" << '\n';
    cout << "3. Получить значение элемента массива" << '\n';
    cout << "4. Отсортировать массив" << '\n';
    cout << "5. Вернуться назад" << '\n';
}

void printSort() {
    system("cls");
    cout << "1. Преобразовать инфиксную запись и найти значение выражения" << '\n';
    cout << "2. Вернуться назад" << '\n';
}

void menu() {
    int var;
    LinkedList linkedList;
    ArrayList arraylist;
    int variant;
    int n;
    do {
        printMenu();
        cin >> var;
        switch (var) {
        case 1:
            cout << "Введите размер списка для автоматического заполнения: ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                int data = rand() % 100;
                linkedList.push_back(data);
            }

            do {
                variant = 0;
                printLinkedList();
                cin >> variant;
                switch (variant) {
                case 1:
                    int index;
                    int data;
                    linkedList.display();
                    cout << '\n' << "Введите значение, которое хотите добавить в список: ";
                    cin >> data;
                    cout << '\n' << "Введите индекс куда вставить значение: ";
                    cin >> index;
                    linkedList.insert(data, index);
                    linkedList.display();
                    break;
                case 2:
                    linkedList.display();
                    cout << '\n' << "Введите индекс элемента, который удалить из списка: ";
                    cin >> index;
                    linkedList.remove(index);
                    linkedList.display();
                    break;
                case 3:
                    cout << '\n' << "Введите индекс значение которого хотите получить: ";
                    cin >> index;
                    if (linkedList.get(index) != NULL)
                        cout << linkedList.get(index)->data << '\n';
                    break;
                case 4:
                    linkedList.display();
                    cout << '\n';
                    linkedList.timSort();
                    linkedList.display();
                    break;
                }
                if (variant != 5)
                    system("pause");
            } while (variant != 5);
            while (linkedList.size != 0)
                linkedList.remove(0);
            break;

        case 2:

            cout << "Введите размер массива для автоматического заполнения: ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                int data = rand() % 100;
                arraylist.add(data);
            }
            variant = 0;
            do {
                printArrayList();
                cin >> variant;
                switch (variant) {
                case 1:
                    int data;
                    arraylist.print();
                    cout << '\n' << "Введите значение, которое хотите добавить в список: ";
                    cin >> data;
                    arraylist.add(data);
                    arraylist.print();
                    break;
                case 2:
                    arraylist.print();
                    int index;
                    cout << '\n' << "Введите индекс элемента, который удалить из списка: ";
                    cin >> index;
                    arraylist.remove(index);
                    arraylist.print();
                    break;
                case 3:
                    cout << '\n' << "Введите индекс значение которого хотите получить: ";
                    cin >> index;
                    cout << arraylist.get(index) << '\n';
                    break;
                case 4:
                    arraylist.print();
                    cout << '\n';
                    arraylist.timSort();
                    arraylist.print();
                }

                if (variant != 5)
                    system("pause");
            } while (variant != 5);
            while (arraylist.size != 0)
                arraylist.remove(0);
            break;

        case 3:
            do {
                printSort();
                cin >> variant;
                string Str;
                switch (variant) {
                case 1:
                    cout << "Допустимые символы: + - * / ^ sin(s) cos(c) 0-9 .\n";
                    cin.ignore();
                    cout << "Введите выражение" << '\n';
                    getline(cin, Str);
                    calculateInfix(Str);
                    break;
                }
                if (variant != 2)
                    system("pause");
            } while (variant != 2);
            break;
        }
        if (var != 4)
            system("pause");
    } while (var != 4);
}

int main() {
    setlocale(0, "RUS");
    menu();
}