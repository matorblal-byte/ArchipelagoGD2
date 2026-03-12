#include "Geode/binding/LoadingLayer.hpp"
#include "Geode/cocos/CCDirector.h"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include <Geode/modify/LoadingLayer.hpp>
#include "APUtils.hpp"
#include <Archipelago.h>

using namespace geode::prelude;

/*
class $modify(APLoadingLayer, LoadingLayer) {
    bool init(bool p0) {
        if (!LoadingLayer::init(p0)) return false;
        if (Mod::get()->getSavedValue<std::string>("recent-url", "") != "") {
            auto url = Mod::get()->getSavedValue<std::string>("recent-url", "");
            APUtils::startArchipelago(url.c_str(), Mod::get()->getSavedValue<std::string>("recent-slot", "").c_str(), Mod::get()->getSavedValue<std::string>("recent-pass", "").c_str());
            auto apLabel = CCLabelBMFont::create(("ArchipelagoGD: Connecting to " + url).c_str(), "goldFont.fnt");
            apLabel->setPosition(CCDirector::get()->getWinSize().width / 2, CCDirector::get()->getWinSize().height - 10);
            apLabel->setScale(.45f);
            apLabel->setID("ap-status-label"_spr);
            this->addChild(apLabel);
            Mod::get()->setSavedValue<std::string>("recent-url", "");
        } else {
            auto apLabel = CCLabelBMFont::create("ArchipelagoGD: Not connected", "goldFont.fnt");
            apLabel->setPosition(CCDirector::get()->getWinSize().width / 2, CCDirector::get()->getWinSize().height - 10);
            apLabel->setScale(.45f);
            apLabel->setID("ap-status-label"_spr);
            this->addChild(apLabel);
        }

        return true;
    }
};
*/