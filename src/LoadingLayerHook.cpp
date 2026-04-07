#include "Geode/binding/LoadingLayer.hpp"
#include "Geode/cocos/CCDirector.h"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include <Geode/modify/LoadingLayer.hpp>
#include <Geode/loader/Dirs.hpp>
#include "APUtils.hpp"
#include <Archipelago.h>

using namespace geode::prelude;

class $modify(APLoadingLayer, LoadingLayer) {
    bool init(bool p0) {
        if (!LoadingLayer::init(p0)) return false;
        std::error_code error;
        APUtils::inLoadingLayer = true;
        auto saves = dirs::getSaveDir();
        auto dir = dirs::getGameDir();
        if (std::filesystem::exists(saves / "inArchModeFlag.txt") || Mod::get()->getSavedValue("InArchMode", false)) {
            auto url = Mod::get()->getSavedValue<std::string>("recent-url", "");
            if (url == "") {
                log::warn("The url is empty");
            }
            APUtils::startArchipelago(url.c_str(), Mod::get()->getSavedValue<std::string>("recent-slot", "").c_str(), Mod::get()->getSavedValue<std::string>("recent-pass", "").c_str());
            auto apLabel = CCLabelBMFont::create(("ArchipelagoGD: Connecting to " + url).c_str(), "goldFont.fnt");
            apLabel->setPosition(CCDirector::get()->getWinSize().width / 2, CCDirector::get()->getWinSize().height - 10);
            apLabel->setScale(.45f);
            apLabel->setID("ap-status-label"_spr);
            this->addChild(apLabel);
            Mod::get()->setSavedValue("InArchMode", true); // 2 checks for if your in arch mode because why not shhh (only used for connectpopup)
            std::filesystem::remove(saves / "inArchModeFlag.txt");
            // add shop items
            if (APUtils::checkShopEnabled) {
                auto shopKeeperShop = GameStatsManager::sharedState()->shopTypeForItemID(1);
                auto archImage = CCSprite::create("APLogo.png"_spr);
                archImage->setTag(100);
                GameStatsManager::sharedState()->addStoreItem(121, 0, 1000, 1000, shopKeeperShop);
                GameStatsManager::sharedState()->addStoreItem(122, 0, 1000, 1000, shopKeeperShop);
                GameStatsManager::sharedState()->addStoreItem(123, 0, 1000, 1000, shopKeeperShop);
                GameStatsManager::sharedState()->addStoreItem(124, 0, 1000, 1000, shopKeeperShop);
                GameStatsManager::sharedState()->addStoreItem(125, 0, 1000, 1000, shopKeeperShop);
                GameStatsManager::sharedState()->addStoreItem(126, 0, 1000, 1000, shopKeeperShop);
            }
        } else {
            auto apLabel = CCLabelBMFont::create("ArchipelagoGD: Not connected", "goldFont.fnt");
            apLabel->setPosition(CCDirector::get()->getWinSize().width / 2, CCDirector::get()->getWinSize().height - 10);
            apLabel->setScale(.45f);
            apLabel->setID("ap-status-label"_spr);
            this->addChild(apLabel);
            for (auto& hook : Mod::get()->getHooks()) {
                if (hook->isEnabled() && !(hook->getDisplayName() == "LoadingLayer::init")){
                    hook->disable();
                }
                if ( // enable back the menu hooks so we can connect
                hook->getDisplayName() == "ConnectPopup::onConnect" || 
                hook->getDisplayName() == "GManager::setup" ||
                hook->getDisplayName() == "MenuLayer::init" ||
                hook->getDisplayName() == "MenuLayer::onArchipelago" ||
                hook->getDisplayName() == "MenuLayer::debug" ||
                hook->getDisplayName() == "MenuLayer::debug2"
                ) {
                    hook->enable();
                }
            Mod::get()->setSavedValue("InArchMode", false);
            }
        }

        return true;
    }
};