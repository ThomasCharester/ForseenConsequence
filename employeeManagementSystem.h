#pragma once

#ifndef EMPLOYEEMANAGEMENTSYSTEM_H
#define EMPLOYEEMANAGEMENTSYSTEM_H

#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

class Employee {
public:
    std::string fullName;
    std::string department;
    std::string position;
    std::string startDate;
    int experience;  // ���������� ��� �����
    int age;

    // ����������� �� ���������
    Employee();

    // ����� ��� ���������� �������� �� ������ startDate
    int calculateAge();

    // ������� ��� ��������� �����
    int getExperience() const;

    // ������� ��� ��������� �����
    void setExperience(int exp);
};

class EmployeeManagementSystem {
public:
    EmployeeManagementSystem();  // �����������

    // ������� ��� ������ � ������������
    void viewEmployees();  // �������� ���� �����������
    void addEmployee(const Employee& emp);  // ���������� ����������
    void removeEmployee(const std::string& employeeName);  // �������� ����������
    void editEmployee(const std::string& employeeName);  // �������������� ����������

    // ������� ��� ���������� �������������� �������
    void viewRetirementEligible();  // �������� ����������� ����������� ��������
    void searchEmployee();  // ����� �����������
    void sortByName();  // ���������� ����������� �� �����
    void sortByAge();  // ���������� ����������� �� ��������
    void sortByExperience();  // ���������� ����������� �� �����
    void sortMenu(); // ����� ��� ����������� ���� ����������

    // ������� ��� ������ � ������
    void writeEmployeesToFile();
    void readEmployeesFromFile();
    void setFileName(std::string fileName);
private:
    std::vector<Employee> employees;  // ������ �����������
    std::string fileName = "employees.t�t"; // ��� ����� � ������������
};

#endif // EMPLOYEEMANAGEMENTSYSTEM_
