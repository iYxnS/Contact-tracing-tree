#include <iostream>
#include <deque>
#include <string>

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
            std::string contactId = contacts.front();
            contacts.pop_front();
            return contactId;
        }
        return ""; 
    }

    std::string removeContactFromBack() {
        if (!contacts.empty()) {
            std::string contactId = contacts.back();
            contacts.pop_back();
            return contactId;
        }
        return ""; 
    }

    void displayContacts() {
        for (const std::string& contact : contacts) {
            std::cout << contact << " ";
        }
        std::cout << std::endl;
    }
};
