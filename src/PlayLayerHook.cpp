#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/utils/random.hpp>
#include "APUtils.hpp"



class $modify(APPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
         geode::log::info("passed if");
        auto levelID = level->m_levelID.value();
         geode::log::info("got level id");
        levelID = APUtils::checkIfTower(levelID);
         geode::log::info("checked if it was tower lvl");
        if (levelID < 50) {
             geode::log::info("was less than 50");
        auto ccsched = cocos2d::CCScheduler::get();
         geode::log::info("obtained ccscheduler");
    if (!(APUtils::speed == 100)) {
         geode::log::info("it was not equal to 1`00");
        double calctw = APUtils::speed/100;
         geode::log::info("calculated the speed multi");
        auto difficulty = level->m_difficulty;
         geode::log::info("got level diff");
        auto diffNum = static_cast<int>(difficulty);
         geode::log::info("casted gddifficulty to int");
        double randWeight = geode::utils::random::generate(0.03, 0.05);
         geode::log::info("randomweiught");
        double weightedcalctw = calctw * (1.1 - (randWeight * diffNum));
         geode::log::info("got the weighted warp");
        double fullycalcedtw = std::clamp(weightedcalctw, 0.75, 2.50);
         geode::log::info("full");
        ccsched->setTimeScale(fullycalcedtw);
         geode::log::info("sped up");
    }
}
        return true;
    }

    void levelComplete() {
        auto ccsched = cocos2d::CCScheduler::get();
        auto levelID = this->m_level->m_levelID.value();
        levelID = APUtils::checkIfTower(levelID);
        geode::log::info("level id is {}", levelID);
        if (!(ccsched->getTimeScale() == 1.00)) {
            this->m_isTestMode = true;
            ccsched->setTimeScale(1.00);
        }
        if (levelID > 100 || this->m_isPracticeMode) {
            PlayLayer::levelComplete();
            return; // reaches into thje zone of normal levels
        }
        auto level = APUtils::levels.at(levelID);
        APUtils::sendItem(levelID);
        geode::log::info("completed level {}, sending itemid {}", level, levelID + 130820130);
        PlayLayer::levelComplete();
    }
};