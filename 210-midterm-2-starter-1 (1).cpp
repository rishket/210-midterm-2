#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// Added struct to represent customers
struct Customer {
    string name;
    bool vip;
    Customer(const string& n = "", bool v = false) : name(n), vip(v) {}
};

class DoublyLinkedList {
private:
    struct Node {
        Customer data;  // Changed from int to Customer
        Node* prev;
        Node* next;
        Node(const Customer& val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(const Customer& customer, int position) {  // Changed parameter type
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(customer);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_customer(const string& name) {  // Changed to find customer by name
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data.name != name)  // Compare names instead
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(const Customer& c) {  // Changed parameter type
        Node* newNode = new Node(c);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(const Customer& c) {  // Changed parameter type
        Node* newNode = new Node(c);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "Line is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data.name;  // Print customer name
            if (current->data.vip) cout << " (VIP)";
            cout << endl;
            current = current->next;
        }
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "Line is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data.name;  // Print customer name
            if (current->data.vip) cout << " (VIP)";
            cout << endl;
            current = current->prev;
        }
    }

};

int main() {
    // Read names from file
    vector<string> names;
    ifstream in("names.txt");
    if (!in) {
        cout << "Error: Cannot open names.txt" << endl;
        return 1;
    }

    string name;
    while (getline(in, name)) {
        if (!name.empty()) {
            names.push_back(name);
        }
    }

    // Create line and add first 5 customers
    DoublyLinkedList line;
    cout << "Store opens:" << endl;
    
    // Add first 5 customers
    for (int i = 0; i < 5 && i < (int)names.size(); i++) {
        cout << "    " << names[i] << " joins the line" << endl;
        Customer c(names[i], false);
        line.push_back(c);
    }

    cout << "\nInitial line:" << endl;
    line.print();

    return 0;
}