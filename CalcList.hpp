#ifndef CALCLIST_HPP
#define CALCLIST_HPP

#include <string>   // for std::string

// Enum for operation types
enum FUNC {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION
};

class CalcList {
public:
    // Constructor & Destructor
    CalcList();
    ~CalcList();

    // Public methods your test file expects
    void newOperation(FUNC func, double operand);   // add a new operation
    void removeLastOperation();                     // undo last operation
    double total() const;                           // return current total
    std::string toString(int precision) const;      // return operation history

private:
    // Node struct for linked list
    struct Node {
        FUNC func;           // which operation
        double operand;      // the number used
        double totalAfter;   // running total after this operation
        Node* prev;          // pointer to previous operation in history
    };

    Node* tail;             // points to the most recent operation
    double runningTotal;    // current calculator total
    size_t opCount;         // number of operations so far
};

#endif // CALCLIST_HPP
