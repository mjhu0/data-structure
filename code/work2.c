// 542313460109 胡华吉 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

// 定义栈结构
typedef struct {
    double arr[MAX];
    int top;
} Stack;

// 初始化栈
void initStack(Stack* stack) {
    stack->top = -1;
}

// 判断栈是否为空
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// 入栈
void push(Stack* stack, double value) {
    stack->arr[++stack->top] = value;
}

// 出栈
double pop(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->arr[stack->top--];
    }
    return -1;
}

// 获取栈顶元素
double peek(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->arr[stack->top];
    }
    return -1;
}

// 判断是否为运算符
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

// 获取运算符的优先级
int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/' || c == '%') return 2;
    return 0;
}

// 计算表达式的值
double evaluateExpression(char* expr) {
    Stack numStack, opStack;
    initStack(&numStack);
    initStack(&opStack);
    
    for (int i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];
        
        if (isdigit(c)) {
            push(&numStack, c - '0');
        } else if (c == '(') {
            push(&opStack, c);
        } else if (c == ')') {
            while (!isEmpty(&opStack) && peek(&opStack) != '(') {
                double b = pop(&numStack);
                double a = pop(&numStack);
                char op = pop(&opStack);
                double result;
                
                switch (op) {
                    case '+': result = a + b; break;
                    case '-': result = a - b; break;
                    case '*': result = a * b; break;
                    case '/': result = a / b; break;
                    case '%': result = (int)a % (int)b; break;
                }
                push(&numStack, result);
            }
            pop(&opStack);  // 弹出 '('
        } else if (isOperator(c)) {
            while (!isEmpty(&opStack) && precedence(peek(&opStack)) >= precedence(c)) {
                double b = pop(&numStack);
                double a = pop(&numStack);
                char op = pop(&opStack);
                double result;
                
                switch (op) {
                    case '+': result = a + b; break;
                    case '-': result = a - b; break;
                    case '*': result = a * b; break;
                    case '/': result = a / b; break;
                    case '%': result = (int)a % (int)b; break;
                }
                push(&numStack, result);
            }
            push(&opStack, c);
        }
    }
    
    while (!isEmpty(&opStack)) {
        double b = pop(&numStack);
        double a = pop(&numStack);
        char op = pop(&opStack);
        double result;
        
        switch (op) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/': result = a / b; break;
            case '%': result = (int)a % (int)b; break;
        }
        push(&numStack, result);
    }
    
    return pop(&numStack);
}

int main() {
    char expr[MAX];
    
    printf("请输入算术表达式：");
    scanf("%s", expr);
    
    double result = evaluateExpression(expr);
    printf("结果：%.2f\n", result);
    
    return 0;
}
