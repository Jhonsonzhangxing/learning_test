//二叉树的前序，中序和后序遍历是根据根结点的位置来判断
//前序：根左右
//中序：左根右
//后序：左右根
//叶子结点也需要判断左右节点，只不过左右节点都是空


//非递归前序遍历，根左右
//(1) 从根结点开始，向左遍历压栈并输出
//(2) 一直找到二叉树最左边的结点，将最左侧的叶子结点压入栈
//(3) 出栈，指向该结点的右孩子
//(4) 将右孩子作为根节点重复(1)(2)(3)
void Pretravel(BiNode* root)
{
	if (!root)
	{
		return;
	}

	stack<BiNode*> st;
	BiNode* p = root;

	while (p || !st.empty())
	{
		while (p){
			cout << p->data;
			st.push(p);
			p = p->lchild;
		}
		

		if (!st.empty())
		{
			p = st.top();
			st.pop();
			p = p->rchild;
		}
	}
}

//非递归中序遍历，左根右
//先输出最左侧叶子结点
//(1) 从根结点开始，往左遍历压栈
//(2) 找到最左侧的叶子结点,也将其压栈
//(3) 出栈，输出结点值，并指向该结点的右孩子
//(4) 将右孩子作为根结点继续(1)(2)(3)
void Intravel(BiNode* root){
	if (root == NULL)
		return;
	stack<BiNode*>st;
	BiNode *p = root;

	while (!st.empty() || p){
		while (p){
			st.push(p);
			p = p->lchild;
		}

		if (!st.empty()){
			p = st.top();
			st.pop();
			cout << p->data;
			p = p->rchild;
		}
	}
}

//非递归后序遍历，左右根
// 维护一个pre结点
//(1) 从根结点开始，往左遍历压栈
//(2) 找到最左侧的叶子结点,也将其压栈
//(3) 出栈，判断当前的结点是不是叶子结点或是不是根结点(上一次访问的是右孩子)
//(4) 若是，输出结点值，更新pre指针
//(5) 若不是，指向右孩子，重复(1)(2)(3)(4)
void behtravel(BiNode* root){
	if (NULL == root)
		return;
	stack<BiNode *> st;
	BiNode * p = root;
	BiNode * pre = NULL;
	while (!st.empty || p){
		while (p){
			st.push(p);
			p = p->lchild;
		}
		if (!st.empty()){
			p = st.top();
			st.pop();

			//右孩子为空(左叶子结点和右叶子结点) 或 刚刚访问的是该结点的右孩子(根结点)
			if (!p->rchild || pre == p->rchild){
				cout << p->data;
				pre = p;
			}
			//右孩子不为空，则将刚刚出栈的结点重新压入，指向结点的右孩子
			else{
				st.push(p);
				p = p->rchild;
			}
		}
	}
}

#include <iostream>
#include <stack>

struct Node {
	int value;
	Node* left;
	Node* right;
	Node(int value) :
		value(value), left(nullptr), right(nullptr) {}
};

void preOrderRecur(Node* head) {
	if (head == nullptr) {
		return;
	}
	std::cout << head->value << ",";
	preOrderRecur(head->left);
	preOrderRecur(head->right);
}

void inOrderRecur(Node* head) {
	if (head == nullptr) {
		return;
	}
	inOrderRecur(head->left);
	std::cout << head->value << ",";
	inOrderRecur(head->right);
}

void posOrderRecur(Node* head) {
	if (head == nullptr) {
		return;
	}
	posOrderRecur(head->left);
	posOrderRecur(head->right);
	std::cout << head->value << ",";
}

void preOrderUnRecur(Node* head) {
	if (head == nullptr) {
		return;
	}
	std::stack<Node*> nstack;
	nstack.push(head);
	while (!nstack.empty()) {
		Node* head = nstack.top();  // get stack top
		std::cout << head->value << ",";
		nstack.pop();
		if (head->right != nullptr) {
			nstack.push(head->right);
		}
		if (head->left != nullptr) {
			nstack.push(head->left);
		}
	}
}

void inOrderUnRecur(Node* head) {
	if (head == nullptr) {
		return;
	}
	std::stack<Node*> nstack;
	while (!nstack.empty() || head != nullptr) {
		if (head != nullptr) {
			nstack.push(head);
			head = head->left;
		}
		else {
			head = nstack.top();
			std::cout << head->value << ",";
			nstack.pop();
			head = head->right;
		}
	}
}

void posOrderUnRecur(Node* head) {
	if (head == nullptr) {
		return;
	}
	std::stack<Node*> nstack1, nstack2;
	nstack1.push(head);
	while (!nstack1.empty()) {
		Node* head = nstack1.top();
		nstack2.push(head);
		nstack1.pop();
		if (head->left != nullptr) {
			nstack1.push(head->left);
		}
		if (head->right != nullptr) {
			nstack1.push(head->right);
		}
	}

	while (!nstack2.empty()) {
		std::cout << nstack2.top()->value << ",";
		nstack2.pop();
	}
}
int main() {
	Node* head = new Node(5);
	head->left = new Node(3);
	head->right = new Node(8);
	head->left->left = new Node(2);
	head->left->right = new Node(4);
	head->right->left = new Node(7);
	head->right->right = new Node(10);
	head->right->left->left = new Node(6);
	head->right->right->left = new Node(9);
	head->right->right->right = new Node(11);

	std::cout << "==============recursive==============";
	std::cout << "\npre-order: ";
	preOrderRecur(head);
	std::cout << "\nin-order: ";
	inOrderRecur(head);
	std::cout << "\npos-order: ";
	posOrderRecur(head);
	std::cout << "\n==============un-recursive==============";
	std::cout << "\npre-order: ";
	preOrderUnRecur(head);
	std::cout << "\nin-order: ";
	inOrderUnRecur(head);
	std::cout << "\npos-order: ";
	posOrderUnRecur(head);
	return 0;
}