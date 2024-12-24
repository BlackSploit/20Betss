#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

// Structure for representing a three-address code
typedef struct {
    char result[MAX];
    char operand1[MAX];
    char operand2[MAX];
    char operator[MAX];
} ThreeAddressCode;

// Array to hold the intermediate code instructions
ThreeAddressCode tac[MAX];
int tacIndex = 0;

// Function to generate intermediate code for expressions
void generateIntermediateCode(char *exp) {
    char stack[MAX][MAX];
    int top = -1;
    int tempCount = 1;  // Temporary variable count (t1, t2, ...)
    
    // Traverse through each character in the expression
    for (int i = 0; i < strlen(exp); i++) {
        char current = exp[i];
        
        // If the character is an operand (either a variable or number)
        if (isalnum(current)) {
            stack[++top][0] = current;
            stack[top][1] = '\0';  // Null-terminate the string
        }
        
        // If the character is an operator
        else if (current == '+' || current == '-' || current == '*' || current == '/') {
            char operand2[MAX], operand1[MAX];
            strcpy(operand2, stack[top--]);
            strcpy(operand1, stack[top--]);

            // Generate a temporary variable (e.g., t1, t2, ...)
            char tempVar[MAX];
            sprintf(tempVar, "t%d", tempCount++);
            
            // Store the operation in intermediate code
            strcpy(tac[tacIndex].result, tempVar);
            strcpy(tac[tacIndex].operand1, operand1);
            strcpy(tac[tacIndex].operand2, operand2);
            sprintf(tac[tacIndex].operator, "%c", current);
            tacIndex++;
            
            // Push the temporary result back onto the stack
            strcpy(stack[++top], tempVar);
        }
    }
}

// Function to print the generated intermediate code
void printIntermediateCode() {
    printf("Intermediate Code (Three-Address Code):\n");
    for (int i = 0; i < tacIndex; i++) {
        printf("%s = %s %s %s\n", tac[i].result, tac[i].operand1, tac[i].operator, tac[i].operand2);
    }
}

int main() {
    char expression[MAX];
    
    printf("Enter an arithmetic expression (e.g., a+b*c): ");
    scanf("%s", expression);
    
    // Generate intermediate code
    generateIntermediateCode(expression);
    
    // Print the intermediate code
    printIntermediateCode();
    
    return 0;
}
