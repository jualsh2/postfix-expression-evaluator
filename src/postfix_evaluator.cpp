#include <iostream>
#include <string>
#include <sstream> // For stringstream to tokenize input
#include <cmath>   

using namespace std;

class stackType {

private:

    int maxStackSize;
    int stackTop; 
    int *list;

public:

    stackType(int a);
    ~stackType();
    void initializeStack();
    bool isEmpty();
    bool isFull();
    void push(int newItem);
    void pop();
    int top();
    void print();
};

stackType::stackType(int a) {
    maxStackSize = a;
    stackTop = 0;
    list = new int[maxStackSize];
}
    
void stackType::initializeStack() {
    if(!isEmpty())
        stackTop = 0;
}

bool stackType::isEmpty() {
    return (stackTop == 0);
}

bool stackType::isFull() {
    return (stackTop == maxStackSize);
}

void stackType::push(int newItem) {
    if (!isFull()) 
        list[stackTop++] = newItem;
    else
        cout << "Stack is full. Cannot push element " << newItem << "." << endl;
}

void stackType::pop() {
    if (!isEmpty())
        stackTop--;
    else
        cout << "Stack is empty. Cannot pop from an empty stack." << endl;
}

int stackType::top() {
    if (!isEmpty()) 
        return list[stackTop - 1];
    else {
        cout << "Stack is empty." << endl;
        return -1;
    }
}

void stackType::print() {
    if (isEmpty()) {
        cout << "Stack is empty." << endl;
        return;
    }

    stackType temp(maxStackSize);

    cout << "Stack elements (top to bottom):" << endl;
    while (!isEmpty()) {
        int value = top();
        cout << value << endl;
        temp.push(value);
        pop();
    }

    while (!temp.isEmpty()) {
        push(temp.top());
        temp.pop();
    }
}

stackType::~stackType() {
    delete[] list;
}


class Queue {

private: 

    int maxQSize;
    int queFront;
    int queRear;
    int length;
    string *queue; // I use STRING queue to store tokens

public:

    Queue(int a = 100);
    ~Queue();
    bool isEmptyQ();
    bool isFullQ();
    string front();
    string rear();
    void addQue(string item);
    void deQue();
    void clearQueue();
    void printQueue();
};

Queue::Queue(int size) {
    if(size < 0)
        maxQSize = 100;
    else 
        maxQSize = size;
        
    length = 0;
    queFront = 0;
    queRear = maxQSize - 1;
    queue = new string[maxQSize]; 
}

bool Queue::isEmptyQ() {
    return (length == 0);
}

bool Queue::isFullQ() {
    return (length == maxQSize);
}

void Queue::deQue() {
    if (isEmptyQ())
        cout << "Empty Queue" << endl;
    else {
        queFront = (queFront + 1) % maxQSize;
        length--;
    }
}

void Queue::addQue(string item) {
    if (isFullQ())
        cout << "Full Queue" << endl;
    else {
        queRear = (queRear + 1) % maxQSize;
        queue[queRear] = item;
        length++;
    }
}

string Queue::front() {
    if (!isEmptyQ())
        return queue[queFront];
    else {
        cout << "Queue is empty." << endl;
        return "";
    }
}

string Queue::rear() {
    if (!isEmptyQ())
        return queue[queRear];
    else {
        cout << "Queue is empty." << endl;
        return "";
    }
}

void Queue::clearQueue() {
    length = 0;
    queFront = 0;
    queRear = maxQSize - 1;
}

void Queue::printQueue() {
    if (isEmptyQ()) {
        cout << "Queue is empty." << endl;
        return;
    }
    
    cout << "Queue elements: ";
    for (int i = 0; i < length; i++) {
        cout << queue[(queFront + i) % maxQSize] << " ";
    }
    cout << endl;
}

Queue::~Queue() {
    delete[] queue;
}


// Postfix Evaluation Functions

// Function to check if a string is an operator
bool isOperator(string token) 
{
    return (token == "+" || token == "-" || token == "*" || token == "/" || token == "^");
}

// Function to check if a string is a number (integer)
bool isNumber(string token) 
{
    if(token.empty())
    {
        return false;
    } 
    
    int start = 0;

    if (token[0] == '-' || token[0] == '+')
    {
        if(token.length() == 1)
            return false;
            start = 1; // allow negative numbers
    } 

    for(int i = start; i < token.length(); i++) 
    {
        if(!isdigit(token[i]))
            return false;
    }
    return true;
}

// Function to compute a binary operation
int compute(int a, int b, string op, bool &errorFlag) 
{
    if(op == "+") 
        return a + b;

    if(op == "-") 
        return a - b;

    if(op == "*") 
        return a * b;

    if(op == "/") 
    {
        if(b == 0) 
        {
            cout << "Error: division by zero" << endl;
            errorFlag = true; 
            return 0;
        }
        return a / b;
    }

    if(op == "^") 
        return pow(a, b);
    else
    {
        cout << "Error: unknown operator " << op << endl;
        errorFlag = true;
        return 0;
    }
}

// Function to evaluate postfix expression using queue and stack
void evaluatePostfix(Queue &q) 
{
    stackType stack(100);
    bool errorFlag = false; 

    while(!q.isEmptyQ() && !errorFlag) 
    {
        string token = q.front();
        q.deQue();

        if(isNumber(token)) 
        {
            try 
            {
                int num = stoi(token); 
                stack.push(num);
            } 
            catch (...) 
            { 
                cout << "Error: invalid number '" << token << "'" << endl;
                return; 
            }
        }
        else if(isOperator(token)) 
        {
            if(stack.isEmpty()) 
            { 
                cout << "Error: insufficient operands" << endl; 
                errorFlag = true; 
                break; 
            }

            int b = stack.top(); 
            stack.pop();

            if(stack.isEmpty()) 
            { 
                cout << "Error: insufficient operands" << endl; 
                errorFlag = true; 
                break; 
            }

            int a = stack.top(); 
            stack.pop();
            int result = compute(a, b, token, errorFlag);

            if(errorFlag) 
                break;

            stack.push(result);
        } 
        else {
            cout << "Error: invalid token " << token << endl;
            errorFlag = true;
            break;
        }
    }

    if(!errorFlag) {
        if(stack.isEmpty()) 
        { 
            cout << "Error: no result on stack" << endl; 
            return; 
        }

        int finalResult = stack.top(); 
        stack.pop();

        if(!stack.isEmpty()) 
        { 
            cout << "Error: leftover operands" << endl; 
            return; 
        }
        
        cout << "Result: " << finalResult << endl;
    }
}

int main() 
{
    string input;
    cout << "Enter a postfix expression (space separated): ";
    getline(cin, input);

    Queue q(20);

    stringstream ss(input);
    string token;

    while(ss >> token) 
    {
        //if(!token.empty())
        q.addQue(token); // add each token
    }

    evaluatePostfix(q); 
    
    return 0;
}