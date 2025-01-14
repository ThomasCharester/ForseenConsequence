#pragma once
#ifndef ADMIN_H
#define ADMIN_H

#include "employeeManagementSystem.h"
#include <string>

class Admin {
public:
    Admin(EmployeeManagementSystem& manager);  // �����������

    void adminMenu();  // ����� ��� ����������� ���� ��������������
    void addEmployee();  // ����� ��� ���������� ����������
    void editEmployee();  // ����� ��� �������������� ����������
    void removeEmployee();  // ����� ��� �������� ����������

private:
    EmployeeManagementSystem& empManager;  // ������ �� ������ ���������� ������������
};

#endif // ADMIN_H
