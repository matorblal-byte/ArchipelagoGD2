#pragma once
// textinput refuses to compile if you don't include the delegate as well

#include <Geode/Geode.hpp>  
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/TextInput.hpp>

using namespace geode::prelude;

class ConnectPopup : public geode::Popup<> {
    protected:
    bool setup() override;
    TextInput* urlInput;
    TextInput* slotInput;
    TextInput* passInput;
    
    public:
    //void onConnect(std::string url, std::string slot, std::string password, CCObject* sender);
    //(urlLabel->getString(), slotLabel->getString(), passLabel->getString())
    void onConnect(CCObject*);
    void connectToAP(const char* url, const char* slot, const char* password);
    static ConnectPopup* create();
};