#pragma once
#ifndef ADMIN_H
#define ADMIN_H

#include "employeeManagementSystem.h"
#include <string>

class Admin {
public:
    Admin(EmployeeManagementSystem& manager);  // Конструктор

    void adminMenu();  // Метод для отображения меню администратора
    void addEmployee();  // Метод для добавления сотрудника
    void editEmployee();  // Метод для редактирования сотрудника
    void removeEmployee();  // Метод для удаления сотрудника

private:
    EmployeeManagementSystem& empManager;  // Ссылка на объект управления сотрудниками
};

#endif // ADMIN_H
