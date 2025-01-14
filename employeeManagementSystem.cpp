// EmployeeManagementSystem.cpp

#include "EmployeeManagementSystem.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>  // Добавлен для работы с датой и временем 
#include <sstream> // Для разбора даты из строки 
#include <fstream>

Employee::Employee() : fullName(""), department(""), position(""), startDate(""), experience(0) {}

EmployeeManagementSystem::EmployeeManagementSystem() {}

void EmployeeManagementSystem::addEmployee(const Employee& emp) {
	employees.push_back(emp);
}

void EmployeeManagementSystem::viewEmployees() {
	// Просмотр всех сотрудников
	std::cout << "Список сотрудников:\n";
	for (const auto& emp : employees) {
		std::cout << emp.fullName << " - " << emp.department << " - " << emp.position << " - " << emp.startDate << " - " << emp.age <<'\n';
	}
}

void EmployeeManagementSystem::removeEmployee(const std::string& employeeName) {
	auto it = std::remove_if(employees.begin(), employees.end(),
		[&employeeName](const Employee& emp) { return emp.fullName == employeeName; });
	employees.erase(it, employees.end());
}

void EmployeeManagementSystem::editEmployee(const std::string& employeeName) {
	// Найдем сотрудника по имени
	auto it = std::find_if(employees.begin(), employees.end(),
		[&employeeName](const Employee& emp) { return emp.fullName == employeeName; });

	// Проверяем, найден ли сотрудник
	if (it != employees.end()) {
		Employee& emp = *it;  // Ссылаемся на найденного сотрудника
		std::cout << "Редактирование данных сотрудника: " << emp.fullName << "\n";

		// Запрашиваем новые данные для редактирования
		std::cout << "Введите новое ФИО: ";
		std::getline(std::cin, emp.fullName);

		std::cout << "Введите новый отдел: ";
		std::getline(std::cin, emp.department);

		std::cout << "Введите новую должность: ";
		std::getline(std::cin, emp.position);

		std::cout << "Введите новую дату начала работы (ГГГГ/ММ/ДД): ";
		std::getline(std::cin, emp.startDate);

		std::cout << "Введите новый стаж (лет): ";
		std::cin >> emp.experience;
		std::cin.ignore();  // Ожидаем ввода новой строки для очистки буфера ввода

		emp.calculateAge();

		std::cout << "Данные сотрудника были успешно обновлены.\n";
	}
	else {
		std::cout << "Сотрудник с таким именем не найден.\n";
	}
}

void EmployeeManagementSystem::viewRetirementEligible() {
	// Пример выполнения индивидуального задания: сотрудники пенсионного возраста
	for (const auto& emp : employees) {
		if (emp.age >= 60) {  // Примерное условие для пенсионного возраста
			std::cout << emp.fullName << " - Пенсионный возраст\n";
		}
	}
}

void EmployeeManagementSystem::searchEmployee() {
	// Пример поиска сотрудника по нескольким параметрам
	std::string searchTerm;
	std::cout << "Введите параметр для поиска: ";
	std::cin >> searchTerm;

	bool found = false;
	for (const auto& emp : employees) {
		if (emp.fullName.find(searchTerm) != std::string::npos ||
			emp.department.find(searchTerm) != std::string::npos ||
			emp.position.find(searchTerm) != std::string::npos) {
			std::cout << "Найден сотрудник: " << emp.fullName << "\n";
			found = true;
		}
	}

	if (!found) {
		std::cout << "Сотрудники с таким параметром не найдены.\n";
	}
}

void EmployeeManagementSystem::sortByName() {
	// Пример сортировки сотрудников по имени
	std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
		return a.fullName < b.fullName;
		});
	std::cout << "Сотрудники отсортированы по имени.\n";
}

void EmployeeManagementSystem::sortByAge()
{
	std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
		return a.age < b.age;
		});
	std::cout << "Сотрудники отсортированы по имени.\n";
}

void EmployeeManagementSystem::sortByExperience() {
	// Сортировка сотрудников по стажу в порядке убывания
	std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
		return a.getExperience() > b.getExperience();  // Сортировка по убыванию стажа
		});

	std::cout << "Сотрудники отсортированы по стажу.\n";
}

void EmployeeManagementSystem::writeEmployeesToFile()
{
	std::fstream file;

	file.open(fileName, std::ios::out);

	if (!file.is_open()) return;

	file << employees.size() << '\n';

	for (int i = 0; i < employees.size(); i++)
		file << employees[i].fullName << '\t'
		<< employees[i].department << '\t'
		<< employees[i].position << '\t'
		<< std::to_string(employees[i].getExperience()) << '\t'
		<< employees[i].startDate
		<< '\n';


	file.close();
}

void EmployeeManagementSystem::readEmployeesFromFile()
{
	std::fstream file;
	std::string buffer;

	file.open(fileName, std::ios::in);

	if (!file.is_open() || file.eof())
	{
		file.close();
		return;
	}
	std::getline(file, buffer, '\n');

	for (int i = stoi(buffer); i > 0; i--) {
		employees.push_back(Employee());

		std::getline(file, buffer, '\t');
		employees[employees.size() - 1].fullName = buffer;
		std::getline(file, buffer, '\t');
		employees[employees.size() - 1].department = buffer;
		std::getline(file, buffer, '\t');
		employees[employees.size() - 1].position = buffer;
		std::getline(file, buffer, '\t');
		employees[employees.size() - 1].setExperience(std::stoi(buffer));
		std::getline(file, buffer, '\n');
		employees[employees.size() - 1].startDate = buffer;

		employees[employees.size() - 1].calculateAge();
	}


	file.close();
}

void EmployeeManagementSystem::setFileName(std::string fileName) { this->fileName = fileName; }

int Employee::calculateAge() {
	// Текущая дата
	auto now = std::chrono::system_clock::now();
	auto currentDate = std::chrono::system_clock::to_time_t(now);
	struct tm current_tm;
	localtime_s(&current_tm, &currentDate);

	// Разбираем дату начала работы в формате "YYYY MM DD"
	std::istringstream ss(startDate);
	int startYear, startMonth, startDay;
	ss >> startYear >> startMonth >> startDay;

	// Переводим дату начала работы в структуру tm
	struct tm start_tm = {};
	start_tm.tm_year = startYear - 1900;  // Годы считаются от 1900
	start_tm.tm_mon = startMonth - 1;     // Месяцы считаются с 0
	start_tm.tm_mday = startDay;

	// Считаем возраст: разница между годами, учитывая месяц и день
	int calculatedAge = current_tm.tm_year - start_tm.tm_year;

	if (current_tm.tm_mon < start_tm.tm_mon ||
		(current_tm.tm_mon == start_tm.tm_mon && current_tm.tm_mday < start_tm.tm_mday)) {
		calculatedAge--;
	}
	age = calculatedAge;

	return calculatedAge;
}

int Employee::getExperience() const {
	return experience;
}

void Employee::setExperience(int exp)
{
	experience = exp;
}

void EmployeeManagementSystem::sortMenu()
{
	int choice;
	do {
		system("cls");
		std::cout << "Меню администратора:\n";
		std::cout << "1. Сортировать по стажу\n";
		std::cout << "2. Сортировать по возрасту\n";
		std::cout << "3. Сортировать по имени\n";
		std::cout << "0. Выйти\n";
		std::cout << "Выберите действие: ";
		std::cin >> choice;

		system("cls");
		switch (choice) {
		case 1:
			sortByExperience();
			break;
		case 2:
			sortByAge();
			break;
		case 3:
			sortByName();
			break;
		case 0:
			return;
			break;
		default:
			std::cout << "Неверный выбор. Попробуйте снова.\n";
			break;
		}
		system("pause");
	} while (choice != 0);
}