#include <Geode/Geode.hpp>
#include <Geode/modify/GJShopLayer.hpp>
#include "APUtils.hpp"

using namespace geode::prelude;

class $modify(GJAPShopLayer, GJShopLayer) {
    static CCScene* scene(ShopType type) {
        auto ret = GJShopLayer::scene(type);
        auto shopKeeperShop = GameStatsManager::sharedState()->shopTypeForItemID(1);
        if (APUtils::checkShopEnabled && type == shopKeeperShop) {
            // we have to use these unreliable methods because nodeids doesnt support the shop layer Yay! This took me so long to figure out bro this took like 7 hours to get these icons to be on the items
            // after boom scroll layer is extended layer -> extended layer 5th page -> ccmenu 5th page -> listbuttonshop
            auto gjsl = ret->getChildByType<GJShopLayer>(0);
            auto lbb = gjsl->getChildByType<ListButtonBar>(0);
            auto bsl = lbb->getChildByType<BoomScrollLayer>(0);
            auto el1 = bsl->getChildByIndex(0);
            auto el2 = el1->getChildByIndex(5);
            auto ccm1 = el1->getChildByIndex(5);
            auto lbs = ccm1->getChildByIndex(0);
            auto children = lbs->getChildren();
            for (int i = 0; i < children->count(); i++) {
                auto item = lbs->getChildByIndex(i); // get the ccmenuitemspriteextra

                item = item->getChildByIndex(0); // get thhe gjitemicon 
                if (item->getTag() == 1000) {
                    item->getChildByIndex(0)->removeFromParent();
                    auto archImage = CCSprite::create("APLogo.png"_spr);
                    archImage->setScale(0.3f);
                    archImage->setPosition(CCPoint(17.f, 20.f));
                    item->addChild(archImage);
                }
            }
        }
        return ret;
    }
};
