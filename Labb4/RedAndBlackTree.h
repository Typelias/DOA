#pragma once
#include <vector>
#include <queue>
#include <iostream>
namespace search
{

enum Color
{
    RED,
    BLACK
};

template <typename T>
class RedAndBlackTree
{
public:
    RedAndBlackTree() { root = nullptr; }
    void insert(const T &data)
    {
        auto x = search(data);
        if (x != nullptr)
            return;
        std::cout << "Search done\n";
        Node *pt = new Node(data);

        root = BSTInsert(root, pt);

        fixViolation(root, pt);
    }
    void inorder()
    {
        inorderHelper(root);
    }
    void levelOrder()
    {
        levelOrderHelper(root);
    }

    T *search(const T &target)
    {
        Node *curr = root;
        while (curr != nullptr)
        {
            if (curr->data == target)
                return &curr->data;
            if (target < curr->data)
                curr = curr->left;
            else if (target > curr->data)
                curr = curr->right;
        }
        return nullptr;
    }

private:
    struct Node
    {
        T data;
        bool color;
        Node *left, *right, *parent;

        Node(T data)
        {
            this->data = data;
            left = right = parent = nullptr;
        }
    };
    Node *root;
    void rotateLeft(Node *&root, Node *&pt)
    {
        Node *pt_right = pt->right;
        pt->right = pt_right->left;
        if (pt->right != nullptr)
            pt->right->parent = pt;
        pt_right->parent = pt->parent;
        if (pt->parent == nullptr)
            root = pt_right;
        else if (pt == pt->parent->left)
            pt->parent->right = pt_right;
        else
            pt->parent->right = pt_right;
        pt_right->left = pt;
        pt->parent = pt_right;
    }
    void rotateRight(Node *&root, Node *&pt)
    {
        Node *pt_left = pt->left;

        pt->left = pt_left->right;

        if (pt->left != nullptr)
            pt->left->parent = pt;

        pt_left->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_left;

        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;

        else
            pt->parent->right = pt_left;

        pt_left->right = pt;
        pt->parent = pt_left;
    }

    void fixViolation(Node *&root, Node *&pt)
    {
        Node *parent_pt = nullptr;
        Node *grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED))
        {

            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            /*  Case : A 
            Parent of pt is left child of Grand-parent of pt */
            if (parent_pt == grand_parent_pt->left)
            {

                Node *uncle_pt = grand_parent_pt->right;

                /* Case : 1 
               The uncle of pt is also red 
               Only Recoloring required */
                if (uncle_pt != nullptr && uncle_pt->color == RED)
                {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }

                else
                {
                    /* Case : 2 
                   pt is right child of its parent 
                   Left-rotation required */
                    if (pt == parent_pt->right)
                    {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    /* Case : 3 
                   pt is left child of its parent 
                   Right-rotation required */
                    rotateRight(root, grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }

            /* Case : B 
           Parent of pt is right child of Grand-parent of pt */
            else
            {
                Node *uncle_pt = grand_parent_pt->left;

                /*  Case : 1 
                The uncle of pt is also red 
                Only Recoloring required */
                if ((uncle_pt != nullptr) && (uncle_pt->color == RED))
                {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else
                {
                    /* Case : 2 
                   pt is left child of its parent 
                   Right-rotation required */
                    if (pt == parent_pt->left)
                    {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    /* Case : 3 
                   pt is right child of its parent 
                   Left-rotation required */
                    rotateLeft(root, grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }

        root->color = BLACK;
    }

    void inorderHelper(Node *root)
    {
        if (root == nullptr)
            return;
        inorderHelper(root->left);
        std::cout << root->data << " ";
        inorderHelper(root->right);
    }

    Node *BSTInsert(Node *root, Node *pt)
    {
        if (root == nullptr)
            return pt;
        if (pt->data < root->data)
        {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        }
        else if (pt->data > root->data)
        {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }

        return root;
    }

    void levelOrderHelper(Node *root)
    {
        if (root == nullptr)
            return;

        std::queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            Node *temp = q.front();
            std::cout << temp->data << "   ";
            q.pop();
            if (temp->left != nullptr)
                q.push(temp->left);
            if (temp->right != nullptr)
                q.push(temp->right);
        }
    }
};
} // namespace search
