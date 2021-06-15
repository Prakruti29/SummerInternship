#include <iostream>

using namespace std;

struct NodePtr {
	int data;
	NodePtr* parent;
	NodePtr* left;
	NodePtr* right;
	int color;
};

typedef NodePtr* rbNode;

class RBTree {
private:
	rbNode root;
	rbNode RBT;

	void initial(rbNode node, rbNode parent) {
		node->data = 0;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = 0;
	}

	rbNode SearchTree(rbNode node, int val) {
		int found = 0;
		while (node != NULL && found == 0)
		{
			if (val == node->data) {
				found = 1;
				return node;
			}
			if (found == 0)
			{
				if (val < node->data)
					node = node->left;
				else
					node = node->right;
			}

		}
		return NULL;
	}

	void RBDelete(rbNode x) {
		rbNode s;
		while (x != root && x->color == 0) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == 1) {
					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == 0 && s->right->color == 0) {
					s->color = 1;
					x = x->parent;
				}
				else {
					if (s->right->color == 0) {
						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
					}

					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			}
			else {
				s = x->parent->left;
				if (s->color == 1) {
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == 0 && s->right->color == 0) {
					s->color = 1;
					x = x->parent;
				}
				else {
					if (s->left->color == 0) {
						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->left;
					}

					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}


	void RbTrans(rbNode m, rbNode n) {
		if (m->parent == nullptr)
			root = n;
		else if (m == m->parent->left)
			m->parent->left = n;
		else
			m->parent->right = n;

		n->parent = m->parent;
	}

	void deleteNode(rbNode node, int val) {
		rbNode z = RBT;
		rbNode x, y;
		while (node != RBT) {
			if (node->data == val) {
				z = node;
			}

			if (node->data <= val) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}

		if (z == RBT) {
			cout << "Value is not present in the tree.." << endl;
			return;
		}

		y = z;
		int y_color = y->color;
		if (z->left == RBT) {
			x = z->right;
			RbTrans(z, z->right);
		}
		else if (z->right == RBT) {
			x = z->left;
			RbTrans(z, z->left);
		}
		else {
			y = minimum(z->right);
			y_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			}
			else {
				RbTrans(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			RbTrans(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_color == 0)
			RBDelete(x);

	}

	void RBInsert(rbNode k) {
		rbNode u;
		while (k->parent->color == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left;
				if (u->color == 1) {
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->left) {
						k = k->parent;
						rightRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			}
			else {
				u = k->parent->parent->right;

				if (u->color == 1) {
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->right) {
						k = k->parent;
						leftRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = 0;
	}

	void inOrder(rbNode node) {
		if (node != RBT) {
			inOrder(node->left);
			cout << node->data << " ";
			inOrder(node->right);
		}
	}

	void preOrder(rbNode node) {
		if (node != RBT) {
			cout << node->data << " ";
			preOrder(node->left);
			preOrder(node->right);
		}
	}

	void postOrder(rbNode node) {
		if (node != RBT) {
			postOrder(node->left);
			postOrder(node->right);
			cout << node->data << " ";
		}
	}

public:
	RBTree() {
		RBT = new NodePtr;
		RBT->color = 0;
		RBT->left = nullptr;
		RBT->right = nullptr;
		root = RBT;
	}

	void inorder() {
		inOrder(this->root);
	}

	void preorder() {
		preOrder(this->root);
	}

	void postorder() {
		postOrder(this->root);
	}

	rbNode searchNode(int val) {
		return SearchTree(this->root, val);
	}

	rbNode minimum(rbNode node) {
		while (node->left != RBT) {
			node = node->left;
		}
		return node;
	}

	void leftRotate(rbNode x) {
		rbNode y = x->right;
		x->right = y->left;

		if (y->left != RBT)
			y->left->parent = x;

		y->parent = x->parent;

		if (x->parent == nullptr)
			this->root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;

		y->left = x;
		x->parent = y;
	}

	void rightRotate(rbNode x) {
		rbNode y = x->left;
		x->left = y->right;

		if (y->right != RBT)
			y->right->parent = x;

		y->parent = x->parent;

		if (x->parent == nullptr)
			this->root = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;

		y->right = x;
		x->parent = y;
	}

	void insert(int val) {
		rbNode node = new NodePtr;
		node->parent = nullptr;
		node->data = val;
		node->left = RBT;
		node->right = RBT;
		node->color = 1;

		rbNode y = nullptr;
		rbNode x = this->root;

		while (x != RBT) {
			y = x;
			if (node->data < x->data)
				x = x->left;
			else
				x = x->right;
		}

		node->parent = y;
		if (y == nullptr)
			root = node;
		else if (node->data < y->data)
			y->left = node;
		else
			y->right = node;

		if (node->parent == nullptr) {
			node->color = 0;
			return;
		}

		if (node->parent->parent == nullptr)
			return;

		RBInsert(node);
	}

	rbNode getRoot() {
		return this->root;
	}

	void deleteNode(int data) {
		deleteNode(this->root, data);
	}

};

int main() {
	RBTree bst;

	bst.insert(11);
	bst.insert(7);
	bst.insert(22);
	bst.insert(6);
	bst.insert(45);
	bst.insert(78);
	bst.insert(12);
	cout << "Tree:\n";
	bst.inorder();
	cout << "\n";
	bst.deleteNode(45);
	cout << "Tree after deletion\n";
	bst.inorder();
	
	cout << "\n";
	auto val = bst.searchNode(11);
	if (val != NULL) {
		cout << "Search value :: " << val->data << " is found" << endl;
	}
	else {
		cout << "Search value is not found" << endl;
	}
	return 0;
}