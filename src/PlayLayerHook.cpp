#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "APUtils.hpp"

int gdBaseID = 130820130;

class $modify(APPlayLayer, PlayLayer) {
    void void levelComplete() {
        auto levelID = this->m_level->m_levelID.value() - 1; // -1 because of 0 indexing
        if (levelID > 100) {
            return; // reaches into thje zone of normal levels
        }
        auto level = APUtils::levels.at(levelID);
        APUtils::sendItem(levelID + gdBaseID);
        geode::log::info("completed level {}, sending itemid {}", level, levelID + gdBaseID);
        PlayLayer::levelComplete();
    }
}