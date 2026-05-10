#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/utils/random.hpp>
#include "APUtils.hpp"
#include "Archipelago.h"

using namespace geode::prelude;

class $modify(APPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        geode::log::debug("Called PlayLayer::init()");
        auto levelID = level->m_levelID.value();
        levelID = APUtils::checkIfTower(levelID);
        if (levelID < 50) {
        auto ccsched = cocos2d::CCScheduler::get();
    if (APUtils::speed != 100) {
        double calctw = APUtils::speed/100;
        auto difficulty = level->m_difficulty;
        auto diffNum = static_cast<int>(difficulty);
        double randWeight = geode::utils::random::generate(0.004, 0.01);
        double base = calctw * (1.1 - ((randWeight) * (diffNum * 1.67)));
        double exp = 0.8-(randWeight * 50);
        calctw = std::pow(base, exp);
        calctw = std::clamp(calctw, 0.75, 2.50);
        geode::log::info("speed set: {}", calctw);
        ccsched->setTimeScale(calctw);
        FMOD::ChannelGroup* masterGroup;
        if (FMODAudioEngine::get()->m_system->getMasterChannelGroup(&masterGroup) != FMOD_OK) return false;
            masterGroup->setPitch(calctw);
    }
}
        geode::log::debug("PlayLayer::init() finished");
        return true;
    }

    // delete portals when needed
    void addObject(GameObject* p0) {
    if (APUtils::checkPortal(p0->m_objectID)) 
        PlayLayer::addObject(p0);
    }   

    void levelComplete() {
        geode::log::debug("Called PlayLayer::levelComplete()");
        auto ccsched = cocos2d::CCScheduler::get();
        auto levelID = this->m_level->m_levelID.value();
        levelID = APUtils::checkIfTower(levelID);
        levelID -= 1;
        geode::log::info("level id is {}", levelID);
        if (ccsched->getTimeScale() != 1.00) {
            ccsched->setTimeScale(1.00);
            FMOD::ChannelGroup* masterGroup;
            if (FMODAudioEngine::get()->m_system->getMasterChannelGroup(&masterGroup) != FMOD_OK) return;
                masterGroup->setPitch(1.00);
        }   
        if (levelID > 128 || this->m_isPracticeMode) {
            PlayLayer::levelComplete();
            return; // reaches into thje zone of normal levels
        }
        auto level = APUtils::levels.at(levelID);
        APUtils::sendItem(levelID); 
        // lets see if the player won the apworld
        auto stars = GameStatsManager::sharedState()->getStat("6");
        geode::log::info("number of stars: {}", stars);
        if (stars > 180) {
            FLAlertLayer::create("Warning", "Because you have goaled, you are unable to gain rewards from levels. Exit Archipelago mode to gain rewards again.", "Ok")->show();
            PlayLayer::get()->m_isTestMode = true;
        }
        geode::log::info("completed level {}, sending itemid {}", level, levelID + 130820130);
        auto status = AP_GetConnectionStatus();
        if (status == AP_ConnectionStatus::Disconnected || status == AP_ConnectionStatus::ConnectionRefused) {
            geode::Notification::create("Error: You currently aren't connected to Archipelago!", geode::NotificationIcon::None, 4.f)->show();
        }
        geode::log::debug("Finished PlayLayer::levelComplete()");
        PlayLayer::levelComplete();
    }
    void onQuit() {
        geode::log::debug("Called PlayLayer::onQuit()");
        auto ccsched = cocos2d::CCScheduler::get();
        if (ccsched->getTimeScale() != 1.00) {
            ccsched->setTimeScale(1.00);
            FMOD::ChannelGroup* masterGroup;
            if (FMODAudioEngine::get()->m_system->getMasterChannelGroup(&masterGroup) != FMOD_OK) return;
                masterGroup->setPitch(1.00);
        }
        geode::log::debug("Finished PlayLayer::onQuit()");
        PlayLayer::onQuit();
    }
};
