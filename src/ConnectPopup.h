#pragma once
// textinput refuses to compile if you don't include the delegate as well

#include <Geode/Geode.hpp>  
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/TextInput.hpp>

using namespace geode::prelude;

class ConnectPopup : public Popup {
    log::info("Defining ConnectPopup class");
    protected:
    bool init();
    log::info("Called init function");
    TextInput* urlInput;
    TextInput* slotInput;
    TextInput* passInput;
    log::info("Defined text input members");
    public:
    //void onConnect(std::string url, std::string slot, std::string password, CCObject* sender);
    //(urlLabel->getString(), slotLabel->getString(), passLabel->getString())
    void onConnect(CCObject*);
    void connectToAP(const char* url, const char* slot, const char* password);
    log::info("About to create connectpopup");
    static ConnectPopup* create();
    log::info("ok");
};