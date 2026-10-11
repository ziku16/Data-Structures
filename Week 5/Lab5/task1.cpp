#include <iostream>
#include <string>
using namespace std;

// Node for dynamic (linked-list based) stack
struct Node {
    char data;
    Node* next;

    Node(char val) : data(val), next(nullptr) {}
};

// Dynamic Stack implementation without STL
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

// Bracket nesting priority hierarchy:
// Square bracket '[' has highest priority (3), curly '{' is middle (2), parenthesis '(' is lowest (1).
// Higher priority brackets must encapsulate lower priority brackets, not the reverse.
int getBracketPriority(char ch) {
    switch (ch) {
        case '[': case ']': return 3;
        case '{': case '}': return 2;
        case '(': case ')': return 1;
        default: return 0;
    }
}

bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

// Validates both correct closing order and bracket priority hierarchy
bool isBalancedWithPriority(const string& expr, string& reason) {
    DynamicStack s;

    for (size_t i = 0; i < expr.length(); i++) {
        char ch = expr[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            // Priority check: an inner opening bracket cannot have higher priority than the outer opening bracket
            if (!s.isEmpty()) {
                int currentPriority = getBracketPriority(ch);
                int topPriority = getBracketPriority(s.peek());
                if (currentPriority > topPriority) {
                    reason = "Priority violated: '" + string(1, ch) + "' cannot be placed inside '" + string(1, s.peek()) + "'";
                    return false;
                }
            }
            s.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.isEmpty()) {
                reason = "Unmatched closing bracket: '" + string(1, ch) + "'";
                return false;
            }

            char top = s.pop();
            if (!isMatchingPair(top, ch)) {
                reason = "Mismatched pair: opened with '" + string(1, top) + "' but closed with '" + string(1, ch) + "'";
                return false;
            }
        }
    }

    if (!s.isEmpty()) {
        reason = "Unclosed bracket remaining on stack: '" + string(1, s.peek()) + "'";
        return false;
    }

    reason = "All brackets matched and priority hierarchy preserved";
    return true;
}

int main() {
    string testCases[] = {
        "[{( )}]",      // Valid: [ > { > (
        "{[( )] }",     // Invalid: [ opened inside { violates priority
        "[(])",         // Invalid: improper nesting
        "(([]))",       // Invalid: [ opened inside ( violates priority
        "[{}(){()}]"    // Valid: proper priority order maintained
    };

    cout << "=== Bracket Balancing with Priority Hierarchy Check ===" << endl;
    for (const string& expr : testCases) {
        string reason;
        bool balanced = isBalancedWithPriority(expr, reason);
        cout << "Expression: " << expr << endl;
        cout << "Result:     " << (balanced ? "Balanced" : "Not Balanced") << endl;
        cout << "Reason:     " << reason << "\n" << endl;
    }

    return 0;
}
