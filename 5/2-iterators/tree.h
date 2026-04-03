#pragma once
#include <memory>
#include <initializer_list>
#include <queue>

namespace example {
template <typename T>
struct Node {
    T data;
    std::weak_ptr<Node> parent;
    std::shared_ptr<Node> left, right;
};

template <typename T>
class Iterator {
public:
    explicit Iterator(Node<T>* node) : node(node) {
    }
    bool operator==(const Iterator&) const = default;
    T& operator*() {
        return node->data;
    }

    Iterator& operator++() {
        if (!node)
            return *this;
        if (node->right) {
            node = (node->right).get();
            while (node->left)
                node = (node->left).get();
            return *this;
        }
        auto parent = node->parent.lock();
        while (parent && parent->right.get() == node) {
            node = parent.get();
            parent = node->parent.lock();
        }
        node = parent.get();
        return *this;
    }

private:
    Node<T>* node;
};

template <typename T>
class BinaryTree {
public:
    BinaryTree(std::initializer_list<T> elems) {
        auto i = elems.begin();
        if (i == elems.end())
            return;

        root = std::make_shared<Node<T>>(*i);
        std::queue<std::shared_ptr<Node<T>>> q;
        q.push(root);

        while (++i < elems.end()) {
            auto curr = q.front();
            q.pop();

            curr->left = std::make_shared<Node<T>>(*i, curr);
            q.push(curr->left);

            if (++i != elems.end()) {
                curr->right = std::make_shared<Node<T>>(*i, curr);
                q.push(curr->right);
            }
        }
    }

    Iterator<T> begin() {
        auto ptr = root.get();
        while (ptr->left)
            ptr = (ptr->left).get();
        return Iterator<T>(ptr);
    }

    Iterator<T> end() {
        return Iterator<T>{nullptr};
    }

private:
    std::shared_ptr<Node<T>> root;
};
}  // namespace example
