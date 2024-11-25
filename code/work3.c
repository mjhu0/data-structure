// 542313460109    胡华吉
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct TreeNode {
    char value;  // 存储运算符或操作数
    struct TreeNode *left, *right;
} TreeNode;

// 创建新节点
TreeNode* newNode(char value) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

// 运算符优先级
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 中序遍历输出二叉树（打印表达式）
void inorder(TreeNode *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%c ", root->value);
    inorder(root->right);
}

// 后序遍历计算表达式值
double postorder(TreeNode *root) {
    if (root == NULL) return 0;
    
    // 如果是数字，返回值
    if (isdigit(root->value)) return root->value - '0';

    // 计算左右子树的值
    double left = postorder(root->left);
    double right = postorder(root->right);

    // 根据运算符进行计算
    switch (root->value) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
    }
    return 0;
}

// 构建表达式的二叉树（简化示例）
TreeNode* buildExpressionTree(char* expr) {
    // 创建简单的表达式树
    // 示例表达式: (3 + 2) * (5 - 1)
    
    TreeNode* root = newNode('*');
    TreeNode* leftSubtree = newNode('+');
    TreeNode* rightSubtree = newNode('-');
    
    leftSubtree->left = newNode('3');
    leftSubtree->right = newNode('2');
    
    rightSubtree->left = newNode('5');
    rightSubtree->right = newNode('1');
    
    root->left = leftSubtree;
    root->right = rightSubtree;

    return root;
}

int main() {
    char expr[] = "(3+2)*(5-1)";
    TreeNode *root = buildExpressionTree(expr);

    printf("Inorder Traversal (Expression): ");
    inorder(root);
    printf("\n");

    printf("Result: %.2f\n", postorder(root));

    return 0;
}
