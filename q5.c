#include <stdio.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char ch)
{
    stack[++top] = ch;
}

char pop()
{
    return stack[top--];
}

void generateSeries(int n)
{
    int i;
    int term;

    printf("Series: ");

    for (i = 1; i <= n; i++)
    {
        term = 3 * i - 2;

        printf("%d", term);

        if (i < n)
            printf(" + ");
    }

    printf("\n");
}

void generatePostfix(int n)
{
    int i;
    int term;

    printf("Postfix: ");

    for (i = 1; i <= n; i++)
    {
        term = 3 * i - 2;

        printf("%d ", term);

        if (i > 1)
        {
            printf("+ ");
        }
    }

    printf("\n");
}

void generatePrefix(int n)
{
    int i;
    int term;

    printf("Prefix:");

    for (i = 1; i < n; i++)
    {
        push('+');
    }

    for (i = 1; i <= n; i++)
    {
        term = 3 * i - 2;

        printf(" %d", term);
    }

    for (i = 0; i < n - 1; i++)
    {
        printf(" %c", pop());
    }

    printf("\n");
}

int main()
{
    int n;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of terms must be greater than 0.\n");
        return 0;
    }

    generateSeries(n);
    generatePostfix(n);
    generatePrefix(n);

    return 0;
}