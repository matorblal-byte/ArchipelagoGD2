#include <Geode/modify/MenuLayer.hpp>
#include "ConnectPopup.h"
#include "APUtils.hpp"

using namespace geode::prelude;

class $modify(APMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;
        
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
        
        return true;
    }

    void onArchipelago(CCObject*) {
        ConnectPopup::create()->show();
    }

    void debug(CCObject*) {
        /*
        Mod::get()->setSavedValue<bool>("Deadlocked: Unlock", true);
        AchievementNotifier::sharedState()->notifyAchievement("Deadlocked has been unlocked", "deadlocked is unlocked", "APLogo.png"_spr, true);
        */
       APUtils::recieveItem(130820149, false);
    }

    void debug2(CCObject*) {
        Mod::get()->setSavedValue<bool>("Deadlocked: Unlock", false);
        AchievementNotifier::sharedState()->notifyAchievement("Deadlocked has been locked", "deadlocked is locked", "APLogo.png"_spr, true);
    }
};


