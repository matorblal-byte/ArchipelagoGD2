#include <Geode/Geode.hpp>
#include <Geode/modify/LevelAreaInnerLayer.hpp>
#include "APUtils.hpp"
// this is the tower btw
using namespace geode::prelude;

class $modify(APTowerLevelPage, LevelAreaInnerLayer) {
    static void onModify(auto& self) {
        if (!self.setHookPriority("LevelAreaInnerLayer::init", -1)) {
            log::warn("uh oh");
        }
    }

	bool init(bool p0) {
        log::info("init func");
		if (!LevelAreaInnerLayer::init(p0)) {
			return false;
		    }
        log::info("defining stuffs");
        auto lockedDoor = CCSpriteFrameCache::get()->spriteFrameByName("towerDoor_locked_001.png");
        log::info("locked door");
        auto mainNode = this->getChildByID("main-node");
        log::info("main node");
        auto menu = mainNode->getChildByID("main-menu");
        log::info("main menu");
        auto TheTowerDoor = menu->getChildByID("level-5001-door");
        log::info("the tower door");
        auto TheSewersDoor = menu->getChildByID("level-5002-door");
        log::info("the sewers door");
        auto TheCellarDoor = menu->getChildByID("level-5003-door");
        log::info("the cellar door");
        auto TheSecretHollowDoor = menu->getChildByID("level-5004-door");
        log::info("the secret hollow door");
        log::info("setting up doors");
        if (bool canPlay = !Mod::get()->getSavedValue<bool>("The Tower: Unlock", false)) {
            log::info("finding sprite");
            auto sprite = static_cast<CCSprite*>(TheTowerDoor->getChildByTag(1));
            log::info("setting frame");
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
        log::info("hey man i finished");
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