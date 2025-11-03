/*****************************************************
 *   inst.data.txt의 명령어 테이블을 읽어
 *   source.asm의 어셈블리 코드를 파싱하여
 *   각 명령어의 OPCODE와 FORMAT을 출력한다.
 *****************************************************/

#define _CRT_SECURE_NO_WARNINGS   // fscanf 등 보안 경고 비활성화
#pragma warning(disable:6011)     // NULL 포인터 분석 경고 비활성화

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 5000
#define MAX_OPERAND 3
#define MAX_INST 256

typedef struct token_unit {
    char* label;
    char* operator;
    char operand[MAX_OPERAND][20];
    char comment[100];
} token;

typedef struct inst_unit {
    char str[10];
    char format[5];
    int type;
    char opcode[5];
} inst;

char* input_data[MAX_LINES];
token* token_table[MAX_LINES];
int line_num = 0;

inst* inst_table[MAX_INST];
int inst_index = 0;

// inst.data.txt 로드
void load_inst_table(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("[오류] inst.data.txt 파일을 열 수 없습니다.\n");
        exit(1);
    }

    while (!feof(fp)) {
        inst* tmp = (inst*)malloc(sizeof(inst));
        if (tmp == NULL) {
            printf("[오류] 메모리 할당 실패!\n");
            exit(1);
        }

        if (fscanf(fp, "%s %s %d %s", tmp->str, tmp->format, &tmp->type, tmp->opcode) == 4) {
            inst_table[inst_index++] = tmp;
        }
    }

    fclose(fp);
    printf("[OK] 명령어 테이블 %d개 로드 완료.\n", inst_index);
}

// source.asm 로드
void load_source_file(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("[오류] source.asm 파일을 열 수 없습니다.\n");
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        input_data[line_num] = _strdup(line); // Visual Studio용
        line_num++;
    }

    fclose(fp);
    printf("[OK] 소스코드 %d라인 로드 완료.\n", line_num);
}

// 토큰 분리
void parse_tokens() {
    for (int i = 0; i < line_num; i++) {
        char* line = input_data[i];
        if (line == NULL || line[0] == '.') continue; // 주석 및 빈 라인 무시

        token* tk = (token*)malloc(sizeof(token));
        if (tk == NULL) {
            printf("[오류] 메모리 할당 실패!\n");
            exit(1);
        }

        tk->label = NULL;
        tk->operator = NULL;
        memset(tk->operand, 0, sizeof(tk->operand));
        memset(tk->comment, 0, sizeof(tk->comment));

        char* label = strtok(line, " \t\n");
        char* op = strtok(NULL, " \t\n");
        char* operand = strtok(NULL, "\n");

        if (op == NULL) { // label 없는 경우 (RSUB 등)
            tk->operator = label;
        }
        else {
            tk->label = label;
            tk->operator = op;
            if (operand) strcpy_s(tk->operand[0], sizeof(tk->operand[0]), operand);
        }

        token_table[i] = tk;
    }
}

// 명령어 검색
inst* find_inst(const char* mnemonic) {
    for (int i = 0; i < inst_index; i++) {
        if (strcmp(inst_table[i]->str, mnemonic) == 0)
            return inst_table[i];
    }
    return NULL;
}

// 결과 출력
void print_result() {
    printf("\n==== [파싱 결과] ====\n");
    for (int i = 0; i < line_num; i++) {
        if (!token_table[i] || !token_table[i]->operator) continue;

        inst* found = find_inst(token_table[i]->operator);

        if (found) {
            printf("%-8s %-8s %-10s  OPCODE: %-3s  FORMAT: %-3s  TYPE: %d\n",
                token_table[i]->label ? token_table[i]->label : "",
                token_table[i]->operator,
                token_table[i]->operand[0],
                found->opcode,
                found->format,
                found->type);
        }
        else {
            printf("%-8s %-8s %-10s  (비명령어)\n",
                token_table[i]->label ? token_table[i]->label : "",
                token_table[i]->operator,
                token_table[i]->operand[0]);
        }
    }
}

int main() {
    printf("=== SIC 어셈블러 파싱 프로그램 (Visual Studio) ===\n");

    load_inst_table("inst.data.txt");
    load_source_file("source.asm");
    parse_tokens();
    print_result();

    printf("\n[완료] 프로그램 종료.\n");
    system("pause");
    return 0;
}
