#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Node for dynamic linked-list based stack
struct Node {
    char data;
    Node* next;

    Node(char val) : data(val), next(nullptr) {}
};

// Dynamic Stack implementation without STL containers
class DynamicStack {
private:
    Node* topNode;

public:
    DynamicStack() : topNode(nullptr) {}

    ~DynamicStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(char val) {
        Node* newNode = new Node(val);
        newNode->next = topNode;
        topNode = newNode;
    }

    char pop() {
        if (isEmpty()) return '\0';
        Node* temp = topNode;
        char val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    char peek() const {
        if (isEmpty()) return '\0';
        return topNode->data;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }
};

// Determines operator precedence: higher value means higher precedence
int getPrecedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0; // For parentheses or non-operators
}

// Right-associative operators (e.g., '^') are evaluated right to left
bool isRightAssociative(char op) {
    return op == '^';
}

// Infix to Postfix conversion using Shunting Yard algorithm with dynamic stack
string infixToPostfix(const string& infix) {
    DynamicStack opStack;
    string postfix = "";

    for (size_t i = 0; i < infix.length(); i++) {
        char ch = infix[i];

        if (isspace(ch)) continue;

        // Operands (letters/digits) go directly to output
        if (isalnum(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            // Left parenthesis acts as a barrier on stack
            opStack.push(ch);
        } else if (ch == ')') {
            // Pop operators to output until matching '(' is encountered
            while (!opStack.isEmpty() && opStack.peek() != '(') {
                postfix += opStack.pop();
            }
            if (!opStack.isEmpty() && opStack.peek() == '(') {
                opStack.pop(); // Discard the '('
            }
        } else {
            // Operator handling based on precedence and associativity rules:
            // Left-associative: pop if top has greater or equal precedence
            // Right-associative: pop only if top has strictly greater precedence
            while (!opStack.isEmpty() && opStack.peek() != '(') {
                char topOp = opStack.peek();
                int topPrec = getPrecedence(topOp);
                int currPrec = getPrecedence(ch);

                if (topPrec > currPrec || (topPrec == currPrec && !isRightAssociative(ch))) {
                    postfix += opStack.pop();
                } else {
                    break;
                }
            }
            opStack.push(ch);
        }
    }

    // Pop remaining operators from stack
    while (!opStack.isEmpty()) {
        char top = opStack.pop();
        if (top != '(') postfix += top;
    }

    return postfix;
}

int main() {
    string expressions[] = {
        "(A+B)*(C-D)",
        "A+B*C^D-E",
        "((A+B)*C)-D/E",
        "A*(B+C)/D",
        "K+L-M*N+(O^P)*W/U/V*T+Q"
    };

    cout << "=== Infix to Postfix Conversion (Dynamic Stack) ===" << endl;
    for (const string& expr : expressions) {
        cout << "Infix:   " << expr << endl;
        cout << "Postfix: " << infixToPostfix(expr) << "\n" << endl;
    }

    return 0;
}
