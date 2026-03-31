#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/utils/random.hpp>
#include "APUtils.hpp"

using namespace geode::prelude;

class $modify(APPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        auto levelID = level->m_levelID.value();
        levelID = APUtils::checkIfTower(levelID, false);
        if (levelID < 50) {
        auto ccsched = cocos2d::CCScheduler::get();
    if (APUtils::speed != 100) {
        double calctw = APUtils::speed/100;
        auto difficulty = level->m_difficulty;
        auto diffNum = static_cast<int>(difficulty);
        double randWeight = geode::utils::random::generate(0.004, 0.01);
        double base = calctw * (1.1 - ((randWeight) * (diffNum * 1.67)));
        double exp = 0.8-(randWeight * 50);
        double weightedcalctw = std::pow(base, exp);
        double fullycalcedtw = std::clamp(weightedcalctw, 0.75, 2.50);
        geode::log::info("speed set: {}", fullycalcedtw);
        ccsched->setTimeScale(fullycalcedtw);
        FMODAudioEngine::get()->update(fullycalcedtw);
        FMOD::ChannelGroup* masterGroup;
        if (FMODAudioEngine::get()->m_system->getMasterChannelGroup(&masterGroup) != FMOD_OK) return false;
            masterGroup->setPitch(1.00);
    }
}
        return true;
    }

    // delete portals when needed
    void addObject(GameObject* p0) {
    if (APUtils::checkPortal(p0->m_objectID)) 
        PlayLayer::addObject(p0);
    }   

    void levelComplete() {
        auto ccsched = cocos2d::CCScheduler::get();
        auto levelID = this->m_level->m_levelID.value();
        levelID = APUtils::checkIfTower(levelID, true);
        levelID -= 1;
        geode::log::info("level id is {}", levelID);
        if (!(ccsched->getTimeScale() == 1.00)) {
            ccsched->setTimeScale(1.00);
            FMODAudioEngine::get()->update(1.00);
            FMOD::ChannelGroup* masterGroup;
            if (FMODAudioEngine::get()->m_system->getMasterChannelGroup(&masterGroup) != FMOD_OK) return;
                masterGroup->setPitch(1.00);
        }   
        if (levelID > 100 || this->m_isPracticeMode) {
            PlayLayer::levelComplete();
            return; // reaches into thje zone of normal levels
        }
        auto level = APUtils::levels.at(levelID - 1);
        APUtils::sendItem(levelID); 
        // lets see if the player won the apworld
        auto stars = GameStatsManager::sharedState()->getStat("6");
        geode::log::info("number of stars: {}", stars);
        if (stars > 180) {
            FLAlertLayer::create("Warning", "Because you have goaled, you are unable to gain rewards from levels. Exit Archipelago mode to gain rewards again.", "Ok")->show();
            PlayLayer::get()->m_isTestMode = true;
        }
        geode::log::info("completed level {}, sending itemid {}", level, levelID + 130820130);
        PlayLayer::levelComplete();
    }
};
