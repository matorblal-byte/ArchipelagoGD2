#include "ConnectPopup.h"
#include <Geode/binding/ButtonSprite.hpp>
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>
#include <Geode/binding/FLAlertLayer.hpp>
#include <Geode/cocos/cocoa/CCObject.h>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/TextInput.hpp>
#include <fmt/core.h>
#include <string>
#include <wincrypt.h>
#include <Archipelago.h>
#include "APUtils.hpp"

using namespace geode::prelude;

bool ConnectPopup::setup() {
    m_noElasticity = true;

    this->setTitle("Connect to Archipelago");

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto const layerSize = CCSize { 346.f, 280.f };
    auto const layerPos = (winSize - layerSize) / 2;

    urlInput = TextInput::create(260, "archipelago.gg:12345", "chatFont.fnt");
    slotInput = TextInput::create(260, "1257Plays", "chatFont.fnt");
    passInput = TextInput::create(260, "topsecretpassword", "chatFont.fnt");

    urlInput->setFilter("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.:;*/");
    urlInput->setString(Mod::get()->getSavedValue<std::string>("recent-url", ""));

    slotInput->setFilter("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-_;:/?!.,[]{}/=+* ");
    slotInput->setString(Mod::get()->getSavedValue<std::string>("recent-slot", ""));

    passInput->setFilter("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-_;:/?!.,[]{}/=+* ");
    passInput->setString(Mod::get()->getSavedValue<std::string>("recent-pass", ""));
    
    auto urlLabel = CCLabelBMFont::create("Archipelago URL", "bigFont.fnt");
    auto slotLabel = CCLabelBMFont::create("Slot Name", "bigFont.fnt");
    auto passLabel = CCLabelBMFont::create("Password (if not set, leave empty)", "bigFont.fnt");

    urlLabel->setScale(.5f);
    urlLabel->setPosition(173.f, 225.f);
    urlInput->setPosition(173.f, urlLabel->getPositionY()-25.f);

    slotLabel->setScale(.5f);
    slotLabel->setPosition(173.f, 170.f);
    slotInput->setPosition(173.f, slotLabel->getPositionY()-25.f);

    passLabel->setScale(.5f);
    passLabel->setPosition(173.f, 115.f);
    passInput->setPosition(173.f, passLabel->getPositionY()-25.f);

    auto connectButton = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Connect"),
        this,
        menu_selector(ConnectPopup::onConnect)
    );

    connectButton->setPosition(173.f, 40.f);

    auto menu = m_buttonMenu;
    menu->addChild(urlInput);
    menu->addChild(slotInput);
    menu->addChild(passInput);

    m_mainLayer->addChild(urlLabel);
    m_mainLayer->addChild(slotLabel);
    m_mainLayer->addChild(passLabel);

    menu->addChild(connectButton);

    return true;
}

void ConnectPopup::onConnect(CCObject*) {
    geode::createQuickPopup(
        "Connect",
        "Are you sure you want to connect to Archipelago? When you agree to this, your game will restart into Archipelago mode. To leave Archipelago mode, open this menu when connected and choose <cr>\"Disconnect\".</c>\n<cg>Server:</c> " + urlInput->getString() + "\n<cb>Slot</c>: " + slotInput->getString(),
        "No", "Yes",
        [this](auto, bool btn2) {
            if (btn2) {
                ConnectPopup::connectToAP(urlInput->getString().c_str(), slotInput->getString().c_str(), passInput->getString().c_str());
            }
        }
    );
}

void ConnectPopup::connectToAP(const char* url, const char* slot, const char* pass) {
    FLAlertLayer::create("stuff", "currently trying to connect - give me a sec and check your multiworld panel", "cool")->show();
    AP_Init(url, "Geometry Dash", slot, pass);
    AP_SetItemClearCallback(&APUtils::clearItemState);
    AP_SetItemRecvCallback(&APUtils::recieveItem);
    AP_SetLocationCheckedCallback(&APUtils::checkLocationCallback);
    AP_SetDeathLinkSupported(true);
    AP_SetDeathLinkRecvCallback(&APUtils::deathLinkRecieved);
    AP_Start();
    Mod::get()->setSavedValue<std::string>("recent-url", urlInput->getString());
    Mod::get()->setSavedValue<std::string>("recent-slot", slotInput->getString());
    Mod::get()->setSavedValue<std::string>("recent-pass", passInput->getString());
}

ConnectPopup* ConnectPopup::create() {
    auto* ret = new ConnectPopup();

   
    if (ret && ret->initAnchored(346.f, 280.f)) {
        ret->autorelease();   
    } else {
        CC_SAFE_DELETE(ret);
    }

    return ret;
};