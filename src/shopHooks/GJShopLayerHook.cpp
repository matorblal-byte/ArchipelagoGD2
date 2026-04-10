#include <Geode/Geode.hpp>
#include <Geode/modify/GJShopLayer.hpp>
#include "../APUtils.hpp"

using namespace geode::prelude;

class $modify(GJAPShopLayer, GJShopLayer) {
    static CCScene* scene(ShopType type) {
        auto ret = GJShopLayer::scene(type);
        geode::log::debug("Called GJShopLayer::scene()");
        auto shopKeeperShop = GameStatsManager::sharedState()->shopTypeForItemID(1);
        if (APUtils::checkShopEnabled && type == shopKeeperShop) {
            // we have to use these unreliable methods because nodeids doesnt support the shop layer Yay!
            auto gjsl = ret->getChildByType<GJShopLayer>(0);
            if (!gjsl) {
                log::error("Couldn't find the GJShopLayer!");
                FLAlertLayer::create("Error", "The GJShopLayer couldn't be found icons will not work correctly", "Ok")->show();
                return ret;
            }
            auto lbb = gjsl->getChildByType<ListButtonBar>(0);
            if (!lbb) {
                log::error("Couldn't find the ListButtonBar!");
                FLAlertLayer::create("Error", "The ListButtonBar couldn't be found icons will not work correctly", "Ok")->show();
                return ret;
            }
            lbb->setID("ListButtonBar");
            auto bsl = lbb->getChildByType<BoomScrollLayer>(0);
            if (!bsl) {
                log::error("Couldn't find the BoomScrollLayer!");
                FLAlertLayer::create("Error", "The BoomScrollLayer couldn't be found icons will not work correctly", "Ok")->show();
                return ret;
            }
            bsl->setID("BoomScrollLayer");
            auto el = bsl->getChildByType<ExtendedLayer>(0);
            if (!el) {
                log::error("Couldn't find the ExtendedLayer!");
                FLAlertLayer::create("Error", "The ExtendedLayer couldn't be found icons will not work correctly", "Ok")->show();
                return ret;
            }
            el->setID("ExtendedLayer");
            auto lbp5 = el->getChildByType<ListButtonPage>(5);
            if (!lbp5) {
                log::error("Couldn't find the 5th ListButtonPage!");
                FLAlertLayer::create("Error", "The 5th ListButtonPage couldn't be found icons will not work correctly", "Ok")->show();
                return ret;
            }
            // add node ids for all the pages for shopkeeper
            el->getChildByType<ListButtonPage>(0)->setID("ShopPage0");
            el->getChildByType<ListButtonPage>(1)->setID("ShopPage1");
            el->getChildByType<ListButtonPage>(2)->setID("ShopPage2");
            el->getChildByType<ListButtonPage>(3)->setID("ShopPage3");
            el->getChildByType<ListButtonPage>(4)->setID("ShopPage4");
            lbp5->setID("ShopPage5");
            auto ccm = lbp5->getChildByIndex<cocos2d::CCMenu>(0);
            if (!ccm) {
                log::error("Couldn't find the CCMenu!");
                FLAlertLayer::create("Error", "The CCMenu couldn't be found icons will not work correctly", "Ok")->show();
                return ret;                
            }
            auto children = ccm->getChildren();
            for (int i = 0; i < children->count(); i++) {
                auto item = ccm->getChildByType<CCMenuItemSpriteExtra>(i); // get the ccmenuitemspriteextra
                auto itemico = item->getChildByType<GJItemIcon>(0); // get thhe gjitemicon 
                if (itemico->getTag() == 1000) {
                    itemico->getChildByIndex(0)->removeFromParent();
                    auto archImage = CCSprite::create("APLogo.png"_spr);
                    archImage->setScale(0.3f);
                    archImage->setPosition(CCPoint(17.f, 20.f));
                    itemico->addChild(archImage);
                    // make index order correct
                    auto ccspr = itemico->getChildByType<CCSprite>(0);
                    auto cclbmf = itemico->getChildByType<CCLabelBMFont>(0);
                    ccspr->removeFromParent();
                    cclbmf->removeFromParent();
                    itemico->addChild(cclbmf);
                    itemico->addChild(ccspr);
                }
            }
        }
        geode::log::debug("Finished GJShopLayer::scene()");
        return ret;
    }
};
