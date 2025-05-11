#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX_SIZE = 100;

class Stack {
private:
    string data[MAX_SIZE];
    int topIndex;

public:
    Stack() {
        topIndex = -1;
    }

    void push(const string& value) {
        if (topIndex < MAX_SIZE - 1) {
            topIndex++;
            data[topIndex] = value;
        }
    }

    void pop() {
        if (!isEmpty()) {
            topIndex--;
        }
    }

    string top() {
        if (!isEmpty()) {
            return data[topIndex];
        }
        return "";
    }

    bool isEmpty() {
        return topIndex == -1;
    }

    void clear() {
        topIndex = -1;
    }
};

class BrowserHistory {
private:
    Stack backStack;
    Stack forwardStack;
    string currentUrl;

public:
    void visit(const string& url) {
        if (!currentUrl.empty()) {
            backStack.push(currentUrl);
        }
        currentUrl = url;
        forwardStack.clear();
        cout << "Visited: " << currentUrl << endl;
    }

    void goBack() {
        if (!backStack.isEmpty()) {
            forwardStack.push(currentUrl);
            currentUrl = backStack.top();
            backStack.pop();
            cout << "Went Back to: " << currentUrl << endl;
        } else {
            cout << "Cannot go back" << endl;
        }
    }

    void goForward() {
        if (!forwardStack.isEmpty()) {
            backStack.push(currentUrl);
            currentUrl = forwardStack.top();
            forwardStack.pop();
            cout << "Went Forward to: " << currentUrl << endl;
        } else {
            cout << "Cannot go forward" << endl;
        }
    }
};

int main() {
    BrowserHistory browser;
    ifstream input("input.txt");
    string command, url;

    while (input >> command) {
        if (command == "VISIT") {
            input >> url;
            browser.visit(url);
        } else if (command == "BACK") {
            browser.goBack();
        } else if (command == "FORWARD") {
            browser.goForward();
        }
    }

    input.close();
    return 0;
}
