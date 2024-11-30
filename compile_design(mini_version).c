#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100  // Maximum size of the expression

// Stack for operators and operands
int opStack[MAX];  // Stack for operators
double valStack[MAX];  // Stack for values (operands)

// Function prototypes
int precedence(char op);
void applyOperator(char op, double *a, double *b, double *result);
double evaluateExpression(const char* expr);
void pushOperator(int* stack, int* top, char op);
void pushValue(double* stack, int* top, double value);
char popOperator(int* stack, int* top);
double popValue(double* stack, int* top);

int main() {
    char expression[MAX];

    printf("Enter a mathematical expression (e.g., 2 + 3 * 4): ");
    fgets(expression, sizeof(expression), stdin);

    // Remove newline character if present
    expression[strcspn(expression, "\n")] = 0;

    // Evaluate and print result
    double result = evaluateExpression(expression);
    printf("Result: %.2f\n", result);

    return 0;
}

// Function to determine the precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

// Function to apply an operator to two values and store the result
void applyOperator(char op, double *a, double *b, double *result) {
    switch (op) {
        case '+': *result = *a + *b; break;
        case '-': *result = *a - *b; break;
        case '*': *result = *a * *b; break;
        case '/': *result = *a / *b; break;
        default: *result = 0; break;
    }
}

// Function to evaluate the expression
double evaluateExpression(const char* expr) {
    int opTop = -1, valTop = -1;
    int i = 0;
    char currentChar;

    while ((currentChar = expr[i++]) != '\0') {
        if (isspace(currentChar)) {
            continue;  // Skip spaces
        }

        if (isdigit(currentChar)) {
            // If currentChar is a number, process it as a value
            double num = 0;
            while (isdigit(currentChar)) {
                num = num * 10 + (currentChar - '0');
                currentChar = expr[i++];
            }
            i--;  // Adjust for the extra increment from the inner loop
            pushValue(valStack, &valTop, num);  // Push value to value stack
        }
        else if (currentChar == '(') {
            pushOperator(opStack, &opTop, currentChar);  // Push '(' to operator stack
        }
        else if (currentChar == ')') {
            // Resolve the stack until we encounter '('
            while (opTop >= 0 && opStack[opTop] != '(') {
                double b = popValue(valStack, &valTop);
                double a = popValue(valStack, &valTop);
                char op = popOperator(opStack, &opTop);
                double result = 0;
                applyOperator(op, &a, &b, &result);
                pushValue(valStack, &valTop, result);
            }
            popOperator(opStack, &opTop);  // Pop '(' from the operator stack
        }
        else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
            // While the operator on the stack has higher precedence, apply it
            while (opTop >= 0 && precedence(opStack[opTop]) >= precedence(currentChar)) {
                double b = popValue(valStack, &valTop);
                double a = popValue(valStack, &valTop);
                char op = popOperator(opStack, &opTop);
                double result = 0;
                applyOperator(op, &a, &b, &result);
                pushValue(valStack, &valTop, result);
            }
            // Push the current operator to the stack
            pushOperator(opStack, &opTop, currentChar);
        }
    }

    // Process remaining operators in the stack
    while (opTop >= 0) {
        double b = popValue(valStack, &valTop);
        double a = popValue(valStack, &valTop);
        char op = popOperator(opStack, &opTop);
        double result = 0;
        applyOperator(op, &a, &b, &result);
        pushValue(valStack, &valTop, result);
    }

    return popValue(valStack, &valTop);  // The final result is at the top of the value stack
}

// Push operator onto the stack
void pushOperator(int* stack, int* top, char op) {
    stack[++(*top)] = op;
}

// Push value onto the stack
void pushValue(double* stack, int* top, double value) {
    stack[++(*top)] = value;
}

// Pop operator from the stack
char popOperator(int* stack, int* top) {
    return (char)stack[(*top)--];
}

// Pop value from the stack
double popValue(double* stack, int* top) {
    return stack[(*top)--];
}
