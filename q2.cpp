#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

class StackList
{
private:
    Node* top;

public:
    StackList()
    {
        top = NULL;
    }

    void push(int value)
    {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    void display()
    {
        Node* temp = top;

        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }

    void sortStack()
    {
        Node* i;
        Node* j;

        for (i = top; i != NULL; i = i->next)
        {
            for (j = i->next; j != NULL; j = j->next)
            {
                if (i->data > j->data)
                {
                    int temp = i->data;
                    i->data = j->data;
                    j->data = temp;
                }
            }
        }
    }

    Node* getTop()
    {
        return top;
    }
};

class CircularQueue
{
private:
    int* queue;
    int size;
    int front;
    int rear;

public:
    CircularQueue(int s)
    {
        size = s;
        queue = new int[size];
        front = -1;
        rear = -1;
    }

    void enqueue(int value)
    {
        if ((rear + 1) % size == front)
        {
            cout << "Queue is full." << endl;
            return;
        }

        if (front == -1)
        {
            front = 0;
            rear = 0;
        }
        else
        {
            rear = (rear + 1) % size;
        }

        queue[rear] = value;
    }

    void display()
    {
        if (front == -1)
        {
            cout << "Queue is empty." << endl;
            return;
        }

        int i = front;

        while (true)
        {
            cout << queue[i] << " ";

            if (i == rear)
                break;

            i = (i + 1) % size;
        }

        cout << endl;
    }
};

int main()
{
    int n1, n2;

    cout << "Enter size of Stack 1: ";
    cin >> n1;

    int* stack1 = new int[n1];

    cout << "Enter elements of Stack 1 from bottom to top:" << endl;

    for (int i = 0; i < n1; i++)
    {
        cin >> stack1[i];
    }

    cout << "Enter size of Stack 2: ";
    cin >> n2;

    int* stack2 = new int[n2];

    cout << "Enter elements of Stack 2 from bottom to top:" << endl;

    for (int i = 0; i < n2; i++)
    {
        cin >> stack2[i];
    }

    StackList stack3;

    int i = 0;
    int j = 0;

    while (i < n1 && j < n2)
    {
        stack3.push(stack1[i]);
        i++;

        stack3.push(stack2[j]);
        j++;
    }

    while (i < n1)
    {
        stack3.push(stack1[i]);
        i++;
    }

    while (j < n2)
    {
        stack3.push(stack2[j]);
        j++;
    }

    cout << endl;
    cout << "Third stack before sorting: ";

    stack3.display();

    stack3.sortStack();

    cout << "Third stack after sorting: ";

    stack3.display();

    int total = n1 + n2;

    CircularQueue queue(total);

    Node* temp = stack3.getTop();

    while (temp != NULL)
    {
        queue.enqueue(temp->data);
        temp = temp->next;
    }

    cout << "Circular Queue: ";
    queue.display();

    delete[] stack1;
    delete[] stack2;

    return 0;
}