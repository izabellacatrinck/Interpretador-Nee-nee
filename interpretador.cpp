#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <utility>

// Para std::pair

using namespace std;

// List template class
template <typename T>
class List
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(T value) : data(value), next(nullptr) {}
    };
    Node *head;
    Node *tail;
    int size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}

    ~List()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }

    void append(T value)
    {
        Node *newNode = new Node(value);
        if (tail)
        {
            tail->next = newNode;
        }
        else
        {
            head = newNode;
        }
        tail = newNode;
        size++;
    }

    T get(int index)
    {
        Node *current = head;
        for (int i = 0; i < index; ++i)
        {
            if (current)
            {
                current = current->next;
            }
            else
            {
                throw out_of_range("Index out of range");
            }
        }
        return current ? current->data : throw out_of_range("Index out of range");
    }

    int getSize()
    {
        return size;
    }
};

// Stack template class
template <typename T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(T value) : data(value), next(nullptr) {}
    };
    Node *top;

public:
    Stack() : top(nullptr) {}

    ~Stack()
    {
        while (top)
        {
            Node *temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(T value)
    {
        Node *newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    T pop()
    {
        if (!top)
            throw out_of_range("Stack is empty");
        Node *temp = top;
        top = top->next;
        T value = temp->data;
        delete temp;
        return value;
    }

    T peek()
    {
        if (!top)
            throw out_of_range("Stack is empty");
        return top->data;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }
};

// Function to parse the Nee code and store functions and their commands
unordered_map<char, List<string>> parse_code(const string &code)
{
    istringstream iss(code);
    unordered_map<char, List<string>> functions;
    string line;
    char current_function = '\0';

    while (getline(iss, line))
    {
        if (line.back() == ':')
        {
            current_function = line[0];
            functions[current_function] = List<string>();
        }
        else if (line.empty())
        {
            current_function = '\0';
        }
        else
        {
            if (current_function != '\0')
            {
                functions[current_function].append(line);
            }
        }
    }

    return functions;
}

// Function to execute the Nee code
string execute_nee(const string &code)
{
    auto functions = parse_code(code);
    Stack<pair<char, int>> call_stack;
    ostringstream output;

    auto execute_function = [&](char name)
    {
        if (functions.find(name) == functions.end())
        {
            return;
        }

        List<string> &commands = functions[name];
        for (int i = 0; i < commands.getSize(); ++i)
        {
            string command = commands.get(i);
            if (command.rfind("PRINT ", 0) == 0)
            {
                string value = command.substr(6);
                output << value << " ";
            }
            else if (functions.find(command[0]) != functions.end())
            {
                call_stack.push({name, i});
                execute_function(command[0]);
                auto [return_function, return_index] = call_stack.pop();
                i = return_index;
            }
        }
    };

    execute_function('Z');

    return output.str();
}

// Main function
int main()
{
    string nee_code = R"(B :
PRINT 5
A
PRINT 6

A :
PRINT 3
PRINT 4

Z :
PRINT 1
A
B
PRINT 2
)";

    string result = execute_nee(nee_code);
    cout << result << endl;

    return 0;
}
