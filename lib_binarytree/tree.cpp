#include "../lib_binarytree/tree.h"

int main() {
    BinaryTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);

    cout << "Tree by levels:" << endl;
    tree.printTreeByLevels(tree.getRoot());

    cout << "InOrder DFS:" << endl;
    tree.dfsInOrder(printNode);
    cout << endl;

    cout << "PreOrder DFS:" << endl;
    tree.dfsPreOrder(printNode);
    cout << endl;

    cout << "PostOrder DFS:" << endl;
    tree.dfsPostOrder(printNode);
    cout << endl;

    cout << "Tree size: " << tree.size() << endl;
    cout << "Tree height: " << tree.height() << endl;

    Node* node = tree.find(3);
    if (node) {
        cout << "Node 3 found at level: " << tree.getLevel(node) << endl;
    }
    else {
        cout << "Node 3 not found" << endl;
    }

    tree.remove(node);
    cout << "Tree after removing node 3:" << endl;
    tree.printTreeByLevels(tree.getRoot());

    return 0;
}