#include <iostream>
#include<vector>
#include<string>
#include<cmath>
using namespace std;

struct Info
{
    //int id;
    string name;
    long no;
};
struct Node
{
    Info info;
    struct Node* next;

};

struct TKey
{
    string key;
    Node* record;
};
struct Tnode
{
    TKey info;

    Tnode* left;
    Tnode* right;
};
Node* insertNode(string n, const long& no)
{
    Node* obj = new Node();
    // obj->info.name = new char[n.length() + 1];
    obj->info.name = n;
    obj->info.no = no;
    obj->next = nullptr;
    return obj;
    // dir.push_back(make_pair(name, no)
}
Tnode* CreateTnode(Node* obj)
{
    Tnode* tnode = new Tnode();
    tnode->info.key = obj->info.name;
    tnode->info.record = obj;
    tnode->left = nullptr;
    tnode->right = nullptr;
    return tnode;
}
void InsertTnode(Tnode* pTree, Tnode* newNode)
{
    Tnode* curr = pTree;
    if (curr != nullptr)
    {
        if ((newNode->info.key < (curr->info.key)))
        {
            if (curr->left == nullptr)
                curr->left = newNode;
            else
            {
                InsertTnode(curr->left, newNode);
            }
        }
        else {
            if (curr->right == nullptr)
            {
                curr->right = newNode;
            }
            else
            {
                InsertTnode(curr->right, newNode);
            }
        }

    }
}
Tnode* BuildNameTree(Node* head)
{
    Tnode* pTree = nullptr;
    Node* temp = head;
    while (temp != nullptr)
    {
        Tnode* newNode = CreateTnode(temp);
        if (pTree == nullptr)
            pTree = newNode;
        else
        {
            InsertTnode(pTree, newNode);
        }
        temp = temp->next;

    }
    return pTree;
}
int printContactList(Tnode* node)
{
    if (node == nullptr)
        return 0;
    cout << node->info.key << " \t\t\t" << node->info.record->info.no << endl;
    printContactList(node->left);
    printContactList(node->right);
}
void printList(Node* node)
{
    auto temp = node;
    while (temp != nullptr)
    {
        cout << temp->info.name << " " << temp->info.no << endl;
        temp = temp->next;
    }
}
Tnode* searchByName(string name, Tnode* root)
{
    Tnode* curr = root;
    if (curr != nullptr)
    {
        if ((curr->info.key.compare(name)) < 0)
        {
            if ((curr->info.key.compare(name)) == 0)
            {
                return curr;
            }
            else if (curr->left == nullptr)
                //curr->left = newNode;
                return nullptr;
            else
            {
                searchByName(name, curr->left);
            }
        }
        else {
            if ((curr->info.key.compare(name)) == 0)
            {
                return curr;
            }
            else if (curr->right == nullptr)
            {
                return nullptr;
            }
            else
            {
                searchByName(name, curr->right);
            }
        }
    }

}
void sortContacts(Tnode* root)
{
    if (root == nullptr)
        return;
    printContactList(root->left);
    cout << root->info.key << " \t\t\t" << root->info.record->info.no << endl;
    printContactList(root->right);
}
Tnode* minNode(Tnode* node)
{
    Tnode* current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}
Tnode* deleteContact(string name, Tnode* root)
{
    Tnode* found = searchByName(name, root);
    if (found == nullptr)
        return NULL;
    else
    {
        if (found->right == nullptr && found->left == nullptr)
        {
            delete(found);
            return NULL;
        }
        else if (found->right == nullptr)
        {
            Tnode* temp = found->left;
            free(found);
            return temp;
        }
        else if (found->left == nullptr)
        {
            Tnode* temp = found->right;
            free(found);
            return temp;
        }
        Tnode *temp = minNode(found->right);
        found->info.key = found->info.key;
        string t = found->info.key;
        found->right = deleteContact(t, found->right); 
    }
    return found;
}

int main()
{
    
    int value;
    long no;
    Node* pHead = nullptr;
    Node* pLast = nullptr;
    Tnode* pTree = nullptr;
    string name;

    do
    {
        cout << "1 for Adding contact" << endl;
        cout << "2 for View Contacts" << endl;
        cout << "3 for Search by Name" << endl;
        cout << "4 for Sort" << endl;
        cout << "5 for Deleting Contact" << endl;
        cout << "6 for exit" << endl;
        cout << "Enter choice" << endl;
        cin >> value;
        if (value == 1)
        {
            cout << "Enter name:";
            cin >> name;
            cout << "Enter mobile number:";
            cin >> no;
            Node* obj = new Node();
            obj = insertNode(name, no);
            if (pHead == nullptr)
            {
                pHead = obj;
            }
            if (pLast != nullptr)
            {
                pLast->next = obj;
            }
            pLast = obj;
            pTree = BuildNameTree(pHead);

        }
        if (value == 2)
        {
            cout << "Contacts List::" << endl;;
            cout << "Name----------------------Contact Number" << endl;
            printContactList(pTree);
        }
        if (value == 3)
        {
            string s;
            cout << "Enter name:" << endl;
            cin >> s;
            Tnode* tnode = searchByName(s, pTree);
            if (tnode == nullptr)
            {
                cout << "Contact Number not found" << endl;
            }
            else
            {
                cout << "Contact Number of " << s << " is " << tnode->info.record->info.no << endl;
            }
        }
        if (value == 4)
        {
            sortContacts(pTree);
        }
        if (value == 5)
        {
            string s;
            if (pTree == nullptr)
            {
                cout << "No Contacts" << endl;
            }
            else
            {
                cout << "Enter name of person whose contact you want to delete?" << endl;
                cin >> s;
                pTree = deleteContact(s, pTree);
                printContactList(pTree);
            }
        }
    } while (value != 6);
}