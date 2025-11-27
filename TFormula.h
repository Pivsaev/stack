#pragma once
#include <iostream>

class TFormula {
	char* str;
public:
	TFormula(char* _str);
	~TFormula();
	TFormula(const TFormula& _str);
	TFormula operator=(const TFormula& _str);
	int checkbrackets(int arr[], int& n);
	char* Postfix();
	double calculate(int& r);
	friend std::ostream& operator<<(std::ostream& out, const TFormula& form);
};

bool isdigit(char c);
