#pragma once

#ifndef USER_H
#define USER_H

#include "employeeManagementSystem.h"
#include <string>

class User {
public:
    User(EmployeeManagementSystem& manager);  // �����������

    void userMenu();  // ����� ��� ����������� ���� ������������

private:
    EmployeeManagementSystem& empManager;  // ������ �� ������ ���������� ������������
};

#endif // USER_H
