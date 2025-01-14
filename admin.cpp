#include "admin.h"
#include <iostream>

Admin::Admin(EmployeeManagementSystem& manager) : empManager(manager) {}

void Admin::adminMenu() {
	int choice;
	do {
		system("cls");
		std::cout << "���� ��������������:\n";
		std::cout << "1. �������� ���� ������� �������\n";
		std::cout << "2. �������� ������ ����������\n";
		std::cout << "3. ������������� ����������\n";
		std::cout << "4. ������� ����������\n";
		std::cout << "5. �������� ����������� ����������� ��������\n";
		std::cout << "6. ������ ����������� �� �����\n";
		std::cout << "7. ����� �����������\n";
		std::cout << "8. ���������� �����������\n";
		std::cout << "0. �����\n";
		std::cout << "�������� ��������: ";
		std::cin >> choice;

		system("cls");
		switch (choice) {
		case 1:
			empManager.viewEmployees(); //+
			break;
		case 2:
			addEmployee(); //+
			break;
		case 3:
			editEmployee(); //+
			break;
		case 4:
			removeEmployee(); //+
			break;
		case 5:
			empManager.viewRetirementEligible(); //+
			break;
		case 6:
			empManager.sortByExperience(); //+
			break;
		case 7:
			empManager.searchEmployee(); //+
			break;
		case 8:
			empManager.sortMenu(); //+
			break;
		case 0:
			std::cout << "����� �� ���������.\n";
			return;
			break;
		default:
			std::cout << "�������� �����. ���������� �����.\n";
			break;
		}
		system("pause");

	} while (choice != 0);
}

void Admin::addEmployee() {
	std::cout << "���������� ������ ����������:\n";
	Employee newEmp;

	std::cout << "������� ���: ";
	std::cin.ignore();
	std::getline(std::cin, newEmp.fullName);

	std::cout << "������� �����: ";
	std::getline(std::cin, newEmp.department);

	std::cout << "������� ���������: ";
	std::getline(std::cin, newEmp.position);

	while (true) {
		const std::string dateFormat = "���� �� ��";
		std::cout << "������� ���� ������ ������ (" + dateFormat + "): ";
		try {
			std::getline(std::cin, newEmp.startDate);
			if (dateFormat.size() != newEmp.startDate.size())
				throw(std::string("������������ ������ ����, ���������� �����"));
			for (int i = 0; i < newEmp.startDate.size(); i++)
				if (dateFormat[i] == ' ' && newEmp.startDate[i] != ' '
					|| (dateFormat[i] >= 48 && dateFormat[i] <= 57) && (newEmp.startDate[i] < 48 || newEmp.startDate[i] > 57))
					throw(std::string("������������ ������ ����, ���������� �����"));

			break;
		}
		catch (std::string exception) {
			std::cout << exception << '\n';
		}
	}
	while (true) {
		try {
			std::cout << "������� ���� (���): ";
			if (!(std::cin >> newEmp.experience))
				throw(std::string("������ ����� ������. ���������� �����"));
			break;
		}
		catch (std::string exception) {
			std::cout << exception << '\n';
			std::cin.clear();
			std::cin.ignore();
		}
	}

	empManager.addEmployee(newEmp);
	std::cout << "��������� ������� ��������.\n";
}

void Admin::editEmployee() {
	std::cout << "������� ��� ���������� ��� ��������������: ";
	std::string employeeName;
	std::cin.ignore();
	std::getline(std::cin, employeeName);
	empManager.editEmployee(employeeName);
}

void Admin::removeEmployee() {
	empManager.viewEmployees();
	std::cout << "������� ��� ���������� ��� ��������: ";
	std::string employeeName;
	std::cin.ignore();
	std::getline(std::cin, employeeName);
	try {
		empManager.removeEmployee(employeeName);
		std::cout << "��������� ������� ������.\n";
	}
	catch (std::string exception) {
		std::cout << exception << '\n';
	}
}

