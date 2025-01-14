#include <iostream>
#include <string>
#include <locale.h>
#include "EmployeeManagementSystem.h"
#include "user.h"
#include "admin.h"
#include <Windows.h>

// ��������� ��� �������� ������� ������ (�����/������)
struct UserCredentials {
    std::string login;
    std::string password;
    bool role;
};

// ������ ������ ��� ������� � �������
UserCredentials adminCredentials = { "admin", "admin123", true };  // �������������
UserCredentials userCredentials = { "user", "user123", false };   // ������������

int main() {
    system("cls");
    // ������������� ������ ��� ��������� ������� ��������
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    EmployeeManagementSystem manager;
    Admin admin(manager);
    User user(manager);

    manager.setFileName("employees.t�t");
    manager.readEmployeesFromFile();

    std::string enteredLogin, enteredPassword;
    bool authenticated = false;
    bool role = false;

    // ����������� ����� � ������
    std::cout << "������� �����: ";
    std::getline(std::cin, enteredLogin);
    std::cout << "������� ������: ";
    std::getline(std::cin, enteredPassword);

    // �������� ������ � ������
    if (enteredLogin == adminCredentials.login && enteredPassword == adminCredentials.password) {
        authenticated = true;
        role = true;
        std::cout << "�� ����� ��� �������������.\n";
    }
    else if (enteredLogin == userCredentials.login && enteredPassword == userCredentials.password) {
        authenticated = true;
        role = false;
        std::cout << "�� ����� ��� ������������.\n";
    }
    else {
        std::cout << "�������� ����� ��� ������. ���������� �����.\n";
    }

    // ���� �������������� ������ �������, ���������� ����
    if (authenticated) {
        if (role) {
            // ����� ����
            admin.adminMenu();
        }
        else {
            // ������������ ����
            user.userMenu();
        }
    }
    manager.writeEmployeesToFile();

    return 0;
}
