#include <iostream>
#include <deque>

template<typename T>
class ContactList {
private:
    std::deque<T> contacts;

public:
    void addContactToFront(const T& contact) {
        contacts.push_front(contact);
    }

    void addContactToBack(const T& contact) {
        contacts.push_back(contact);
    }

    T removeContactFromFront() {
        if (!contacts.empty()) {
            T contact = contacts.front();
            contacts.pop_front();
            return contact;
        }
        return T(); 
    }

    T removeContactFromBack() {
        if (!contacts.empty()) {
            T contact = contacts.back();
            contacts.pop_back();
            return contact;
        }
        return T(); 
    }

    void displayContacts() {
        for (const T& contact : contacts) {
            std::cout << contact << " ";
        }
        std::cout << std::endl;
    }
};

