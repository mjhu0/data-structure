#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100  // 最大接种者数量
#define NAME_LEN 20  // 姓名最大长度

typedef struct {
    char id[19];           // 身份证号
    char name[NAME_LEN];   // 姓名
    int doses;             // 已接种剂数
    char firstDose[11];    // 第一剂接种时间
    char secondDose[11];   // 第二剂接种时间
} VaccinationInfo;

typedef struct Node {
    VaccinationInfo data;
    struct Node *next;
} HashNode;

// 全局变量
VaccinationInfo list[MAX]; // 顺序表
int count = 0;             // 当前接种者数量
HashNode *hashTable[MAX];  // 哈希表

// 函数声明
void displayAll();
void displayEligible();
void insertInfo();
void deleteByPosition();
void deleteById();
void sortById();
void quickSort(int low, int high);
int binarySearch(char id[]);
void buildHashTable();
HashNode* searchHashTable(char *key, int *conflicts);
void menu();
int hashFunction(char *key);

// 辅助函数声明
int compareDate(const char *date1, const char *date2);

// 主函数
int main() {
    // 初始化
    for (int i = 0; i < MAX; i++) {
        hashTable[i] = NULL;
    }

    menu();
    return 0;
}

// 菜单
void menu() {
    int choice;
    do {
        printf("\n--- 新冠疫苗接种信息管理系统 ---\n");
        printf("1. 显示所有信息\n");
        printf("2. 显示满足接种第二剂的接种者信息\n");
        printf("3. 插入接种者信息\n");
        printf("4. 删除指定位置的接种者\n");
        printf("5. 删除指定身份证号的接种者\n");
        printf("6. 按身份证号排序\n");
        printf("7. 按第一剂接种时间排序 (快速排序)\n");
        printf("8. 根据身份证号查找接种者\n");
        printf("9. 使用哈希表查找接种信息\n");
        printf("0. 退出系统\n");
        printf("请选择操作：");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayAll(); break;
            case 2: displayEligible(); break;
            case 3: insertInfo(); break;
            case 4: deleteByPosition(); break;
            case 5: deleteById(); break;
            case 6: sortById(); break;
            case 7: 
                quickSort(0, count - 1); 
                printf("排序完成，按第一剂接种时间显示信息如下：\n");
                displayAll(); 
                break;
            case 8: {
                char id[19];
                printf("请输入身份证号：");
                scanf("%s", id);
                int index = binarySearch(id);
                if (index != -1) {
                    printf("接种者信息：身份证号:%s 姓名:%s 已接种剂数:%d 第一剂:%s 第二剂:%s\n", 
                           list[index].id, list[index].name, list[index].doses, list[index].firstDose, list[index].secondDose);
                } else {
                    printf("未找到对应接种者。\n");
                }
                break;
            }
           case 9: {
               char key[NAME_LEN];
               printf("请输入姓名或身份证号：");
               scanf("%s", key);
               int conflicts = 0;
               HashNode *node = searchHashTable(key, &conflicts);
               if (node) {
                   printf("接种者信息：身份证号:%s 姓名:%s 冲突次数:%d\n", 
                          node->data.id, node->data.name, conflicts);
               } else {
                   printf("未找到对应接种者。\n");
               }
               break;
           }
            case 0: printf("退出系统。\n"); break;
            default: printf("无效选项，请重新选择。\n");
        }
    } while (choice != 0);
}

// 显示所有接种者信息
void displayAll() {
    if (count == 0) {
        printf("接种信息为空。\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("身份证号:%s 姓名:%s 已接种剂数:%d 第一剂:%s 第二剂:%s\n",
               list[i].id, list[i].name, list[i].doses, list[i].firstDose, list[i].secondDose);
    }
}

// 显示满足接种第二剂的接种者
void displayEligible() {
    printf("功能未完全实现，请自行完善日期比较逻辑。\n");
}

// 插入接种者信息
void insertInfo() {
    if (count >= MAX) {
        printf("接种信息已满。\n");
        return;
    }
    VaccinationInfo info;
    printf("请输入身份证号、姓名、已接种剂数、第一剂时间、第二剂时间：");
    scanf("%s %s %d %s %s", info.id, info.name, &info.doses, info.firstDose, info.secondDose);
    list[count++] = info; // 简单插入到末尾，进一步实现插入到指定位置
}

// 删除指定位置接种者信息
void deleteByPosition() {
    int pos;
    printf("请输入删除位置：");
    scanf("%d", &pos);
    if (pos < 0 || pos >= count) {
        printf("位置无效。\n");
        return;
    }
    for (int i = pos; i < count - 1; i++) {
        list[i] = list[i + 1];
    }
    count--;
    printf("删除成功。\n");
}

// 删除指定身份证号接种者信息
void deleteById() {
    char id[19];
    printf("请输入身份证号：");
    scanf("%s", id);
    int found = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].id, id) == 0) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        printf("未找到对应接种者。\n");
        return;
    }
    for (int i = found; i < count - 1; i++) {
        list[i] = list[i + 1];
    }
    count--;
    printf("删除成功。\n");
}

// 插入排序
void sortById() {
    for (int i = 1; i < count; i++) {
        VaccinationInfo temp = list[i];
        int j = i - 1;
        while (j >= 0 && strcmp(list[j].id, temp.id) > 0) {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = temp;
    }
    printf("排序完成。\n");
}

// 辅助函数：日期比较
int compareDate(const char *date1, const char *date2) {
    return strcmp(date1, date2);
}

// 快速排序
int partition(int low, int high) {
    VaccinationInfo pivot = list[low];
    while (low < high) {
        while (low < high && compareDate(list[high].firstDose, pivot.firstDose) >= 0) high--;
        list[low] = list[high];
        while (low < high && compareDate(list[low].firstDose, pivot.firstDose) <= 0) low++;
        list[high] = list[low];
    }
    list[low] = pivot;
    return low;
}

void quickSort(int low, int high) {
    if (low < high) {
        int pivot = partition(low, high);
        quickSort(low, pivot - 1);
        quickSort(pivot + 1, high);
    }
}

// 二分查找
int binarySearch(char id[]) {
    int low = 0, high = count - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = strcmp(list[mid].id, id);
        if (cmp == 0) return mid;
        else if (cmp < 0) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

HashNode* searchHashTable(char *key, int *conflicts) {
    int index = hashFunction(key);
    *conflicts = 0;
    HashNode *node = hashTable[index];
    while (node) {
        if (strcmp(node->data.id, key) == 0 || strcmp(node->data.name, key) == 0) {
            return node;
        }
        node = node->next;
        (*conflicts)++;
    }
    return NULL;
}
int hashFunction(char *key) {
    return key[0] % MAX;
}