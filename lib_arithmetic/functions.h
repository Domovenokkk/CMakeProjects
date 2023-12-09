// Copyright 2023 Mezhuev Maksim
#ifndef FUNCTIONS_FUNCTIONS_H_
#define FUNCTIONS_FUNCTIONS_H_


#include <cstdlib>
#include <string>
#include <iostream>
#include <Windows.h>

void PrintMenu() {
	//std::cout << "���� ���������: " << expression << std::endl;
	std::cout << "����:" << std::endl;
	std::cout << "  1. ������ �������� ����������." << std::endl;
	std::cout << "  2. ������� �������� �������� �������." << std::endl;
	std::cout << "  3. ��������� �������� �������." << std::endl;
	std::cout << "  4. ��������� � ������� ���������." << std::endl;
	std::cout << "  5. �����." << std::endl;
	std::cout << "�����: ";
}



class Parser {
	std::string expression;
public:
	Parser() {
		expression = "none";
	}
	Parser(std::string _expression) : expression(_expression) {}
	Parser(const Parser& p) :expression(p.expression) {}

	std::string get_expression() const {
		return expression;
	}

	friend std::ostream& operator << (std::ostream& out, const Parser& p);
	friend std::istream& operator>>(std::istream& input, Parser& p);


	void DeleteSpaces() {
		expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());
	}
};


std::istream& operator>>(std::istream& input, Parser& p) {
	std::cout << "������� ���������: ";
	getline(input, p.expression);
	return input;
}

std::ostream& operator<<(std::ostream& out, Parser& p) {
	out << "���� ���������: " << p.get_expression() << std::endl;
	return out;
}


#endif FUNCTIONS_FUNCTIONS_H_