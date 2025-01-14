#pragma once

#ifndef USER_H
#define USER_H

#include "employeeManagementSystem.h"
#include <string>

class User {
public:
    User(EmployeeManagementSystem& manager);  // Конструктор

    void userMenu();  // Метод для отображения меню пользователя

private:
    EmployeeManagementSystem& empManager;  // Ссылка на объект управления сотрудниками
};

#endif // USER_H
