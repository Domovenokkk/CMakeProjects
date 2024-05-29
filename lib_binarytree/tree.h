// Copyright 2024 Mezhuev Maksim


#include <iostream>
#include <algorithm>
#include <vector>
#include "../lib_queue/queue.h"
#include "../lib_stack/stack.h"

using std::max;
using std::cout;
using std::endl;

struct Node {
    int data;
    Node* left;
    Node* right;
    explicit Node(int value) : data(value), left(nullptr), right(nullptr) {}
};


Node* create(int value, Node* l = nullptr, Node* r = nullptr) {
    Node* node = new Node(value);
    node->left = l;
    node->right = r;
    return node;
}

class BinaryTree {
    Node* root;

public:
    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        Node* newNode = new Node(value);
        if (!root) {
            root = newNode;
            return;
        }

        TQueue<Node*> q;  
        q.push(root);

        while (!q.isEmpty()) {
            Node* current = q.front();
            q.pop();

            // Проверяем, есть ли у текущего узла левый потомок. Если нет,
            // новый узел становится его левым потомком, и функция завершает работу
            if (!current->left) {
                current->left = newNode;
                return;
            }
            else {
                q.push(current->left);
            }

            if (!current->right) {
                current->right = newNode;
                return;
            }
            else {
                q.push(current->right);
            }
        }
    }

    // Метод для поиска узла с заданным значением
    Node* find(int value) {
        if (!root) return nullptr;

        TQueue<Node*> q;
        q.push(root);

        while (!q.isEmpty()) {
            Node* current = q.front();
            q.pop();
            if (current->data == value) return current;
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        return nullptr;
    }

    // Метод для удаления узла
    // Метод для удаления узла
    void remove(Node* node) {
        // Если дерево пусто или удаляемый узел равен nullptr, просто возвращаемся.
        if (!root || !node) return;

        // Специальный случай: если дерево состоит из одного узла, и это корневой узел,
        // то удаляем корень и устанавливаем root в nullptr.
        if (root == node && !root->left && !root->right) {
            delete root;
            root = nullptr;
            return;
        }

        // Используем BFS для нахождения самого правого узла и его родителя
        TQueue<Node*> q;
        q.push(root);
        Node* rightmost = nullptr;         // Указатель на самый правый узел
        Node* rightmostParent = nullptr;   // Указатель на родителя самого правого узла
        Node* targetParent = nullptr;      // Указатель на родителя удаляемого узла

        while (!q.isEmpty()) {
            Node* current = q.front();
            q.pop();

            // Проверяем левый потомок текущего узла
            if (current->left) {
                rightmostParent = current;  // Родитель текущего левого потомка становится текущим узлом
                q.push(current->left);
            }

            // Проверяем правый потомок текущего узла
            if (current->right) {
                rightmostParent = current;  // Родитель текущего правого потомка становится текущим узлом
                q.push(current->right);
            }

            // Определяем родителя узла, который нужно удалить
            if (current->left && current->left == node) {
                targetParent = current;
            }
            else if (current->right && current->right == node) {
                targetParent = current;
            }

            // Обновляем указатель на самый правый узел
            rightmost = current;
        }

        // Заменяем данные удаляемого узла данными самого правого узла
        if (rightmost != node) {
            node->data = rightmost->data;
        }

        // Удаляем самый правый узел
        if (rightmostParent) {
            if (rightmostParent->right == rightmost) {
                rightmostParent->right = nullptr;
            }
            else {
                rightmostParent->left = nullptr;
            }
        }

        // Освобождаем память, занятую самым правым узлом
        delete rightmost;
    }

    // Метод для получения корня дерева
    Node* getRoot() const {
        return root;
    }


    void printTreeByLevels(Node* root) {
        if (!root) return;

        TQueue<Node*> q;
        q.push(root);

        while (!q.isEmpty()) {
            int levelSize = q.getSize();  // Количество узлов на текущем уровне
            std::vector<int> levelNodes;

            // Обрабатываем все узлы на текущем уровне
            for (int i = 0; i < levelSize; ++i) {
                Node* currentNode = q.front();
                q.pop();
                levelNodes.push_back(currentNode->data);


                if (currentNode->left) {
                    q.push(currentNode->left);
                }
                if (currentNode->right) {
                    q.push(currentNode->right);
                }
            }

            // Печатаем узлы на текущем уровне
            for (int val : levelNodes) {
                cout << val << " ";
            }
            cout << endl;
        }
    }

public:
    // Метод для обхода в ширину
    void BFS(void (*func)(Node*)) {
        if (root == nullptr) return;
        TQueue<Node*> q;
        q.push(root);  // Первый элемент
        while (!q.isEmpty()) {
            Node* cur = q.front();
            q.pop();
            if (cur) {
                if (cur->left != nullptr) { q.push(cur->left); }
                if (cur->right != nullptr) { q.push(cur->right); }
                func(cur);
            }
        }
    }

    // Методы для обхода в глубину
    void dfsInOrder(void (*func)(Node*)) {
        dfsInOrderRec(root, func);
    }

    void dfsPreOrder(void (*func)(Node*)) {
        dfsPreOrderRec(root, func);
    }

    void dfsPostOrder(void (*func)(Node*)) {
        dfsPostOrderRec(root, func);
    }


    int height() {
        return heightRec(root);
    }


    int getLevel(Node* node) {
        return getLevelRec(root, node, 1);
    }


    int size() {
        return sizeRec(root);
    }

private:
    //функции для обхода в глубину
    void dfsInOrderRec(Node* node, void (*func)(Node*)) {
        if (node == nullptr) return;
        dfsInOrderRec(node->left, func);
        func(node);
        dfsInOrderRec(node->right, func);
    }

    void dfsPreOrderRec(Node* node, void (*func)(Node*)) {
        if (node == nullptr) return;
        func(node);
        dfsPreOrderRec(node->left, func);
        dfsPreOrderRec(node->right, func);
    }

    void dfsPostOrderRec(Node* node, void (*func)(Node*)) {
        if (node == nullptr) return;
        dfsPostOrderRec(node->left, func);
        dfsPostOrderRec(node->right, func);
        func(node);
    }


    int heightRec(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = heightRec(node->left);
        int rightHeight = heightRec(node->right);
        return max(leftHeight, rightHeight) + 1;
    }


    int getLevelRec(Node* current, Node* target, int level) {
        if (current == nullptr) {
            return 0;
        }
        if (current == target) {
            return level;
        }
        int downLevel = getLevelRec(current->left, target, level + 1);
        if (downLevel != 0) {
            return downLevel;
        }
        return getLevelRec(current->right, target, level + 1);
    }


    int sizeRec(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return sizeRec(node->left) + 1 + sizeRec(node->right);
    }
};

//функция для печати узла
void printNode(Node* node) {
    if (node) {
        cout << node->data << " ";
    }
}