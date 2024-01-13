#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <vector>
#include <string>

struct AVLNode {
    int score;
    std::string playerName;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int s, const std::string& name);
};

class AVLTree {
private:
    AVLNode* root;
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* findMinScoreNode(AVLNode* node);
    AVLNode* deleteMinScoreNode(AVLNode* node);
    AVLNode* insert(AVLNode* node, int score, const std::string& playerName);
    AVLNode* balanceNode(AVLNode* node);
    std::string inorderTraversal();
   

public:
    AVLTree();
    void AddScore(int score, const std::string& playerName);
    std::vector<AVLNode*> getSortedData();
    AVLNode* getRoot();
    void displayLeaderboard();
    void inOrderTraversal(AVLNode* node, std::vector<AVLNode*>& sortedData) const;
    std::string inorderTraversal () const;
    void populateFromData(const std::string& data);
};

#endif

