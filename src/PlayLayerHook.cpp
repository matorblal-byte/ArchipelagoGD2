#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/utils/random.hpp>
#include "APUtils.hpp"



class $modify(APPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        auto levelID = level->m_levelID.value();
        levelID = APUtils::checkIfTower(levelID);
        if (levelID < 50) {
        auto ccsched = cocos2d::CCScheduler::get();
    if (!(APUtils::speed == 100)) {
        double calctw = APUtils::speed/100;
        auto difficulty = level->m_difficulty;
        auto diffNum = static_cast<int>(difficulty);
        double randWeight = geode::utils::random::generate(0.004, 0.01);
        double base = calctw * (1.1 - ((randWeight) * (diffNum * 1.1));
        double exp = 0.8-(randWeight * 40);
        double weightedcalctw = std::pow(base, exp);
        double fullycalcedtw = std::clamp(weightedcalctw, 0.75, 2.50);
        geode::log::info("speed set: {}", fullycalcedtw);
        ccsched->setTimeScale(fullycalcedtw);
        FMODAudioEngine::get()->update(fullycalcedtw);
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
            FMODAudioEngine::get()->update(1.00);
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