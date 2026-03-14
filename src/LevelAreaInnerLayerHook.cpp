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
		if (!LevelAreaInnerLayer::init(p0)) {
			return false;
		    }
        auto mainNode = this->getChildByID("main-node");
        if (!mainNode) {
            log::warn("could not find main node");
            return true;
        }
        auto menu = mainNode->getChildByID("main-menu");
        if (!menu) {
            log::warn("could not find menu");
            return true;
        }
        auto TheTowerDoor = geode::cast::typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("level-5001-button"));
;        if (!TheTowerDoor) {
            log::warn("could not find tower door");
            return true;
        }
        auto TheSewersDoor = geode::cast::typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("level-5002-button"));
        if (!TheSewersDoor) {
            log::warn("could not find sewers door");
            return true;
        }
        auto TheCellarDoor = geode::cast::typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("level-5003-button"));
        if (!TheCellarDoor) {
            log::warn("could not find cellar door");
            return true;
        }
        auto TheSecretHollowDoor = geode::cast::typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("level-5004-button"));
        if (!TheSecretHollowDoor) {
            log::warn("could not find secret hollow door");
            return true;
        }
        if (bool canPlay = !Mod::get()->getSavedValue<bool>("The Tower: Unlock", false)) {
            auto lockedDoor5001 = CCSprite::createWithSpriteFrameName("towerDoor_locked_001.png");
            TheTowerDoor->setNormalImage(lockedDoor5001);
        }
        if (bool canPlay = !Mod::get()->getSavedValue<bool>("The Sewers: Unlock", false)) {
            auto lockedDoor5002 = CCSprite::createWithSpriteFrameName("towerDoor_locked_001.png");
            TheSewersDoor->setNormalImage(lockedDoor5002);
        }
        if (bool canPlay = !Mod::get()->getSavedValue<bool>("The Cellar: Unlock", false)) {
            auto lockedDoor5003 = CCSprite::createWithSpriteFrameName("towerDoor_locked_001.png");
            TheCellarDoor->setNormalImage(lockedDoor5003);
        }
        if (bool canPlay = !Mod::get()->getSavedValue<bool>("The Secret Hollow: Unlock", false)) {
            auto lockedDoor5004 = CCSprite::createWithSpriteFrameName("towerDoor_locked_001.png");
            TheSecretHollowDoor->setNormalImage(lockedDoor5004);
        }
        return true;
        }
    void onDoor(CCObject* sender) {
        auto id = sender->getTag();
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