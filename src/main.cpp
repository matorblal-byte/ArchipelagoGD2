#include <Geode/modify/MenuLayer.hpp>
#include "ConnectPopup.cpp"
#include "APUtils.hpp"
#include "Archipelago.h"

using namespace geode::prelude;

class $modify(APMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;
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
        auto trm = static_cast<CCMenu*>(this->getChildByID("top-right-menu"));
        trm->addChild(apBtn);
        trm->addChild(otherBtn);
        trm->addChild(anotherBtn);
        trm->updateLayout();
        if (APUtils::manaOrbsToAdd != 0) {
            GameStatsManager::sharedState()->incrementStat("14", APUtils::manaOrbsToAdd);
        }
        if (APUtils::diamondsToAdd != 0) {
            GameStatsManager::sharedState()->incrementStat("13", APUtils::diamondsToAdd);
        }
        return true;
    
        if (Mod::get()->getSavedValue<bool>("InArchMode", false)) {
            auto status = AP_GetConnectionStatus();
            if (status != AP_ConnectionStatus::Connected && status != AP_ConnectionStatus::Authenticated) {
                FLAlertLayer::create("Error", "You are not connected to AP currently! You might be slow to connect, but if not please check your internet connection", "Ok")->show();
            }
        }
    }

    void onArchipelago(CCObject*) {
        ConnectPopup::create()->show();
    }

    void debug(CCObject*) {
        Mod::get()->setSavedValue<bool>("Deadlocked: Unlock", true);
        AchievementNotifier::sharedState()->notifyAchievement("Deadlocked has been unlocked", "deadlocked is unlocked", "APLogo.png"_spr, true);
       APUtils::recieveItem(130820149, false);
    }

    void debug2(CCObject*) {
        Mod::get()->setSavedValue<bool>("Deadlocked: Unlock", false);
        AchievementNotifier::sharedState()->notifyAchievement("Deadlocked has been locked", "deadlocked is locked", "APLogo.png"_spr, true);
    }
        
};

