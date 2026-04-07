#include <iostream>
#include <string>
#include <list>
#include <queue>

typedef std::string String;

class TreeNode {
public:
    String medicareId;
    int directContacts = 0;
    int totalCases = 1;
    TreeNode* parentPtr = nullptr;
    std::list<TreeNode*> directContactsPtrList;

    TreeNode(const String& medId, TreeNode* parent = nullptr)
        : medicareId(medId), parentPtr(parent) {
        if (parent) {
            parent->directContactsPtrList.push_back(this);
            parent->directContacts++; 
            TreeNode* p = parent;
            while (p) {
                p->totalCases++;
                p = p->parentPtr;
            }
        }
    }
};

class ContactTree {
private:
    TreeNode* root = nullptr;

    void clear(TreeNode* node) {
        for (auto child : node->directContactsPtrList) {    
            clear(child);
        }
        delete node;
    }

    TreeNode* findBFS(const String& medId) {        //search node by the ID using BFS 
        if (!root) return nullptr;  // check if tree is empt
        std::queue<TreeNode*> q;    
        q.push(root);
        while (!q.empty()) { // The loop continues as long as there are nodes left in the queue to process.
            TreeNode* current = q.front();
            q.pop();
            if (current->medicareId == medId) return current; //The Medicare ID of the current node is compared with the medId, if we don t find it the BFS continues
            for (auto child : current->directContactsPtrList) { //all direct children of the current node are added to the queue
                q.push(child);
            }
        }
        return nullptr; //If the queue becomes empty and no node with the specified Medicare ID has been found the method returns nullptr 
    }

public:
    ContactTree() {}

    ContactTree(const String& patientZeroId) {  
        root = new TreeNode(patientZeroId);   //new TreeNode--> patientZeroId and sets new node as the root of the tree.
    }

    ~ContactTree() {
        if (root) clear(root);   //Checks if root is not nullptr
    }

    bool IsEmpty() const { //Cghecks if Tree is empty 
        return root == nullptr;
    }

    int GetSize() const {   
        return root ? root->totalCases : 0; //Returns the total number of nodes in the tree. 
    }

    void AddPatient0(const String& id) {    //Sets or resets the root of the tree to a new Patient Zero.
        if (root) clear(root);
        root = new TreeNode(id);
    }

    void AddContact(const String& parentId, const String& childId) {
        TreeNode* parentNode = findBFS(parentId);   
        if (parentNode) {
            new TreeNode(childId, parentNode); //// Successfully add the child
        }
        else {
            std::cerr << "Parent ID not found\n"; /// Parent node does not exist
        }
    }

    void DeleteContact(const String& medId) {   //remove a specific node identified by the Medicare ID along with all its descendant nodes. 
        TreeNode* node = findBFS(medId);
        if (node && node != root) { // Checks if the node exists and is not the root of the tree
            TreeNode* parent = node->parentPtr; //finds the parent pointer from the node that is going to be deleted
            parent->directContacts--; //Decrements 
            for (auto it = parent->directContactsPtrList.begin(); it != parent->directContactsPtrList.end(); ++it) { //Iterates through the parent's list of child pointers to find and remove the pointer to the node being deleted.
                if (*it == node) {
                    parent->directContactsPtrList.erase(it);
                    break;
                }
            }
            clear(node);
            while (parent) {
                parent->totalCases--; //just makes sure if we delete a node then it deletes in the TotalCases
                parent = parent->parentPtr;
            }
        }
        else if (node == root) {
            clear(root);    //clears whole tree if we delete root 
            root = nullptr;
        }
        else {
            std::cerr << "Contact ID not found\n";
        }
    }

    void DisplayContact(const String& id) {
        TreeNode* node = findBFS(id);
        if (node) {
            std::cout << "Medicare ID: " << node->medicareId << "\n"; //Prints the Medicare ID of the node
            std::cout << "Direct Contacts: " << node->directContacts << "\n";// Displays the number of direct contacts or children that the node has. 
            std::cout << "Total Cases: " << node->totalCases << "\n"; //Shows the total number of cases in the subtree rooted at this node
            std::cout << "Parent: " << (node->parentPtr ? node->parentPtr->medicareId : "None") << "\n"; //Displays the Medicare ID of the node's parent if it exists.
        }
        else {
            std::cerr << "Contact ID not found\n";
        }
    }

    void TraceSource(const String& id) { //Displays all the nodes from this node till the root
        TreeNode* node = findBFS(id);   
        while (node) { //while continues as long as its not null 
            std::cout << node->medicareId << " -> "; //print node ID 
            node = node->parentPtr; //move to the parent node 
        }
        std::cout << "Root\n";
    }

    void PrintContactCases(const String& id) { //Print direct children contacts, given a contact
        TreeNode* node = findBFS(id);
        if (node) {
            for (auto child : node->directContactsPtrList) { //Loop Through Direct Contacts
                std::cout << child->medicareId << "\n";
            }
        }
        else {
            std::cerr << "Contact ID not found\n";
        }
    }

    void PrintContactTree() { 
        if (!root) return;  // checks if tree is empty
        std::queue<TreeNode*> q; //queu is declared it will manage the nodes during BFS
        q.push(root); //root enqueued, (where the BFS starts)
        while (!q.empty()) { //it will keep going as long as there are nodes left in the queue 
            TreeNode* current = q.front(); //takes the node to be processed from the front and removes it 
            q.pop();
            DisplayContact(current->medicareId); 
            for (auto child : current->directContactsPtrList) {//goes through each child of the list 
                q.push(child);
            }
        }
    }
 };
