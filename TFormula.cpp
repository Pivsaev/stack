#include "TFormula.h"
#include "TStack.h"

std::ostream& operator<<(std::ostream& out, const TFormula& form)
{
	out << form.str;
	return out;
}

std::istream& operator>>(std::istream& in, TFormula& form)
{
    const int MAX = 100;
    char buffer[MAX];
    int i = 0;
    char c;
    delete[] form.str;
    while (in.get(c) && c != '\n' && i < MAX - 1) {
        buffer[i] = c;
        i++;
    }
    if (i == MAX - 1) {
        buffer[MAX - 1] = '\0';
    }
    else {
        buffer[i] = '\0';
    }
    if (i > 0) {
        form.str = new char[i + 1];
        for (int j = 0; j <= i; j++) {
            form.str[j] = buffer[j];
        }
    }
    else {
        form.str = nullptr;
    }
    return in;
}

bool isdigit(char c)
{
    bool res = true;
    if ((c != '1') && (c != '2') && (c != '3') && (c != '4') &&
        (c != '5') && (c != '6') && (c != '7') && (c != '8') &&
        (c != '9') && (c != '0')) {
        res =  false;
    }
    return res;
}

bool isop(char c)
{
    bool res = false;
    if ((c == '+') || (c == '-') || (c == '*') || (c == '/')){
        res = true;
    }
    return res;
}

bool isbracket(char c)
{
    bool res = false;
    if ((c == '(') || (c == ')')) {
        res = true;
    }
    return res;
}

int priority(char op)
{
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return 3;
        return 0;
}

TFormula::TFormula(char* _str)
{
    size_t len = strlen(_str);
    str = new char[len + 1];
    for (size_t i = 0; i <= len; i++) {
        str[i] = _str[i];
    }
}

TFormula::~TFormula()
{
    delete[] str;
}

TFormula::TFormula(const TFormula& _str)
{
    if (_str.str) {
        size_t len = strlen(_str.str);
        str = new char[len + 1];
        for (size_t i = 0; i <= len; i++) {
            str[i] = _str.str[i];
        }
    }
    else {
        str = nullptr;
    }
}

TFormula TFormula::operator=(const TFormula& _str)
{
    if (this != &_str) {
        delete[] str;

        if (_str.str) {
            size_t len = strlen(_str.str);
            str = new char[len + 1];
            for (size_t i = 0; i < len; i++) {
                str[i] = _str.str[i];
            }
        }
        else {
            str = nullptr;
        }
    }
    return *this;
}

TFormula::TFormula():str(nullptr) {}

int TFormula::checkbrackets(int arr[], int& n)
{
    n = 0;
    if (!str) {
        return n;
    }
    TDynamicStack<int> stack;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (str[i] == '(') {
            stack.Push(i);
        }
        else if (str[i] == ')') {
            if (stack.IsEmpty()) {
                arr[n++] = i;
            }
            else {
                stack.Pop();
            }
        }
    }
    while (!stack.IsEmpty()) {
        arr[n++] = stack.Pop();
    }
    return n;
}

char* TFormula::Postfix()
{
    int errorPositions[100];
    int errorCount = 0;
    if (checkbrackets(errorPositions, errorCount) != 0) {
        int expt = 1;
        throw expt;
    }
    int len = strlen(str);
    TDynamicStack<char> st(len + 1);
    int maxSize = len * 3 + 1;
    char* result = new char[maxSize];
    int resultIndex = 0;
    bool predetoop = false;

    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (c == ' ') continue;

        if (isdigit(c) || c == '.') {
            bool tochka_bila = (c == '.');
            bool cifra_bila = isdigit(c);
            while (i < len && (isdigit(str[i]) || str[i] == '.')) {
                if (resultIndex >= maxSize - 1) {
                    delete[] result;
                    int expt = 5;
                    throw expt;
                }

                if (str[i] == '.') {
                    if (tochka_bila) {
                        delete[] result;
                        int expt = 2;
                        throw expt;
                    }
                    tochka_bila = true;
                }
                else {
                    cifra_bila = true;
                }

                result[resultIndex++] = str[i++];
            }
            if (!cifra_bila) {
                delete[] result;
                int expt = 3;
                throw expt;
            }

            if (resultIndex >= maxSize - 1) {
                delete[] result;
                int expt = 5;
                throw expt;
            }
            result[resultIndex++] = ' ';
            i--;
            predetoop = false;
        }
        else if (isop(c)) {
            if (c == '-' && (i == 0 || str[i - 1] == '(' || isop(str[i - 1]))) {
                result[resultIndex++] = '0';
                result[resultIndex++] = ' ';
                while (!st.IsEmpty() && isop(st.Peek()) &&
                    priority(st.Peek()) >= priority(c)) {
                    if (resultIndex >= maxSize - 2) {
                        delete[] result;
                        int expt = 5;
                        throw expt;
                    }
                    result[resultIndex++] = st.Pop();
                    result[resultIndex++] = ' ';
                }
                st.Push(c);
                predetoop = true;
            }
            else {
                if (predetoop) {
                    delete[] result;
                    int expt = 6;
                    throw expt;
                }
                while (!st.IsEmpty() && isop(st.Peek()) &&
                    priority(st.Peek()) >= priority(c)) {
                    if (resultIndex >= maxSize - 2) {
                        delete[] result;
                        int expt = 5;
                        throw expt;
                    }
                    result[resultIndex++] = st.Pop();
                    result[resultIndex++] = ' ';
                }
                st.Push(c);
                predetoop = true;
            }
        }
        else if (c == '(') {
            st.Push(c);
        }
        else if (c == ')') {
            while (!st.IsEmpty() && st.Peek() != '(') {
                if (resultIndex >= maxSize - 2) {
                    delete[] result;
                    int expt = 5;
                    throw expt;
                }
                result[resultIndex++] = st.Pop();
                result[resultIndex++] = ' ';
            }
            if (!st.IsEmpty()) {
                st.Pop();
            }
        }
        else {
            delete[] result;
            int expt = 4;
            throw expt;
        }
    }
    while (!st.IsEmpty()) {
        if (resultIndex >= maxSize - 2) {
            delete[] result;
            int expt = 5;
            throw expt;
        }
        result[resultIndex++] = st.Pop();
        result[resultIndex++] = ' ';
    }
    if (resultIndex > 0) {
        if (result[resultIndex - 1] == ' ') {
            result[resultIndex - 1] = '\0';
        }
        else {
            result[resultIndex] = '\0';
        }
    }
    else {
        result[0] = '\0';
    }
    return result;
}

double TFormula::calculate(int& r)
{
    r = 0;
    char* pf = Postfix();

    TDynamicStack<double> st(strlen(pf) + 1);

    for (int i = 0; i < strlen(pf); i++) {
        if (pf[i] == ' ') continue;

        if (isdigit(pf[i]) || pf[i] == '.') {
            double n = 0;
            double d = 1;
            bool point = false;

            while (i < strlen(pf) && (isdigit(pf[i]) || pf[i] == '.')) {
                if (pf[i] == '.') {
                    point = true;
                }
                else if (!point) {
                    n = n * 10 + (pf[i] - '0');
                }
                else {
                    n = n + (pf[i] - '0') / (d * 10);
                    d = d * 10;
                }
                i++;
            }
            i--;
            st.Push(n);
        }
        else if (isop(pf[i])) {
            double b = st.Pop();
            double a = st.Pop();
            double res;

            if (pf[i] == '+') res = a + b;
            else if (pf[i] == '-') res = a - b;
            else if (pf[i] == '*') res = a * b;
            else if (pf[i] == '/') res = a / b;

            st.Push(res);
        }
    }

    double res = st.Pop();
    delete[] pf;
    return res;
}
