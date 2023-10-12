//
//  Tree.hpp
//  Practice
//
//  Created by iSteven on 2023/10/10.
//

#ifndef Tree_hpp
#define Tree_hpp

#include <stdio.h>
#include <vector>

struct TreeNode {
    TreeNode(int v) : val(v) {
        left = nullptr;
        right = nullptr;
    }
    
    ~TreeNode() {
        left = nullptr;
        right = nullptr;
    }
    
    int val;
    TreeNode *left;
    TreeNode *right;
};


using namespace std;

// leetcode#102 二叉树的层序遍历  (队列)
vector<vector<int>> levelOrder(TreeNode* root);

// leetcode#103 二叉树的锯齿形层序遍历
vector<vector<int>> zigzagLevelOrder(TreeNode* root);

// easy leetcode#110 平衡二叉树
bool isBalanced(TreeNode* root);

// leetcode#129 求根节点到叶节点数字之和
int sumNumbers(TreeNode* root);

// easy leetcode#226 翻转二叉树
TreeNode* invertTree(TreeNode* root);

// easy leetcode#104 二叉树的最大深度


#endif /* Tree_hpp */
