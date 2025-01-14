#include <iostream>
#include <string>
#include <locale.h>
#include "EmployeeManagementSystem.h"
#include "user.h"
#include "admin.h"
#include <Windows.h>

// Структура для хранения учетных данных (логин/пароль)
struct UserCredentials {
    std::string login;
    std::string password;
    bool role;
};

// Пример данных для логинов и паролей
UserCredentials adminCredentials = { "admin", "admin123", true };  // Администратор
UserCredentials userCredentials = { "user", "user123", false };   // Пользователь

int main() {
    system("cls");
    // Устанавливаем локаль для поддержки русских символов
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    EmployeeManagementSystem manager;
    Admin admin(manager);
    User user(manager);

    manager.setFileName("employees.tхt");
    manager.readEmployeesFromFile();

    std::string enteredLogin, enteredPassword;
    bool authenticated = false;
    bool role = false;

    // Запрашиваем логин и пароль
    std::cout << "Введите логин: ";
    std::getline(std::cin, enteredLogin);
    std::cout << "Введите пароль: ";
    std::getline(std::cin, enteredPassword);

    // Проверка логина и пароля
    if (enteredLogin == adminCredentials.login && enteredPassword == adminCredentials.password) {
        authenticated = true;
        role = true;
        std::cout << "Вы вошли как Администратор.\n";
    }
    else if (enteredLogin == userCredentials.login && enteredPassword == userCredentials.password) {
        authenticated = true;
        role = false;
        std::cout << "Вы вошли как Пользователь.\n";
    }
    else {
        std::cout << "Неверный логин или пароль. Попробуйте снова.\n";
    }

    // Если аутентификация прошла успешно, показываем меню
    if (authenticated) {
        if (role) {
            // Админ меню
            admin.adminMenu();
        }
        else {
            // Пользователь меню
            user.userMenu();
        }
    }
    manager.writeEmployeesToFile();

    return 0;
}
