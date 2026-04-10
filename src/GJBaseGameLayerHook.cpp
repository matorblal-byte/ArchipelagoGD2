#include "APUtils.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

using namespace geode::prelude;

class $modify(APGJBaseGameLayer, GJBaseGameLayer) {
    void processItems() {
        geode::log::debug("Called GJBaseGameLayer::processItems()");
        GJBaseGameLayer::processItems();
        auto levelObj = PlayLayer::get()->m_level;
        if (APUtils::coinsEnabled) {
            auto levelID = levelObj->m_levelID.value();
            levelID = APUtils::checkIfTower(levelID);
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
        geode::log::debug("Finished GJBaseGameLayer::processItems()");
    }
};
