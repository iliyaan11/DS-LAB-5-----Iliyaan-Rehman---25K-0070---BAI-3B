#include <iostream>
#include <string>
using namespace std;

class Stack
{
private:
    char arr[100];
    int top;

public:
    Stack()
    {
        top = -1;
    }

    void push(char value)
    {
        arr[++top] = value;
    }

    char pop()
    {
        return arr[top--];
    }

    char peek()
    {
        if (top == -1)
            return '\0';

        return arr[top];
    }

    bool isEmpty()
    {
        return top == -1;
    }
};

int precedence(char op)
{
    if (op == '^')
        return 3;

    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}

bool isOperator(char ch)
{
    return ch == '+' || ch == '-' ||
           ch == '*' || ch == '/' || ch == '^';
}

string infixToPostfix(string infix)
{
    Stack s;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++)
    {
        char ch = infix[i];

        if (ch == ' ')
            continue;

        if (isalnum(ch))
        {
            postfix += ch;
            postfix += ' ';
        }
        else if (ch == '(')
        {
            s.push(ch);
        }
        else if (ch == ')')
        {
            while (!s.isEmpty() && s.peek() != '(')
            {
                postfix += s.pop();
                postfix += ' ';
            }

            if (!s.isEmpty())
                s.pop();
        }
        else if (isOperator(ch))
        {
            while (!s.isEmpty() &&
                   s.peek() != '(' &&
                   precedence(s.peek()) >= precedence(ch))
            {
                postfix += s.pop();
                postfix += ' ';
            }

            s.push(ch);
        }
    }

    while (!s.isEmpty())
    {
        postfix += s.pop();
        postfix += ' ';
    }

    return postfix;
}

string reverseString(string str)
{
    string result = "";

    for (int i = str.length() - 1; i >= 0; i--)
    {
        if (str[i] == '(')
            result += ')';
        else if (str[i] == ')')
            result += '(';
        else
            result += str[i];
    }

    return result;
}

string infixToPrefix(string infix)
{
    string reversed = reverseString(infix);

    string postfix = infixToPostfix(reversed);

    string prefix = "";

    for (int i = postfix.length() - 1; i >= 0; i--)
    {
        prefix += postfix[i];
    }

    return prefix;
}

int main()
{
    string exp1 = "((1-cos(theta))/(1+cos(theta)))";
    string exp2 = "1-(cos(theta)^2)";
    string exp3 = "(1/2)*(cos(alpha-beta)-cos(alpha+beta))";

    cout << "Expression 1:" << endl;
    cout << "Postfix: " << infixToPostfix(exp1) << endl;
    cout << "Prefix:  " << infixToPrefix(exp1) << endl;

    cout << endl;

    cout << "Expression 2:" << endl;
    cout << "Postfix: " << infixToPostfix(exp2) << endl;
    cout << "Prefix:  " << infixToPrefix(exp2) << endl;

    cout << endl;

    cout << "Expression 3:" << endl;
    cout << "Postfix: " << infixToPostfix(exp3) << endl;
    cout << "Prefix:  " << infixToPrefix(exp3) << endl;

    return 0;
}