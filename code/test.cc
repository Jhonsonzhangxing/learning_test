#include <iostream>
#include <queue>
#include <vector>

template<typename T>
struct Node {
    T data;
    Node* left;
    Node* right;
};

template<typename T>
void parseTree(Node<T>* root) {
    if (root == nullptr) return; 
    std::queue<Node<T>*> q;
    q.emplace(root);
    while(!q.empty()) {
        std::size_t size = q.size();
        std::vector<T> vec;
        for (std::size_t i = 0; i < size; ++i) {
            Node<T>* tmp = q.front();
            q.pop();
            vec.emplace(tmp->data);
            q.emplace(tmp->left);
            q.emplace(tmp->right);
        }
    }
}

template<typename T>
void preparse(Node<T>* root) {
    if (root== nullptr) return ;
    std::cout << root->data << std::endl;
    preparse(root->left);
    preparse(root->right);
}

template<typename T>
void midparse(Node<T>* root) {
    if (root== nullptr) return ;
    preparse(root->left);
    std::cout << root->data << std::endl;
    preparse(root->right);
}

bool ispalindrom(int num) {
    std::string str_num = std::to_string(num);
    std::size_t size = str_num.size();
    std::size_t left = 0;
    std::size_t right = size - 1;
    while(left > right) {
        if(str_num.at(left) != str_num.at(right)) {
            return false;
            break;
        }
        left++;
        right--;
    }
}

template<typename T>
Node<T>* splitlist(Node<T>* head, T data) {
    if(head==nullptr) return;
    Node<T> small;
    Node<T> big;
    Node<T>* small_ptr = &small;
    Node<T>* big_ptr = &big;

    while(head != nullptr) {    
        if(head->data > data) {
            big_ptr->right = head;
            big_ptr = head;
        } else {
            small_ptr->right = head;
            small_ptr = head;
        }
        head = head->right;
    }
    small_ptr->next = &big;
    big_ptr->right = nullptr;
    return small.left;
}




int main() {

    return 0;
}