#include <Geode/Geode.hpp>
#include <Geode/modify/PurchaseItemPopup.hpp>
#include "../APUtils.hpp"
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
            std::string imageToCreate;
            if (item == APItem1) { // held item is what item is binded tp the specific shop ite
                imageToCreate = APUtils::shopItemsItem.at(0);
            } else if (item == APItem2) {
                 imageToCreate = APUtils::shopItemsItem.at(1);
            } else if (item == APItem3) {
                imageToCreate = APUtils::shopItemsItem.at(2);
            } else if (item == APItem4) {
                 imageToCreate = APUtils::shopItemsItem.at(3);
            } else if (item == APItem5) {
                 imageToCreate = APUtils::shopItemsItem.at(4);
            } else if (item == APItem6) {
                imageToCreate = APUtils::shopItemsItem.at(5);
            }
            auto imageName = APUtils::getImageForShopItem(imageToCreate);
            cocos2d::CCSprite* image;
            if (std::string_view(imageName) == "currencyOrbIcon_001.png" || std::string_view(imageName) == "GJ_diamondsIcon_001.png") {
                image = cocos2d::CCSprite::createWithSpriteFrameName(imageName);
            } else {
                image = cocos2d::CCSprite::create(imageName);
            }
            if (std::string_view(imageName) == "APLogo.png"_spr) {
                image->setScale(0.3f);
            } else if (std::string_view(imageName).contains("Unlock")) {
                image->setScale(0.4f);
            } else if (std::string_view(imageName) == "currencyOrbIcon_001.png" || std::string_view(imageName) == "GJ_diamondsIcon_001.png") {
                image->setScale(1.4f);
            }
                image->setPosition(CCPoint(17.f, 20.f)); 
            ret->getChildByID("main-layer")->getChildByID("icon")->addChild(image);
            auto text = ret->getChildByID("main-layer")->getChildByID("info-area")->getChildByType<MultilineBitmapFont>(0)->getChildByType<CCLabelBMFont>(0);
            text->setString(fmt::format("Do you want to buy this {}", imageToCreate).c_str());
            text->setScale(0.7f);
            for (auto i = 24; i < 24 + imageToCreate.length(); i++) { // color tags do not work here
                auto letter = text->getChildByType<cocos2d::CCFontSprite>(i);
                letter->setColor(ccORANGE);
            }
        }
        geode::log::debug("Finished PurchaseItemPopup::init()");
        return ret;
    }
};