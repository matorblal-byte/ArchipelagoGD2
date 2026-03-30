#include "Archipelago.h"
#include <Geode/modify/GameStatsManager.hpp>
#include "APUtils.hpp"
using namespace geode::prelude;

class $modify(APGameStatsManager, GameStatsManager) {
    void incrementStat(char* key, int amount) {
        if (key == "6") {
            GameStatsManager::incrementStat(key, amount);
            auto stars = GameStatsManager::sharedState()->getStat("6");
                geode::log::info("number of stars: {}", stars);
                if (stars > 180) {
                    APUtils::goal();
                    AchievementNotifier::sharedState()->notifyAchievement("Win", "You have released all your locations! Good win", "APLogo.png"_spr, true);
                    FLAlertLayer::create("Warning", "Because you have goaled, you are unable to gain rewards from levels. Exit Archipelago mode to gain rewards again.", "Ok")->show();
                    PlayLayer::get()->m_isTestMode = true;
                    return;
            }
        }
        GameStatsManager::incrementStat(key, amount);
    }
};