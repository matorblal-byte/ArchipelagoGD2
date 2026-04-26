#include <Geode/modify/MenuLayer.hpp>
#include "ConnectPopup.cpp"
#include "APUtils.hpp"
#include "Archipelago.h"

using namespace geode::prelude;

class $modify(APMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;
        geode::log::debug("Called MenuLayer::init()");
        APUtils::inLoadingLayer = false;
        auto apBtn = CCMenuItemSpriteExtra::create(
            CircleButtonSprite::createWithSprite("APLogo.png"_spr, 1.0f, CircleBaseColor::Gray, CircleBaseSize::SmallAlt),
            this,
            menu_selector(APMenuLayer::onArchipelago)
        );
        auto otherBtn = CCMenuItemSpriteExtra::create(
            CircleButtonSprite::createWithSprite("APLogo.png"_spr, 1.0f, CircleBaseColor::Green, CircleBaseSize::SmallAlt),
            this,
            menu_selector(APMenuLayer::debug)
        );
        auto anotherBtn = CCMenuItemSpriteExtra::create(
            CircleButtonSprite::createWithSprite("APLogo.png"_spr, 1.0f, CircleBaseColor::DarkAqua, CircleBaseSize::SmallAlt),
            this,
            menu_selector(APMenuLayer::debug2)
        );
        if (geode::Loader::get()->getLoadedMod("ninxout.redash")) {
            auto bm = this->getChildByID("bottom-menu");
            bm->addChild(apBtn);
            //bm->addChild(otherBtn);
            //bm->addChild(anotherBtn);
            bm->updateLayout();
        } else {
        auto trm = static_cast<CCMenu*>(this->getChildByID("top-right-menu"));
        trm->addChild(apBtn);
        trm->addChild(otherBtn);
        trm->addChild(anotherBtn);
        otherBtn->setVisible(false);
        anotherBtn->setVisible(false);
        trm->updateLayout();
        }
        apBtn->setID("APConnectBtn"_spr);
        otherBtn->setID("APDebug1Btn"_spr);
        anotherBtn->setID("APDebug2Btn"_spr);
        if (APUtils::manaOrbsToAdd != 0) {
            GameStatsManager::sharedState()->incrementStat("14", APUtils::manaOrbsToAdd);
            APUtils::manaOrbsToAdd = 0;
        }
        if (APUtils::diamondsToAdd != 0) {
            GameStatsManager::sharedState()->incrementStat("13", APUtils::diamondsToAdd);
            APUtils::diamondsToAdd = 0;
        }
        if (Mod::get()->getSavedValue<bool>("InArchMode", false)) {
            auto status = AP_GetConnectionStatus();
            if (status == AP_ConnectionStatus::Disconnected || status == AP_ConnectionStatus::ConnectionRefused) {
                geode::Notification::create("Error: You currently aren't connected to Archipelago!", geode::NotificationIcon::None, 4.f)->show();
            }
        }
        if (APUtils::errorMessage != "") {
            geode::Notification::create(APUtils::errorMessage.c_str(), geode::NotificationIcon::None, 4.f)->show();
        }
        geode::log::debug("MenuLayer::init() was finshed");
        return true;
    }

    void onArchipelago(CCObject*) {
        ConnectPopup::create()->show();
    }

    void debug(CCObject*) {
        for (auto& level : APUtils::levels) {
                Mod::get()->setSavedValue<bool>(level + ": Unlock", true);
            }
    }

    void debug2(CCObject*) {
        if (GJAccountManager::sharedState()->m_username.empty()) { // i am NOT getting banned for misclicking this
        GameStatsManager::sharedState()->incrementStat("14", 10000);
        }
    }
        
};

