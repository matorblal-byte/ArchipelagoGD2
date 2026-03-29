#include "APUtils.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

using namespace geode::prelude;

class $modify(APGJBaseGameLayer, GJBaseGameLayer) {
    void processItems() {
        auto stars = GameStatsManager::sharedState()->getStat("6");
        geode::log::info("number of stars: {}", stars);
        if (stars > 180) {
            FLAlertLayer::create("Warning", "Because you have goaled, you are unable to gain rewards from levels. Exit Archipelago mode to gain rewards again.", "Ok")->show();
            PlayLayer::get()->m_isTestMode = true;
        }
        GJBaseGameLayer::processItems();
        stars = GameStatsManager::sharedState()->getStat("6"); // get it again because stars were presumably added
        geode::log::info("number of stars: {}", stars);
        if (stars > 180) {
            APUtils::goal();
            AchievementNotifier::sharedState()->notifyAchievement("Win", "You have released all your locations! Good win", "APLogo.png"_spr, true);
            FLAlertLayer::create("Warning", "Because you have goaled, you are unable to gain rewards from levels. Exit Archipelago mode to gain rewards again.", "Ok")->show();
            PlayLayer::get()->m_isTestMode = true;
        }
        auto levelObj = PlayLayer::get()->m_level;
        if (APUtils::coinsEnabled) {
            auto levelID = levelObj->m_levelID.value();
            if (levelID < 100) {
                for (int i = 0; i < 3; i++) {
                    auto key = levelObj->getCoinKey(i+1);
                    auto hasCoin = GameStatsManager::sharedState()->hasSecretCoin(key);
                    if (hasCoin) {
                        auto itemID = (levelID * 1000) + (i+1) + 130820130;
                        APUtils::sendItem(itemID);
                        geode::log::info("sent coin item with id {}", itemID);
                    } else {
                        if (!key) {
                            geode::log::warn("couldnt find key for coin {}, level {}, id {}", i+1, levelID, levelObj->m_levelID.value());
                        }
                    }
                }
            }
        }
    }
};