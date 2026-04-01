#include <Geode/Geode.hpp>
#include <Geode/modify/GameStatsManager.hpp>
#include "APUtils.hpp"

using namespace geode::prelude;

class $modify(APGameStatsManager, GameStatsManager) {
    bool purchaseItem(int index) {
        if (!GameStatsManager::purchaseItem(index)) return false;
        if (index > 120) {
            index -= 21; // -20 is just to offset it to ther right asmount and -1 is 0 indexing 
            APUtils::sendItem(index);
        }
        return true;
    }
};