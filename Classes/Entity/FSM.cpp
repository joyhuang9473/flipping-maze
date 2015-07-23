#include "FSM.h"

USING_NS_CC;

FSM::FSM(std::string state, std::function<void()> onEnter) {
    this->m_currentState = state;
    this->m_previousState = "";
    this->addState(state, onEnter);
}

FSM* FSM::create(std::string state, std::function<void()> onEnter) {
    FSM* fsm = new FSM(state, onEnter);

    if (fsm) {
        return fsm;
    }

    CC_SAFE_DELETE(fsm);
    return nullptr;
}

FSM* FSM::addState(std::string state, std::function<void()> onEnter) {
    if (state == "") {
        log("FSM::addState: state can't be empty string!");
        return nullptr;
    }

    this->m_states.insert(state);
    this->m_onEnters[state] = onEnter;
    return this;
}

bool FSM::isContainState(std::string stateName) {
    return this->m_states.find(stateName) != this->m_states.end();
}

void FSM::printState() {
    log("FSM::printState: list of states");

    for (auto iter = this->m_states.begin() ; iter != this->m_states.end() ; iter++) {
        log(iter->c_str());
    }
}

void FSM::changeToState(std::string state) {
    if (this->isContainState(state)) {
        this->m_previousState = this->m_currentState;
        this->m_currentState = state;

        log("FSM::changeToState: %s -> %s", this->m_previousState.c_str(), this->m_currentState.c_str());

        if (this->m_onEnters[state]) this->m_onEnters[state]();
    } else {
        log("FSM::changeToState: no such state as %s , state unchanged", state.c_str());
    }
}

FSM* FSM::addEvent(std::string eventName, std::string from, std::string to) {
    if (eventName == "") {
        log("FSM::addEvent: eventName can't be empty!");
        return nullptr;
    }
    if(!this->isContainState(from)) {
        log("FSM::addEvent: from state %s does not exit", from.c_str());
        return nullptr;
    }
    if(!this->isContainState(to)) {
        log("FSM::addEvent: to state %s does not exit", to.c_str());
        return nullptr;
    }

    std::unordered_map<std::string, std::string>& oneEvent = this->m_events[eventName];
    oneEvent[from] = to;
    return this;
}

bool FSM::canDoEvent(std::string eventName) {
    return this->m_events[eventName].find(this->m_currentState) != this->m_events[eventName].end();
}


bool FSM::doEvent(std::string eventName) {
    if (this->canDoEvent(eventName)) {
        log("FSM::doEvent: doing event %s", eventName.c_str());
        this->changeToState(this->m_events[eventName][this->m_currentState]);
        return true;
    } else {
        log("FSM::doEvent: cannot do event %s", eventName.c_str());
        return false;
    }
}

void FSM::setOnEnter(std::string state, std::function<void()> onEnter) {
    if (this->isContainState(state)) {
        this->m_onEnters[state] = onEnter;
    } else {
        log("FSM::setOnEnter: no state named %s", state.c_str());
    }
}

std::string FSM::getCurrState() {
    return this->m_currentState;
}

