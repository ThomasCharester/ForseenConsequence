// EmployeeManagementSystem.cpp

#include "EmployeeManagementSystem.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>  // �������� ��� ������ � ����� � �������� 
#include <sstream> // ��� ������� ���� �� ������ 
#include <fstream>

Employee::Employee() : fullName(""), department(""), position(""), startDate(""), experience(0) {}

EmployeeManagementSystem::EmployeeManagementSystem() {}

void EmployeeManagementSystem::addEmployee(const Employee& emp) {
	employees.push_back(emp);
}

void EmployeeManagementSystem::viewEmployees() {
	// �������� ���� �����������
	std::cout << "������ �����������:\n";
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
	// ������ ���������� �� �����
	auto it = std::find_if(employees.begin(), employees.end(),
		[&employeeName](const Employee& emp) { return emp.fullName == employeeName; });

	// ���������, ������ �� ���������
	if (it != employees.end()) {
		Employee& emp = *it;  // ��������� �� ���������� ����������
		std::cout << "�������������� ������ ����������: " << emp.fullName << "\n";

		// ����������� ����� ������ ��� ��������������
		std::cout << "������� ����� ���: ";
		std::getline(std::cin, emp.fullName);

		std::cout << "������� ����� �����: ";
		std::getline(std::cin, emp.department);

		std::cout << "������� ����� ���������: ";
		std::getline(std::cin, emp.position);

		std::cout << "������� ����� ���� ������ ������ (����/��/��): ";
		std::getline(std::cin, emp.startDate);

		std::cout << "������� ����� ���� (���): ";
		std::cin >> emp.experience;
		std::cin.ignore();  // ������� ����� ����� ������ ��� ������� ������ �����

		emp.calculateAge();

		std::cout << "������ ���������� ���� ������� ���������.\n";
	}
	else {
		std::cout << "��������� � ����� ������ �� ������.\n";
	}
}

void EmployeeManagementSystem::viewRetirementEligible() {
	// ������ ���������� ��������������� �������: ���������� ����������� ��������
	for (const auto& emp : employees) {
		if (emp.age >= 60) {  // ��������� ������� ��� ����������� ��������
			std::cout << emp.fullName << " - ���������� �������\n";
		}
	}
}

void EmployeeManagementSystem::searchEmployee() {
	// ������ ������ ���������� �� ���������� ����������
	std::string searchTerm;
	std::cout << "������� �������� ��� ������: ";
	std::cin >> searchTerm;

	bool found = false;
	for (const auto& emp : employees) {
		if (emp.fullName.find(searchTerm) != std::string::npos ||
			emp.department.find(searchTerm) != std::string::npos ||
			emp.position.find(searchTerm) != std::string::npos) {
			std::cout << "������ ���������: " << emp.fullName << "\n";
			found = true;
		}
	}

	if (!found) {
		std::cout << "���������� � ����� ���������� �� �������.\n";
	}
}

void EmployeeManagementSystem::sortByName() {
	// ������ ���������� ����������� �� �����
	std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
		return a.fullName < b.fullName;
		});
	std::cout << "���������� ������������� �� �����.\n";
}

void EmployeeManagementSystem::sortByAge()
{
	std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
		return a.age < b.age;
		});
	std::cout << "���������� ������������� �� �����.\n";
}

void EmployeeManagementSystem::sortByExperience() {
	// ���������� ����������� �� ����� � ������� ��������
	std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
		return a.getExperience() > b.getExperience();  // ���������� �� �������� �����
		});

	std::cout << "���������� ������������� �� �����.\n";
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
	// ������� ����
	auto now = std::chrono::system_clock::now();
	auto currentDate = std::chrono::system_clock::to_time_t(now);
	struct tm current_tm;
	localtime_s(&current_tm, &currentDate);

	// ��������� ���� ������ ������ � ������� "YYYY MM DD"
	std::istringstream ss(startDate);
	int startYear, startMonth, startDay;
	ss >> startYear >> startMonth >> startDay;

	// ��������� ���� ������ ������ � ��������� tm
	struct tm start_tm = {};
	start_tm.tm_year = startYear - 1900;  // ���� ��������� �� 1900
	start_tm.tm_mon = startMonth - 1;     // ������ ��������� � 0
	start_tm.tm_mday = startDay;

	// ������� �������: ������� ����� ������, �������� ����� � ����
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
		std::cout << "���� ��������������:\n";
		std::cout << "1. ����������� �� �����\n";
		std::cout << "2. ����������� �� ��������\n";
		std::cout << "3. ����������� �� �����\n";
		std::cout << "0. �����\n";
		std::cout << "�������� ��������: ";
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
			std::cout << "�������� �����. ���������� �����.\n";
			break;
		}
		system("pause");
	} while (choice != 0);
}