#ifndef __FSM_h__
#define __FSM_h__

#include "cocos2d.h"

class FSM : public cocos2d::Node {
public:
    FSM(std::string state, std::function<void()> onEnter = nullptr);
    static FSM* create(std::string state, std::function<void()> onEnter = nullptr);

    FSM* addState(std::string state, std::function<void()> onEnter = nullptr);
    FSM* addEvent(std::string eventName, std::string from, std::string to);

    bool isContainState(std::string stateName);
    void printState();
    bool doEvent(std::string eventName);
    bool canDoEvent(std::string eventName);

    void setOnEnter(std::string state, std::function<void()> onEnter);

    std::string getCurrState();

private:
    void changeToState(std::string state);

    std::set<std::string> m_states;
    std::unordered_map<std::string,std::unordered_map<std::string,std::string>> m_events;
    std::unordered_map<std::string,std::function<void()>> m_onEnters;
    std::string m_currentState;
    std::string m_previousState;
};

#endif