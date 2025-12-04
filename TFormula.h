#pragma once
#include <iostream>

class TFormula {
	char* str;
public:
	TFormula(char* _str);
	~TFormula();
	TFormula(const TFormula& _str);
	TFormula operator=(const TFormula& _str);
	TFormula();
	int checkbrackets(int arr[], int& n);
	friend std::ostream& operator<<(std::ostream& out, const TFormula& form);
	char* Postfix();
	friend std::istream& operator>>(std::istream& in, TFormula& form);
	double calculate(int& r);
};

bool isdigit(char c);
bool isop(char c);
bool isbracket(char c);
int priority(char op);
