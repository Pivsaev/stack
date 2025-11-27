#include "TFormula.h"
#include "TStack.h"

std::ostream& operator<<(std::ostream& out, const TFormula& form)
{
	out << form.str;
	return out;
}

bool isdigit(char c)
{
    if ((c != '1') && (c != '2') && (c != '3') && (c != '4') &&
        (c != '5') && (c != '6') && (c != '7') && (c != '8') &&
        (c != '9') && (c != '0')) {
        return false;
    }
    return true;
}

TFormula::TFormula(char* _str)
{
    str = new char[strlen(_str) + 1];
    strcpy(str, _str);
}

TFormula::~TFormula()
{
    delete[] str;
}

TFormula::TFormula(const TFormula& _str)
{
    str = new char[strlen(_str.str) + 1];
    strcpy(str, _str.str);
}

TFormula TFormula::operator=(const TFormula& _str)
{
    if (this != &_str) {
        if (strlen(str) != strlen(_str.str)) {
            delete[] str;
            str = new char[strlen(_str.str) + 1];
        }
    }
    strcpy(str, _str.str);
    return *this;
}

char* TFormula::Postfix()
{
    TStack<char> st;
    // Увеличиваем буфер для безопасности
    char* result = new char[strlen(str) * 3 + 10];  // было *2+1, стало *3+10
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        // Добавляем проверку на переполнение буфера
        if (j >= strlen(str) * 3 + 5) {
            break; // предотвращаем переполнение
        }

        if (isdigit(c) || c == '.') {
            while ((isdigit(str[i]) || str[i] == '.') && j < strlen(str) * 3 + 5) {
                result[j++] = str[i++];
            }
            i--;
            if (j < strlen(str) * 3 + 5) {
                result[j++] = ' ';
            }
        }
        else if (c == '(') {
            if (j < strlen(str) * 3 + 5) {
                st.add(c);
            }
        }
        else if (c == ')') {
            while (!st.isempty() && st.peek() != '(' && j < strlen(str) * 3 + 5) {
                result[j++] = st.peek();
                if (j < strlen(str) * 3 + 5) {
                    result[j++] = ' ';
                }
                st.udalit();
            }
            if (!st.isempty() && st.peek() == '(') {
                st.udalit();
            }
        }
        else if (c == '+' || c == '-') {
            while (!st.isempty() && st.peek() != '(' && j < strlen(str) * 3 + 5) {
                result[j++] = st.peek();
                if (j < strlen(str) * 3 + 5) {
                    result[j++] = ' ';
                }
                st.udalit();
            }
            if (j < strlen(str) * 3 + 5) {
                st.add(c);
            }
        }
        else if (c == '*' || c == '/') {
            while (!st.isempty() && (st.peek() == '*' || st.peek() == '/') && j < strlen(str) * 3 + 5) {
                result[j++] = st.peek();
                if (j < strlen(str) * 3 + 5) {
                    result[j++] = ' ';
                }
                st.udalit();
            }
            if (j < strlen(str) * 3 + 5) {
                st.add(c);
            }
        }
    }

    while (!st.isempty() && j < strlen(str) * 3 + 5) {
        result[j++] = st.peek();
        if (j < strlen(str) * 3 + 5) {
            result[j++] = ' ';
        }
        st.udalit();
    }

    // Гарантируем, что не выйдем за границы
    if (j >= strlen(str) * 3 + 10) {
        j = strlen(str) * 3 + 9;
    }

    result[j] = '\0';
    return result;
}

double TFormula::calculate(int& r)
{
    r = 0;
    TStack<double> st;

    char* postfix = Postfix();
    char token[100];
    int tokenIndex = 0;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        if (isdigit(c) || c == '.') {
            token[tokenIndex++] = c;
        }
        else if (c == ' ' && tokenIndex > 0) {
            token[tokenIndex] = '\0';
            st.add(atof(token));
            tokenIndex = 0;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (st.isempty()) {
                r = -1;
                delete[] postfix;
                return 0;
            }
            double b = st.peek(); st.udalit();

            if (st.isempty()) {
                r = -1;
                delete[] postfix;
                return 0;
            }
            double a = st.peek(); st.udalit();

            double res = 0;
            if (c == '+') res = a + b;
            else if (c == '-') res = a - b;
            else if (c == '*') res = a * b;
            else if (c == '/') {
                if (b == 0) {
                    r = -3;
                    delete[] postfix;
                    return 0;
                }
                res = a / b;
            }

            st.add(res);
        }
    }

    if (st.isempty()) {
        r = -2;
        delete[] postfix;
        return 0;
    }

    double finalResult = st.peek();
    st.udalit();

    delete[] postfix;
    return finalResult;
}
