//胡华吉  542313460109
#include <stdio.h>
#include <stdlib.h>

typedef struct HuffmanNode {
    int freq;  // 部门使用外线电话的频率
    int dept;  // 部门编号
    struct HuffmanNode *left, *right;
} HuffmanNode;

// 创建新的哈夫曼节点
HuffmanNode* newHuffmanNode(int freq, int dept) {
    HuffmanNode *node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    node->freq = freq;
    node->dept = dept;
    node->left = node->right = NULL;
    return node;
}

// 合并两个哈夫曼节点
HuffmanNode* mergeHuffmanNodes(HuffmanNode *left, HuffmanNode *right) {
    HuffmanNode *node = newHuffmanNode(left->freq + right->freq, -1);  // -1表示非叶节点
    node->left = left;
    node->right = right;
    return node;
}

// 生成哈夫曼树
HuffmanNode* buildHuffmanTree(int freq[], int n) {
    // 这里使用最小堆或优先队列来构建哈夫曼树
    // 暂时用贪心算法合并最小频率的节点
    HuffmanNode *nodes[n];
    for (int i = 0; i < n; i++) {
        nodes[i] = newHuffmanNode(freq[i], i);  // 创建每个部门的哈夫曼节点
    }

    while (n > 1) {
        // 找到最小的两个节点
        HuffmanNode *min1 = nodes[0], *min2 = nodes[1];
        for (int i = 2; i < n; i++) {
            if (nodes[i]->freq < min1->freq) {
                min2 = min1;
                min1 = nodes[i];
            } else if (nodes[i]->freq < min2->freq) {
                min2 = nodes[i];
            }
        }

        // 合并最小的两个节点
        HuffmanNode *merged = mergeHuffmanNodes(min1, min2);
        
        // 更新节点列表
        nodes[0] = merged;  // 放入合并后的节点
        n--;  // 频率减少一个
    }
    return nodes[0];  // 返回树的根
}

// 输出哈夫曼编码
void printHuffmanCodes(HuffmanNode *root, char* str, int depth) {
    if (root == NULL) return;

    if (root->left == NULL && root->right == NULL) {
        // 叶节点，输出部门和路径
        printf("Department %d: %s\n", root->dept, str);
    }

    str[depth] = '0';
    printHuffmanCodes(root->left, str, depth + 1);

    str[depth] = '1';
    printHuffmanCodes(root->right, str, depth + 1);
}

int main() {
    int freq[] = {5, 20, 10, 12, 8, 43, 5, 6, 9, 15, 19, 32};
    int n = sizeof(freq) / sizeof(freq[0]);

    HuffmanNode* root = buildHuffmanTree(freq, n);

    char str[100];
    printf("Huffman Codes for Departments:\n");
    printHuffmanCodes(root, str, 0);

    return 0;
}
