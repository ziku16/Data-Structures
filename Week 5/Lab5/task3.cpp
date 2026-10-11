#include <iostream>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;

// Node for dynamic linked-list based stack of double values
struct Node {
    double data;
    Node* next;

    Node(double val) : data(val), next(nullptr) {}
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

    void push(double val) {
        Node* newNode = new Node(val);
        newNode->next = topNode;
        topNode = newNode;
    }

    double pop() {
        if (isEmpty()) return 0.0;
        Node* temp = topNode;
        double val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    double peek() const {
        if (isEmpty()) return 0.0;
        return topNode->data;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }
};

// Variable binding structure to map variable characters to numeric values
struct VariableBinding {
    char name;
    double value;
};

// Finds the numeric value associated with a variable character
double getVariableValue(char var, const VariableBinding bindings[], int bindingCount) {
    for (int i = 0; i < bindingCount; i++) {
        if (bindings[i].name == var) {
            return bindings[i].value;
        }
    }
    // Fallback: if character is a digit '0'-'9', convert to number
    if (isdigit(var)) {
        return var - '0';
    }
    cout << "Warning: undefined variable '" << var << "', defaulting to 0." << endl;
    return 0.0;
}

// Evaluates an operation given operator and two operands in correct order
double applyOperator(char op, double val1, double val2) {
    switch (op) {
        case '+': return val1 + val2;
        case '-': return val1 - val2;
        case '*': return val1 * val2;
        case '/':
            if (val2 == 0) {
                cout << "Error: Division by zero encountered!" << endl;
                return 0.0;
            }
            return val1 / val2;
        case '^': return pow(val1, val2);
        default: return 0.0;
    }
}

// Postfix expression evaluation using dynamic stack
double evaluatePostfix(const string& postfix, const VariableBinding bindings[], int bindingCount) {
    DynamicStack evalStack;

    for (size_t i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];

        if (isspace(ch)) continue;

        if (isalnum(ch)) {
            // Operands: look up numeric value and push onto stack
            double val = getVariableValue(ch, bindings, bindingCount);
            evalStack.push(val);
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
            // In postfix: first popped operand is the right operand (op2), second is left (op1)
            double op2 = evalStack.pop();
            double op1 = evalStack.pop();
            double result = applyOperator(ch, op1, op2);
            evalStack.push(result);
        }
    }

    return evalStack.pop();
}

int main() {
    // Demonstration 1: Variable substitution
    // Expression: AB+C*D- equivalent to ((A + B) * C) - D
    string postfix1 = "AB+C*D-";
    VariableBinding bindings1[] = {
        {'A', 5.0},
        {'B', 3.0},
        {'C', 2.0},
        {'D', 4.0}
    };
    int count1 = sizeof(bindings1) / sizeof(bindings1[0]);

    cout << "=== Demonstration 1: Postfix Evaluation with Variables ===" << endl;
    cout << "Postfix Expression: " << postfix1 << endl;
    cout << "Variables: A=5, B=3, C=2, D=4" << endl;
    cout << "Evaluation Steps: (5 + 3) * 2 - 4 = 16 - 4 = 12" << endl;
    cout << "Result: " << evaluatePostfix(postfix1, bindings1, count1) << endl;

    // Demonstration 2: Expression with power operator
    // Expression: XY^Z+ equivalent to (X ^ Y) + Z
    string postfix2 = "XY^Z+";
    VariableBinding bindings2[] = {
        {'X', 3.0},
        {'Y', 2.0},
        {'Z', 10.0}
    };
    int count2 = sizeof(bindings2) / sizeof(bindings2[0]);

    cout << "\n=== Demonstration 2: Exponentiation in Postfix ===" << endl;
    cout << "Postfix Expression: " << postfix2 << endl;
    cout << "Variables: X=3, Y=2, Z=10" << endl;
    cout << "Evaluation Steps: 3^2 + 10 = 9 + 10 = 19" << endl;
    cout << "Result: " << evaluatePostfix(postfix2, bindings2, count2) << endl;

    return 0;
}
