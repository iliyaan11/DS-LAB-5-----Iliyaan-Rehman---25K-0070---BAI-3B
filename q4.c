#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char value)
{
    stack[++top] = value;
}

char pop()
{
    return stack[top--];
}

char peek()
{
    return stack[top];
}

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

void infixToPostfix(char infix[], char postfix[])
{
    int i, j = 0;
    char ch;

    top = -1;

    for (i = 0; infix[i] != '\0'; i++)
    {
        ch = infix[i];

        if (ch == ' ')
            continue;

        if (isdigit(ch) || ch == 'x')
        {
            postfix[j++] = ch;
        }
        else if (ch == '(')
        {
            push(ch);
        }
        else if (ch == ')')
        {
            while (!((top == -1)) && peek() != '(')
            {
                postfix[j++] = pop();
            }

            pop();
        }
        else
        {
            while (top != -1 &&
                   peek() != '(' &&
                   precedence(peek()) >= precedence(ch))
            {
                postfix[j++] = pop();
            }

            push(ch);
        }
    }

    while (top != -1)
    {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
}

double valueStack[MAX];
int valueTop = -1;

void pushValue(double value)
{
    valueStack[++valueTop] = value;
}

double popValue()
{
    return valueStack[valueTop--];
}

double evaluatePostfix(char postfix[], double x)
{
    int i;
    char ch;
    double a, b;

    valueTop = -1;

    for (i = 0; postfix[i] != '\0'; i++)
    {
        ch = postfix[i];

        if (ch == ' ')
            continue;

        if (ch == 'x')
        {
            pushValue(x);
        }
        else if (isdigit(ch))
        {
            pushValue(ch - '0');
        }
        else
        {
            b = popValue();
            a = popValue();

            if (ch == '+')
                pushValue(a + b);
            else if (ch == '-')
                pushValue(a - b);
            else if (ch == '*')
                pushValue(a * b);
            else if (ch == '/')
                pushValue(a / b);
            else if (ch == '^')
                pushValue(pow(a, b));
        }
    }

    return popValue();
}

int checkCondition(char condition[], double x)
{
    double value;
    char operator[3];

    if (sscanf(condition, "x %2s %lf", operator, &value) == 2)
    {
        if (strcmp(operator, ">=") == 0)
            return x >= value;

        if (strcmp(operator, "<=") == 0)
            return x <= value;

        if (strcmp(operator, ">") == 0)
            return x > value;

        if (strcmp(operator, "<") == 0)
            return x < value;

        if (strcmp(operator, "==") == 0)
            return x == value;
    }

    return 0;
}

int main()
{
    char expression1[MAX];
    char expression2[MAX];

    char condition1[MAX];
    char condition2[MAX];

    char postfix[MAX];

    double x;
    char selectedExpression[MAX];
    char selectedCondition[MAX];

    printf("Enter Expression 1: ");
    fgets(expression1, MAX, stdin);
    expression1[strcspn(expression1, "\n")] = '\0';

    printf("Enter Condition 1: ");
    fgets(condition1, MAX, stdin);
    condition1[strcspn(condition1, "\n")] = '\0';

    printf("Enter Expression 2: ");
    fgets(expression2, MAX, stdin);
    expression2[strcspn(expression2, "\n")] = '\0';

    printf("Enter Condition 2: ");
    fgets(condition2, MAX, stdin);
    condition2[strcspn(condition2, "\n")] = '\0';

    printf("Enter x: ");
    scanf("%lf", &x);

    if (checkCondition(condition1, x))
    {
        strcpy(selectedExpression, expression1);
        strcpy(selectedCondition, condition1);
    }
    else if (checkCondition(condition2, x))
    {
        strcpy(selectedExpression, expression2);
        strcpy(selectedCondition, condition2);
    }
    else
    {
        printf("\nNo condition is satisfied.\n");
        return 0;
    }

    infixToPostfix(selectedExpression, postfix);

    double result = evaluatePostfix(postfix, x);

    printf("\nThe program selects:\n");
    printf("Condition: %s\n", selectedCondition);
    printf("Expression: %s\n", selectedExpression);
    printf("Postfix: %s\n", postfix);
    printf("Calculated Value: %.2lf\n", result);

    return 0;
}