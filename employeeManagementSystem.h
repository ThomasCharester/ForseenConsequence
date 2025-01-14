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
    int experience;  // Количество лет стажа
    int age;

    // Конструктор по умолчанию
    Employee();

    // Метод для вычисления возраста на основе startDate
    int calculateAge();

    // Функция для получения стажа
    int getExperience() const;

    // Функция для изменения стажа
    void setExperience(int exp);
};

class EmployeeManagementSystem {
public:
    EmployeeManagementSystem();  // Конструктор

    // Функции для работы с сотрудниками
    void viewEmployees();  // Просмотр всех сотрудников
    void addEmployee(const Employee& emp);  // Добавление сотрудника
    void removeEmployee(const std::string& employeeName);  // Удаление сотрудника
    void editEmployee(const std::string& employeeName);  // Редактирование сотрудника

    // Функции для выполнения индивидуальных заданий
    void viewRetirementEligible();  // Просмотр сотрудников пенсионного возраста
    void searchEmployee();  // Поиск сотрудников
    void sortByName();  // Сортировка сотрудников по имени
    void sortByAge();  // Сортировка сотрудников по возрасту
    void sortByExperience();  // Сортировка сотрудников по стажу
    void sortMenu(); // Метод для отображения меню сортировки

    // Функции для работы с файлом
    void writeEmployeesToFile();
    void readEmployeesFromFile();
    void setFileName(std::string fileName);
private:
    std::vector<Employee> employees;  // Список сотрудников
    std::string fileName = "employees.tхt"; // Имя файла с сотрудниками
};

#endif // EMPLOYEEMANAGEMENTSYSTEM_
