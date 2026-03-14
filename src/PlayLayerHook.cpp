#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "APUtils.hpp"



class $modify(APPlayLayer, PlayLayer) {
    void levelComplete() {
        geode::log::info("is this mic on");
        auto levelID = this->m_level->m_levelID.value();
        geode::log::info("level id is {}", levelID);
        if (levelID > 100) {
            return; // reaches into thje zone of normal levels
        }
        auto level = APUtils::levels.at(levelID);
        APUtils::sendItem(levelID);
        geode::log::info("completed level {}, sending itemid {}", level, levelID + 130820130);
        PlayLayer::levelComplete();
    }
};