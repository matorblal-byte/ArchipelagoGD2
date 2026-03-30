#include <Geode/modify/LevelPage.hpp>
#include "APUtils.hpp"

using namespace geode::prelude;

auto goaled = false;
class $modify(APLevelPage, LevelPage) {  
    
bool init(GJGameLevel* level) {
    if (!LevelPage::init(level)) {
        return false;
    }
    auto stars = GameStatsManager::sharedState()->getStat("6");
    geode::log::info("number of stars: {}", stars);
    if (stars > 180 && !goaled) {
        goaled = true;
        APUtils::goal();
        AchievementNotifier::sharedState()->notifyAchievement("Win", "You have released all your locations! Good win", "APLogo.png"_spr, true);
        FLAlertLayer::create("Warning", "Because you have goaled, you are unable to gain rewards from levels. Exit Archipelago mode to gain rewards again.", "Ok")->show();
        PlayLayer::get()->m_isTestMode = true;
    }
    return true;
}
    //thank you uproxide
    static void onModify(auto& self) {
        if (!self.setHookPriority("LevelPage::updateDynamicPage", -1)) {
            log::warn("uh oh");
        }
    }

    void onPlay(CCObject* sender) {
        // disable ther coin locks on play
        if (!APUtils::coinLocksEnabled) {
            m_level->m_requiredCoins = 0;
		    LevelPage::onPlay(sender);
        }
        // here we also check for button-menu because only the tower's levelpage has that so we can not lock it by accident
        if (bool canPlay = !Mod::get()->getSavedValue<bool>(this->m_level->m_levelName + ": Unlock", false) and !getChildByIDRecursive("button-menu")) {
            FLAlertLayer::create("Locked", "You have not recieved this level yet.", "OK")->show();
        }
        else {
            LevelPage::onPlay(nullptr);
        }
    }

    void updateDynamicPage(GJGameLevel* p0) {
        if (!APUtils::coinLocksEnabled) {
            p0->m_requiredCoins = 0;
		    LevelPage::updateDynamicPage(p0);
        }
        if (bool canPlay = !Mod::get()->getSavedValue<bool>(p0->m_levelName + ": Unlock", false)) {
            LevelPage::updateDynamicPage(p0);

            auto lockSprite = CCSprite::createWithSpriteFrameName("GJLargeLock_001.png");
            auto apSprite = CCSprite::createWithSpriteFrameName("APLogo.png"_spr);
            auto button = static_cast<CCMenuItemSpriteExtra*>(this->getChildByIDRecursive("level-button"));

            if (auto lSprite = this->getChildByIDRecursive("ap-lock-sprite"_spr)) {
                lSprite->removeMeAndCleanup();
            }
            if (auto aSprite = this->getChildByIDRecursive("ap-logo-sprite"_spr)) {
                aSprite->removeMeAndCleanup();
            }
            if (!button->getChildByIDRecursive("lock-sprite")) {
                button->addChild(lockSprite);
            }
            button->addChild(apSprite);

            lockSprite->setID("ap-lock-sprite"_spr);
            apSprite->setID("ap-logo-sprite"_spr);
            
            apSprite->setPositionX(15.0f);
            apSprite->setPositionY(15.0f);
            apSprite->setScale(.2f);
            lockSprite->setPosition(button->getContentSize() / 2);

            if (auto scale9 = static_cast<CCScale9Sprite*>(button->getChildByIDRecursive("scale-9-sprite"))) {
                scale9->getChildByID("level-name-label")->setVisible(false);
                scale9->getChildByID("difficulty-sprite")->setVisible(false);
                scale9->getChildByID("stars-icon")->setVisible(false);
                scale9->getChildByID("stars-label")->setVisible(false);
                // mana orbs aren't like the other girls?? for some reason??
                if (auto orbsLabel = scale9->getChildByID("orbs-label")) {
                    orbsLabel->setVisible(false);
                }
                if (auto orbsIcon = scale9->getChildByID("orbs-icon")) {
                    orbsIcon->setVisible(false);
                }
                // more difficulties compat
                if (auto morediff = scale9->getChildByID("uproxide.more_difficulties/more-difficulties-spr")) {
                    morediff->setVisible(false);
                }
            };
        }
        else {
            LevelPage::updateDynamicPage(p0);

            if (auto lSprite = this->getChildByIDRecursive("ap-lock-sprite"_spr)) {
                lSprite->removeMeAndCleanup();
            }
            if (auto aSprite = this->getChildByIDRecursive("ap-logo-sprite"_spr)) {
                aSprite->removeMeAndCleanup();
            }
        }
    }
};