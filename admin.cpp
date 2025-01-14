#include "admin.h"
#include <iostream>

Admin::Admin(EmployeeManagementSystem& manager) : empManager(manager) {}

void Admin::adminMenu() {
	int choice;
	do {
		system("cls");
		std::cout << "Меню администратора:\n";
		std::cout << "1. Просмотр всех учетных записей\n";
		std::cout << "2. Добавить нового сотрудника\n";
		std::cout << "3. Редактировать сотрудника\n";
		std::cout << "4. Удалить сотрудника\n";
		std::cout << "5. Просмотр сотрудников пенсионного возраста\n";
		std::cout << "6. Список сотрудников по стажу\n";
		std::cout << "7. Поиск сотрудников\n";
		std::cout << "8. Сортировка сотрудников\n";
		std::cout << "0. Выйти\n";
		std::cout << "Выберите действие: ";
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
			std::cout << "Выход из программы.\n";
			return;
			break;
		default:
			std::cout << "Неверный выбор. Попробуйте снова.\n";
			break;
		}
		system("pause");

	} while (choice != 0);
}

void Admin::addEmployee() {
	std::cout << "Добавление нового сотрудника:\n";
	Employee newEmp;

	std::cout << "Введите ФИО: ";
	std::cin.ignore();
	std::getline(std::cin, newEmp.fullName);

	std::cout << "Введите отдел: ";
	std::getline(std::cin, newEmp.department);

	std::cout << "Введите должность: ";
	std::getline(std::cin, newEmp.position);

	while (true) {
		const std::string dateFormat = "ГГГГ ММ ДД";
		std::cout << "Введите дату начала работы (" + dateFormat + "): ";
		try {
			std::getline(std::cin, newEmp.startDate);
			if (dateFormat.size() != newEmp.startDate.size())
				throw(std::string("Неправильный формат даты, попробуйте снова"));
			for (int i = 0; i < newEmp.startDate.size(); i++)
				if (dateFormat[i] == ' ' && newEmp.startDate[i] != ' '
					|| (dateFormat[i] >= 48 && dateFormat[i] <= 57) && (newEmp.startDate[i] < 48 || newEmp.startDate[i] > 57))
					throw(std::string("Неправильный формат даты, попробуйте снова"));

			break;
		}
		catch (std::string exception) {
			std::cout << exception << '\n';
		}
	}
	while (true) {
		try {
			std::cout << "Введите стаж (лет): ";
			if (!(std::cin >> newEmp.experience))
				throw(std::string("Ошибка ввода данных. Попробуйте снова"));
			break;
		}
		catch (std::string exception) {
			std::cout << exception << '\n';
			std::cin.clear();
			std::cin.ignore();
		}
	}

	empManager.addEmployee(newEmp);
	std::cout << "Сотрудник успешно добавлен.\n";
}

void Admin::editEmployee() {
	std::cout << "Введите имя сотрудника для редактирования: ";
	std::string employeeName;
	std::cin.ignore();
	std::getline(std::cin, employeeName);
	empManager.editEmployee(employeeName);
}

void Admin::removeEmployee() {
	empManager.viewEmployees();
	std::cout << "Введите имя сотрудника для удаления: ";
	std::string employeeName;
	std::cin.ignore();
	std::getline(std::cin, employeeName);
	try {
		empManager.removeEmployee(employeeName);
		std::cout << "Сотрудник успешно удален.\n";
	}
	catch (std::string exception) {
		std::cout << exception << '\n';
	}
}

