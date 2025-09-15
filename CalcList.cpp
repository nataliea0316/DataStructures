#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdio>
#include <sstream> 
#include <iomanip> 
#include "CalcList.hpp"
using namespace std;

// 1) Constructor: set initial state
CalcList::CalcList()
    : tail(nullptr), runningTotal(0.0), opCount(0) {}

// 2) Destructor: free all nodes (prevents memory leaks)
CalcList::~CalcList() {
    while (tail != nullptr) {
        Node* tmp = tail;
        tail = tail->prev;
        delete tmp;
    }
}

void CalcList::newOperation(FUNC func, double operand) {
    double newTotal = runningTotal;

    switch(func)
    {
       case ADDITION:
       newTotal = runningTotal + operand;
       break;
       case SUBTRACTION:
       newTotal = runningTotal - operand;
       break;
       case MULTIPLICATION:
       newTotal = runningTotal * operand;
       break;
       case DIVISION:
       if (operand == 0){
        throw invalid_argument("Cannot divide by zero.");
        }
       newTotal = runningTotal / operand;
       break;

       default:
        throw invalid_argument("Unknown operation");
    }
    Node* node = new Node{func, operand, newTotal, tail};
    tail = node;
    runningTotal = newTotal;
    opCount++;
}

// 3) removeLastOperation
void CalcList::removeLastOperation() {
    if (tail == nullptr) {
        // no operations to undo
        throw std::runtime_error("No operations to remove.");
    }

    // save current node and step back
    Node* old = tail;
    tail = tail->prev;

    // free the removed node
    delete old;

    // update running total
    if (tail != nullptr) {
        runningTotal = tail->totalAfter;
    } else {
        runningTotal = 0.0;   // reset if history is empty
    }

    // decrement operation count
    --opCount;
}



// 4) total
double CalcList::total() const {
    return runningTotal;
}

// 5) toString
std::string CalcList::toString(int precision) const {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision);

    const Node* current = tail;
    int step = opCount;
    bool first = true;
    while (current != nullptr) {
        double before;
        char symbol;

        switch (current->func) {
            case ADDITION:
                before = current->totalAfter - current->operand;
                symbol = '+';
                break;
            case SUBTRACTION:
                before = current->totalAfter + current->operand;
                symbol = '-';
                break;
            case MULTIPLICATION:
                before = (current->operand != 0) 
                         ? current->totalAfter / current->operand
                         : 0;
                symbol = '*';
                break;
            case DIVISION:
                before = current->totalAfter * current->operand;
                symbol = '/';
                break;
        }
        if (!first) out << "\n";  // add newline BEFORE all but the first line
        first = false;

        out << step << ": "
        << before << symbol << current->operand
        << "=" << current->totalAfter;
    

        current = current->prev; // move to the previous node
        --step;
    }

    return out.str();
}
