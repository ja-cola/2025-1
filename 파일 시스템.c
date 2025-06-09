#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_NAME 50

typedef struct {
    char name[MAX_NAME];
    int size;
} File;

typedef struct {
    char name[MAX_NAME];
    File files[MAX_FILES];
    int file_count;
} Directory;

void create_file(Directory *dir, char *name, int size) {
    if (dir->file_count < MAX_FILES) {
        strcpy(dir->files[dir->file_count].name, name);
        dir->files[dir->file_count].size = size;
        dir->file_count++;
        printf("파일 %s가 생성되었습니다.\n", name);
    } else {
        printf("디렉토리에 파일을 더 이상 추가할 수 없습니다.\n");
    }
}

void list_files(Directory *dir) {
    printf("디렉토리: %s\n", dir->name);
    for (int i = 0; i < dir->file_count; i++) {
        printf("파일 이름: %s, 크기: %d KB\n", dir->files[i].name, dir->files[i].size);
    }
}

int main() {
    Directory dir = {"Documents", {}, 0};
    
    create_file(&dir, "file1.txt", 20);
    create_file(&dir, "file2.txt", 30);
    list_files(&dir);

    return 0;
}
