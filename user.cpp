// user.cpp

#include "user.h"
#include <iostream>

User::User(EmployeeManagementSystem& manager) : empManager(manager) {}

void User::userMenu() {
    int choice;
    do {
        system("cls");
        std::cout << "���� ������������:\n";
        std::cout << "1. �������� ���� �����������\n";
        std::cout << "2. ���������� ��������������� �������\n";
        std::cout << "3. ����� �����������\n";
        std::cout << "4. ���������� �����������\n";
        std::cout << "0. �����\n";
        std::cout << "�������� ��������: ";
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
            std::cout << "����� �� ���������.\n";
            break;
        default:
            std::cout << "�������� �����. ���������� �����.\n";
            break;
        }
        system("pause");
    } while (choice != 0);
}

