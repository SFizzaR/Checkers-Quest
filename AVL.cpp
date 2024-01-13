#include "AVL.hpp"
#include <iostream>
#include <sstream>

AVLNode::AVLNode(int s, const std::string& name)
    : score(s), playerName(name), left(nullptr), right(nullptr), height(1) {}

AVLTree::AVLTree() : root(nullptr) {}

int AVLTree::height(AVLNode* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int AVLTree::balanceFactor(AVLNode* node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode* AVLTree::insert(AVLNode* node, int score, const std::string& playerName) {
    if (node == nullptr)
        return new AVLNode(score, playerName);

    if (score < node->score)
        node->left = insert(node->left, score, playerName);
    else if (score > node->score)
        node->right = insert(node->right, score, playerName);
    else
        return node;

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    if (balance > 1 && score < node->left->score)
        return rightRotate(node);

    if (balance < -1 && score > node->right->score)
        return leftRotate(node);

    if (balance > 1 && score > node->left->score) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && score < node->right->score) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Check if the tree has more than 5 nodes
    if (node->left != nullptr && node->right != nullptr) {
        if (height(node) > 5) {
            // Find the player with the lowest score
            AVLNode* minNode = findMinScoreNode(node->right);
            // Compare the scores and replace if necessary
            if (score > minNode->score) {
                node->right = deleteMinScoreNode(node->right);
                node = insert(node, score, playerName);
            }
        }
    }

    return node;
}

void AVLTree::AddScore(int score, const std::string& playerName) {
    root = insert(root, score, playerName);
}

AVLNode* AVLTree::findMinScoreNode(AVLNode* node) {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

AVLNode* AVLTree::deleteMinScoreNode(AVLNode* node) {
    if (node->left == nullptr)
        return node->right;
    node->left = deleteMinScoreNode(node->left);
    return balanceNode(node);
}

AVLNode* AVLTree::balanceNode(AVLNode* node) {
    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    if (balance > 1 && balanceFactor(node->left) >= 0)
        return rightRotate(node);

    if (balance > 1 && balanceFactor(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && balanceFactor(node->right) <= 0)
        return leftRotate(node);

    if (balance < -1 && balanceFactor(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}
void AVLTree::populateFromData(const std::string& data) {
    // Clear existing tree
    root = nullptr;

    std::istringstream stream(data);
    std::string line;
    while (std::getline(stream, line)) {
        std::istringstream lineStream(line);
        int score;
        std::string playerName;

        // Assuming the format is "score playerName"
        if (lineStream >> score >> playerName) {
            root = insert(root, score, playerName);
        }
    }
}

void AVLTree::inOrderTraversal(AVLNode* node, std::vector<AVLNode*>& sortedData) const {
    if (node != nullptr) {
        inOrderTraversal(node->right, sortedData);
        sortedData.push_back(node);
        inOrderTraversal(node->left, sortedData);
    }
}

std::vector<AVLNode*> AVLTree::getSortedData() {
    std::vector<AVLNode*> sortedData;
    inOrderTraversal(root, sortedData);
    return sortedData;
}

AVLNode* AVLTree::getRoot() {
    return root;
}

void AVLTree::displayLeaderboard() {
    std::vector<AVLNode*> sortedData = getSortedData();

    std::cout << "Leaderboard:" << std::endl;
    for (const auto& node : sortedData) {
        std::cout << node->playerName << ": " << node->score << std::endl;
    }
}

