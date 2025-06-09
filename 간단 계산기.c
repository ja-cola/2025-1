#include <stdio.h>

void add(double a, double b) {
    printf("덧셈 결과: %.2f\n", a + b);
}

void subtract(double a, double b) {
    printf("뺄셈 결과: %.2f\n", a - b);
}

void multiply(double a, double b) {
    printf("곱셈 결과: %.2f\n", a * b);
}

void divide(double a, double b) {
    if (b != 0) {
        printf("나눗셈 결과: %.2f\n", a / b);
    } else {
        printf("0으로 나눌 수 없습니다.\n");
    }
}

int main() {
    double num1, num2;
    char operator;

    printf("첫 번째 숫자를 입력하세요: ");
    scanf("%lf", &num1);
    printf("두 번째 숫자를 입력하세요: ");
    scanf("%lf", &num2);
    printf("연산자를 입력하세요 (+, -, *, /): ");
    scanf(" %c", &operator);

    switch (operator) {
        case '+':
            add(num1, num2);
            break;
        case '-':
            subtract(num1, num2);
            break;
        case '*':
            multiply(num1, num2);
            break;
        case '/':
            divide(num1, num2);
            break;
        default:
            printf("잘못된 연산자입니다.\n");
            break;
    }

    return 0;
}
