#include <Geode/Geode.hpp>
#include <Geode/modify/PurchaseItemPopup.hpp>

using namespace geode::prelude;

class $modify(APPurchaseItemPopup, PurchaseItemPopup) {
    static PurchaseItemPopup* create(GJStoreItem* item) {
        PurchaseItemPopup* ret = PurchaseItemPopup::create(item);
        geode::log::debug("Called PurchaseItemPopup::init()");
        auto APItem1 = GameStatsManager::sharedState()->getStoreItem(121);
        auto APItem2 = GameStatsManager::sharedState()->getStoreItem(122);
        auto APItem3 = GameStatsManager::sharedState()->getStoreItem(123);
        auto APItem4 = GameStatsManager::sharedState()->getStoreItem(124);
        auto APItem5 = GameStatsManager::sharedState()->getStoreItem(125);
        auto APItem6 = GameStatsManager::sharedState()->getStoreItem(126);
        if (item == APItem1 ||
            item == APItem2 ||
            item == APItem3 ||
            item == APItem4 ||
            item == APItem5 ||
            item == APItem6
        ) {
            auto ccspr = ret->getChildByID("main-layer")->getChildByID("icon")->getChildByType<cocos2d::CCSprite>(0);
            ccspr->removeFromParent();
            auto archImage = CCSprite::create("APLogo.png"_spr);
            archImage->setScale(0.3f);
            archImage->setPosition(CCPoint(17.f, 20.f)); 
            ret->getChildByID("main-layer")->getChildByID("icon")->addChild(archImage);
            auto text = ret->getChildByID("main-layer")->getChildByID("info-area")->getChildByType<MultilineBitmapFont>(0)->getChildByType<CCLabelBMFont>(0);
            text->setString("Do you want to buy this Archipelago Item");
            text->setScale(0.7f);
            for (auto i = 24; i < 40; i++) {
                auto letter = text->getChildByType<cocos2d::CCFontSprite>(i);
                letter->setColor(ccORANGE);
            }
        }
        geode::log::debug("Finished PurchaseItemPopup::init()");
        return ret;
    }
};