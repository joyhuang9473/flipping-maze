#include "ContactListener.h"

ContactListener::ContactListener() {}
ContactListener::~ContactListener() {}

void ContactListener::BeginContact(b2Contact* contact) {
    Contact curContact = {
        contact->GetFixtureA(),
        contact->GetFixtureB()
    };

    this->m_contacts.push_back(curContact);
}

void ContactListener::EndContact(b2Contact* contact) {
    Contact curContact = {
        contact->GetFixtureA(),
        contact->GetFixtureB()
    };

    std::vector<Contact>::iterator it = std::find(this->m_contacts.begin(), this->m_contacts.end(), curContact);

    if (it != this->m_contacts.end()) {
        this->m_contacts.erase(it);
    }
}
