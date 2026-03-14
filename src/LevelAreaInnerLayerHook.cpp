#include <Geode/Geode.hpp>
#include <Geode/modify/LevelAreaInnerLayer.hpp>
#include "APUtils.hpp"
// this is the tower btw
using namespace geode::prelude;

class $modify(APTowerLevelPage, LevelAreaInnerLayer) {
	bool init(bool p0) {
		if (!LevelAreaInnerLayer::init(p0)) {
			return false;
		    }
        auto lockedDoor = CCSpriteFrameCache::get()->spriteFrameByName("towerDoor_locked_001.png");
        auto mainNode = this->getChildByID("main-node");
        auto menu = mainNode->getChildByID("main-menu");
        auto TheTowerDoor = menu->getChildByID("level-5001-door");
        auto TheSewersDoor = menu->getChildByID("level-5002-door");
        auto TheCellarDoor = menu->getChildByID("level-5003-door");
        auto TheSecretHollowDoor = menu->getChildByID("level-5004-door");
        if (bool canPlay = !Mod::get()->getSavedValue<bool>("The Tower: Unlock", false)) {
            auto sprite = static_cast<CCSprite*>(TheTowerDoor->getChildByTag(1));
            sprite->setDisplayFrame(lockedDoor);
        }
        if (bool canPlay = !Mod::get()->getSavedValue<bool>("The Sewers: Unlock", false)) {
            auto sprite = static_cast<CCSprite*>(TheSewersDoor->getChildByTag(1));
            sprite->setDisplayFrame(lockedDoor);
        }
        if (bool canPlay = !Mod::get()->getSavedValue<bool>("The Cellar: Unlock", false)) {
            auto sprite = static_cast<CCSprite*>(TheCellarDoor->getChildByTag(1));
            sprite->setDisplayFrame(lockedDoor);
        }
        if (bool canPlay = !Mod::get()->getSavedValue<bool>("The Secret Hollow: Unlock", false)) {
            auto sprite = static_cast<CCSprite*>(TheSecretHollowDoor->getChildByTag(1));
            sprite->setDisplayFrame(lockedDoor);
        }
        return true;
        }
    void onDoor(CCObject* sender) {
        auto id = this->m_levelID;
        if (id == 5001) {
             if (bool canPlay = !Mod::get()->getSavedValue<bool>("The Tower: Unlock", false)) {
                FLAlertLayer::create("Locked", "You have not recieved this level yet.", "OK")->show();
            }
            else {
                LevelAreaInnerLayer::onDoor(sender);
            }
        } else if (id == 5002) {
             if (bool canPlay = !Mod::get()->getSavedValue<bool>("The Sewers: Unlock", false)) {
                FLAlertLayer::create("Locked", "You have not recieved this level yet.", "OK")->show();
            }
            else {
                LevelAreaInnerLayer::onDoor(sender);
            }
        } else if (id == 5003) {
             if (bool canPlay = !Mod::get()->getSavedValue<bool>("The Cellar: Unlock", false)) {
                FLAlertLayer::create("Locked", "You have not recieved this level yet.", "OK")->show();
            }
            else {
                LevelAreaInnerLayer::onDoor(sender);
            }
        } else if (id == 5004) {
             if (bool canPlay = !Mod::get()->getSavedValue<bool>("The Secret Hollow: Unlock", false)) {
                FLAlertLayer::create("Locked", "You have not recieved this level yet.", "OK")->show();
            }
            else {
                LevelAreaInnerLayer::onDoor(sender);
            }
        } else {
            geode::log::warn("unrecognized door {}", id);
            LevelAreaInnerLayer::onDoor(sender);
        }
};  
};