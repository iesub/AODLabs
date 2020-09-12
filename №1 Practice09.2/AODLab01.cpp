#include <iostream>
#include <string>
using namespace std;

struct node {
public:
    string category = "R";
    int number;
    int timeSpent;
    int categoryNumber;
    node* next = NULL;
    node* prev = NULL;
    void addNode(node* obj, string category, int number, int timeSpent);
    void deleteNode(node* obj);
    void showInf();
    void insert(node* obj, string category, int number, int timeSpent);
    void preorotise();
};

void node::addNode(node* obj, string category, int number, int timeSpent) {
    if (this->next == NULL) {
        this->next = obj;
        obj->prev = this;
    }
    else {
        next->addNode(obj, category, number, timeSpent);
    }
    obj->category = category;
    obj->number = number;
    obj->timeSpent = timeSpent;
    if (obj->category == "M") obj->categoryNumber = 1;
    if (obj->category == "K") obj->categoryNumber = 2;
    if (obj->category == "P") obj->categoryNumber = 3;
}

void node::deleteNode(node* obj) {
    if (obj->next != NULL) {
        obj->prev->next = obj->next;
        obj->next->prev = obj->prev;
        delete(obj);
    }
    else {
        delete(obj);
        this->next = NULL;
    }
}

void node::showInf() {
    cout << "Employee category: " << this->category << " Employee number: " << this->number << " Time spent on solving: " << this->timeSpent << endl;
}

void node::insert(node* obj, string category, int number, int timeSpent) {
    if (this->next != NULL) {
        obj->next = this->next;
        this->next = obj;
    }
    else {
        this->next = obj;
    }
    obj->category = category;
    obj->number = number;
    obj->timeSpent = timeSpent;
    obj->prev = this;
}

void node::preorotise() {
    if (this->next != NULL) {
        if (this->categoryNumber > this->next->categoryNumber) {
            this->next->prev = this->prev;
            this->prev = this->next;
            this->next = this->prev->next;
            this->prev->next = this;
            this->prev->prev->next = this->prev;
            this->preorotise();
        }
        else this->next->preorotise();

    }
}

int main()
{
    node start;
    while (true) {
        string category;
        int number;
        int timeSpent;
        node* obj;
        obj = new node;
        cout << "Employee category: ";
        cin >> category;
        cout << endl;
        cout << "Employee number: ";
        cin >> number;
        cout << endl;
        cout << "Time spent on solving: ";
        cin >> timeSpent;
        cout << endl;
        start.addNode(obj, category, number, timeSpent);
        cout << "Continue? 1-Yes 0-No" << endl;
        int check;
        cin >> check;
        if (check == 0) break;
    }
    start.next->preorotise();
    int timeM = 0;
    int timeK = 0;
    int timeP = 0;
    while (start.next != NULL) {
        start.next->showInf();
        cout << "Done" << endl;
        if (start.next->categoryNumber == 1) timeM += start.next->timeSpent;
        if (start.next->categoryNumber == 2) timeK += start.next->timeSpent;
        if (start.next->categoryNumber == 3) timeP += start.next->timeSpent;
        start.deleteNode(start.next);
    }
    cout << "Time spent on category M: " << timeM << " minutes" << endl;
    cout << "Time spent on category K: " << timeK << " minutes" << endl;
    cout << "Time spent on category P: " << timeP << " minutes" << endl;
}