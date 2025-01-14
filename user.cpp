// user.cpp

#include "user.h"
#include <iostream>

User::User(EmployeeManagementSystem& manager) : empManager(manager) {}

void User::userMenu() {
    int choice;
    do {
        system("cls");
        std::cout << "Меню пользователя:\n";
        std::cout << "1. Просмотр всех сотрудников\n";
        std::cout << "2. Выполнение индивидуального задания\n";
        std::cout << "3. Поиск сотрудников\n";
        std::cout << "4. Сортировка сотрудников\n";
        std::cout << "0. Выйти\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        system("cls");
        switch (choice) {
        case 1:
            empManager.viewEmployees();
            break;
        case 2:
            empManager.viewRetirementEligible();
            break;
        case 3:
            empManager.searchEmployee();
            break;
        case 4:
            empManager.sortMenu();
            break;
        case 0:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
        system("pause");
    } while (choice != 0);
}

