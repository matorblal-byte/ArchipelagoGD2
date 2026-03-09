#include "Geode/binding/LoadingLayer.hpp"
#include "Geode/cocos/CCDirector.h"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include <Geode/modify/LoadingLayer.hpp>

using namespace geode::prelude;

class $modify(APLoadingLayer, LoadingLayer) {
    bool init(bool p0) {
        if (!LoadingLayer::init(p0)) return false;

        auto apLabel = CCLabelBMFont::create("ArchipelagoGD: Connecting to archipelago.gg:12345", "goldFont.fnt");
        apLabel->setPosition(CCDirector::get()->getWinSize().width / 2, CCDirector::get()->getWinSize().height - 10);
        apLabel->setScale(.45f);
        apLabel->setID("ap-status-label"_spr);
        this->addChild(apLabel);

        return true;
    }
};