#include <iostream>
#include <deque>
#include <list>
#include <queue>
#include <string>

typedef std::string String;

// ===================== TreeNode =====================
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

// ===================== ContactTree =====================
class ContactTree {
private:
    TreeNode* root = nullptr;

    void clear(TreeNode* node) {
        for (auto child : node->directContactsPtrList)
            clear(child);
        delete node;
    }

    TreeNode* findBFS(const String& medId) {
        if (!root) return nullptr;
        std::queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            if (current->medicareId == medId) return current;
            for (auto child : current->directContactsPtrList)
                q.push(child);
        }
        return nullptr;
    }

public:
    ContactTree() {}
    ContactTree(const String& patientZeroId) {
        root = new TreeNode(patientZeroId);
    }
    ~ContactTree() {
        if (root) clear(root);
    }

    bool IsEmpty() const { return root == nullptr; }
    int GetSize() const { return root ? root->totalCases : 0; }

    void AddPatient0(const String& id) {
        if (root) clear(root);
        root = new TreeNode(id);
    }

    void AddContact(const String& parentId, const String& childId) {
        TreeNode* parentNode = findBFS(parentId);
        if (parentNode)
            new TreeNode(childId, parentNode);
        else
            std::cerr << "Parent ID not found\n";
    }

    void DeleteContact(const String& medId) {
        TreeNode* node = findBFS(medId);
        if (node && node != root) {
            TreeNode* parent = node->parentPtr;
            parent->directContacts--;
            for (auto it = parent->directContactsPtrList.begin(); it != parent->directContactsPtrList.end(); ++it) {
                if (*it == node) {
                    parent->directContactsPtrList.erase(it);
                    break;
                }
            }
            clear(node);
            while (parent) {
                parent->totalCases--;
                parent = parent->parentPtr;
            }
        } else if (node == root) {
            clear(root);
            root = nullptr;
        } else {
            std::cerr << "Contact ID not found\n";
        }
    }

    void DisplayContact(const String& id) {
        TreeNode* node = findBFS(id);
        if (node) {
            std::cout << "Medicare ID: "   << node->medicareId << "\n";
            std::cout << "Direct Contacts: " << node->directContacts << "\n";
            std::cout << "Total Cases: "   << node->totalCases << "\n";
            std::cout << "Parent: " << (node->parentPtr ? node->parentPtr->medicareId : "None") << "\n";
        } else {
            std::cerr << "Contact ID not found\n";
        }
    }

    void TraceSource(const String& id) {
        TreeNode* node = findBFS(id);
        while (node) {
            std::cout << node->medicareId << " -> ";
            node = node->parentPtr;
        }
        std::cout << "Root\n";
    }

    void PrintContactCases(const String& id) {
        TreeNode* node = findBFS(id);
        if (node) {
            for (auto child : node->directContactsPtrList)
                std::cout << child->medicareId << "\n";
        } else {
            std::cerr << "Contact ID not found\n";
        }
    }

    void PrintContactTree() {
        if (!root) return;
        std::queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            DisplayContact(current->medicareId);
            std::cout << "---\n";
            for (auto child : current->directContactsPtrList)
                q.push(child);
        }
    }
};

// ===================== ContactList (Deque) =====================
class ContactList {
private:
    std::deque<std::string> contacts;

public:
    void addContactToFront(const std::string& contactId) {
        contacts.push_front(contactId);
    }
    void addContactToBack(const std::string& contactId) {
        contacts.push_back(contactId);
    }
    std::string removeContactFromFront() {
        if (!contacts.empty()) {
            std::string id = contacts.front();
            contacts.pop_front();
            return id;
        }
        return "";
    }
    std::string removeContactFromBack() {
        if (!contacts.empty()) {
            std::string id = contacts.back();
            contacts.pop_back();
            return id;
        }
        return "";
    }
    void displayContacts() {
        for (const std::string& c : contacts)
            std::cout << c << " ";
        std::cout << "\n";
    }
};

// ===================== main() =====================
int main() {

    // ---- ContactTree Demo ----
    std::cout << "========== CONTACT TREE DEMO ==========\n\n";

    ContactTree tree("P0");

    // Build the infection chain:
    //       P0
    //      /  \
    //    P1    P2
    //   /  \
    //  P3   P4
    tree.AddContact("P0", "P1");
    tree.AddContact("P0", "P2");
    tree.AddContact("P1", "P3");
    tree.AddContact("P1", "P4");

    std::cout << "Tree size (total cases): " << tree.GetSize() << "\n\n";

    std::cout << "--- Display P1 ---\n";
    tree.DisplayContact("P1");

    std::cout << "\n--- Trace source of P3 (back to Patient Zero) ---\n";
    tree.TraceSource("P3");

    std::cout << "\n--- Direct contacts of P1 ---\n";
    tree.PrintContactCases("P1");

    std::cout << "\n--- Full tree (BFS order) ---\n";
    tree.PrintContactTree();

    std::cout << "--- Deleting P1 (and their subtree: P3, P4) ---\n";
    tree.DeleteContact("P1");
    std::cout << "Tree size after deletion: " << tree.GetSize() << "\n\n";

    std::cout << "--- Tree after deletion ---\n";
    tree.PrintContactTree();

    // ---- ContactList (Deque) Demo ----
    std::cout << "========== CONTACT LIST (DEQUE) DEMO ==========\n\n";

    ContactList list;
    list.addContactToBack("C1");
    list.addContactToBack("C2");
    list.addContactToFront("C0");

    std::cout << "Contacts: ";
    list.displayContacts();

    std::cout << "Removed from front: " << list.removeContactFromFront() << "\n";
    std::cout << "Removed from back: "  << list.removeContactFromBack()  << "\n";

    std::cout << "Remaining contacts: ";
    list.displayContacts();

    return 0;
}