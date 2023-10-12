//
//  Tree.cpp
//  Practice
//
//  Created by iSteven on 2023/10/10.
//

#include "Tree.hpp"
#include <queue>
#include <deque>

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> ans;
    if (root == nullptr) {
        return ans;
    }
    queue<TreeNode*> q;
    // 根节点入队列
    q.push(root);
    while(!q.empty()) {
        // 遍历当前层节点，并添加到列表
        int size = (int)q.size();
        vector<int> vec;
        while (size > 0) {
            TreeNode *node = q.front();
            q.pop();
            vec.push_back(node->val);
            
            // 将当前层节点的每个字节点入队列（遍历完当前层，那么下一层所有节点都入队列了）
            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
            // 保证遍历完成
            size--;
        }
        ans.push_back(vec);
    }
    return ans;
}

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> ans;
    if (root == nullptr) {
        return ans;
    }
    queue<TreeNode*> q;
    q.push(root);
    bool from_left = true;
    while(!q.empty()) {
        int size = (int)q.size();
        deque<int> list;
        while (size > 0) {
            TreeNode *node = q.front();
            q.pop();
            if (from_left) {
                list.push_back(node->val);
            } else {
                list.push_front(node->val);
            }
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
            size--;
        }
        ans.push_back(vector<int>{list.begin(), list.end()});
        from_left = !from_left;
    }
    return ans;
}

int depthOfTree(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    return max(depthOfTree(root->left), depthOfTree(root->right)) + 1;
}

bool isBalanced(TreeNode* root) {
    if(root == nullptr) {
        return true;
    }
        
    int depthLeft = depthOfTree(root->left);
    int depthRight = depthOfTree(root->right);
    
    return (abs(depthLeft - depthRight) <= 1 && isBalanced(root->left) && isBalanced(root->right));
    
}

int dfs(TreeNode *root, int preSum) {
    if (!root) {
        return 0;
    }
    
    int sum = preSum * 10 + root->val;
    if (root->left == nullptr && root->right == nullptr) {
        return sum;
    }
    return (dfs(root->left, sum) + dfs(root->right, sum));
}

int sumNumbers(TreeNode* root) {
    return dfs(root, 0);
}

TreeNode* invertTree(TreeNode* root) {
    
    if (root == nullptr) {
        return root;
    }
    
    TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    invertTree(root->left);
    invertTree(root->right);
    
    return root;
}

int maxDepth(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    } else {
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
}


#pragma mark - helper
