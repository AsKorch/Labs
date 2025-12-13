#ifndef LAB_4_H
#define LAB_4_H

// Узел дерева
struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Функции работы с деревьями (изменены имена)
struct TreeNode* createTreeNode(int key);
struct TreeNode* insertTreeNode(struct TreeNode* root, int key);
int findTreeMinValue(struct TreeNode* root);
int getTreeHeight(struct TreeNode* root);
int countTreeDescendants(struct TreeNode* root);
int countTreeSpecialNodes(struct TreeNode* root);
void printTree(struct TreeNode* root);
int generateNumbersToFile(void);
struct TreeNode* readNumbersAndBuildTree(void);
struct TreeNode* extendGraphFromMin(struct TreeNode* originalRoot, int targetSum);
int sumTree(struct TreeNode* root);
void deleteTree(struct TreeNode** root);
int run_lab4(void);

#endif /* LAB_4_H */