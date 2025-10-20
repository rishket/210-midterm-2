#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Customer {
    string name;
    bool vip;
    Customer(const string& n = "", bool v = false) : name(n), vip(v) {}
};

class DoublyLinkedList {
private:
    struct Node {
        Customer data;
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

    void push_back(const Customer& c) {
        Node* newNode = new Node(c);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(const Customer& c) {
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

        Node* temp = head;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) {
            cout << "Line is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data.name;
            if (current->data.vip) cout << " (VIP)";
            cout << endl;
            current = current->next;
        }
    }

    bool is_empty() const {
        return head == nullptr;
    }

    Customer* peek_front() {
        return head ? &head->data : nullptr;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    srand(time(0));

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

    DoublyLinkedList line;
    cout << "Store opens:" << endl;
    
    int nextCustomerIndex = 0;
    
    // Add first 5 customers
    for (int i = 0; i < 5 && i < (int)names.size(); i++) {
        cout << "    " << names[i] << " joins the line" << endl;
        Customer c(names[i], false);
        line.push_back(c);
        nextCustomerIndex++;
    }

    cout << "\nInitial line:" << endl;
    line.print();
    cout << endl;

    // Run simulation for 20 time steps
    for (int t = 1; t <= 20; t++) {
        cout << "Time step #" << t << ":" << endl;
        
        // Try to serve customer (40% chance)
        if (!line.is_empty() && (rand() % 100) < 40) {
            Customer* first = line.peek_front();
            cout << "    " << first->name;
            if (first->vip) cout << " (VIP)";
            cout << " is served" << endl;
            line.pop_front();
        } else if (!line.is_empty()) {
            cout << "    No service this time step" << endl;
        } else {
            cout << "    No one in line" << endl;
        }

        // Try to add new customer (60% chance)
        if ((rand() % 100) < 60 && nextCustomerIndex < (int)names.size()) {
            bool isVip = (rand() % 100) < 10;  // 10% chance for VIP
            cout << "    " << names[nextCustomerIndex];
            if (isVip) cout << " (VIP)";
            cout << " joins the line" << endl;
            
            Customer newCustomer(names[nextCustomerIndex], isVip);
            if (isVip) {
                line.push_front(newCustomer);  // VIPs go to front
            } else {
                line.push_back(newCustomer);   // Others to back
            }
            nextCustomerIndex++;
        }
        
        cout << "    Resulting line:" << endl;
        line.print();
        cout << endl;
    }

    return 0;
}