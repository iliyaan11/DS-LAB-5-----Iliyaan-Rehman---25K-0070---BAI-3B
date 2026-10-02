#include <iostream>
using namespace std;

int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    int stack[100];

    cout << "Enter elements from bottom to top:" << endl;

    for (int i = 0; i < n; i++)
    {
        cin >> stack[i];
    }

    int maximum = stack[0];
    int minimum = stack[0];

    for (int i = 1; i < n; i++)
    {
        if (stack[i] > maximum)
            maximum = stack[i];

        if (stack[i] < minimum)
            minimum = stack[i];
    }

    cout << "Maximum value: " << maximum << endl;
    cout << "Minimum value: " << minimum << endl;

    if (n % 2 == 1)
    {
        int middle = stack[n / 2];
        cout << "Middle element: " << middle << endl;
    }
    else
    {
        int middle1 = stack[(n / 2) - 1];
        int middle2 = stack[n / 2];

        cout << "Middle elements: " << middle1 << " and " << middle2 << endl;
    }

    return 0;
}