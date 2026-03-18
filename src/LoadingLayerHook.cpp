#include "Geode/binding/LoadingLayer.hpp"
#include "Geode/cocos/CCDirector.h"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include <Geode/modify/LoadingLayer.hpp>
#include <Geode/loader/Dirs.hpp>
#include "APUtils.hpp"
#include <Archipelago.h>

using namespace geode::prelude;

class $modify(APLoadingLayer, LoadingLayer) {
    bool init(bool p0) {
        std::error_code error;
        auto saves = dirs::getSaveDir();
        auto dir = dirs::getGameDir();
        if (!LoadingLayer::init(p0)) return false;
        if (std::filesystem::exists(dir / "ArchGDBackupedSave" / "inArchModeFlag.archgd")) {
            auto url = Mod::get()->getSavedValue<std::string>("recent-url", "");
            APUtils::startArchipelago(url.c_str(), Mod::get()->getSavedValue<std::string>("recent-slot", "").c_str(), Mod::get()->getSavedValue<std::string>("recent-pass", "").c_str());
            auto apLabel = CCLabelBMFont::create(("ArchipelagoGD: Connecting to " + url).c_str(), "goldFont.fnt");
            apLabel->setPosition(CCDirector::get()->getWinSize().width / 2, CCDirector::get()->getWinSize().height - 10);
            apLabel->setScale(.45f);
            apLabel->setID("ap-status-label"_spr);
            this->addChild(apLabel);
            std::filesystem::remove(dir / "ArchGDBackupedSave" / "inArchModeFlag.archgd", error);
            if (error) {
                FLAlertLayer::create("Error", "Unable to remove arch mode flag! Logs for more info", "Ok")->show();
                log::warn("Unable to restore save data: Error: {} Code: {}", error.message(), error.value());        
            }
        } else {
            if (std::filesystem::exists(dir / "ArchGDBackupedSave" / "inArchModeFlag.archgd")) {
            std::filesystem::copy_file(dir / "ArchGDBackupedSave" / "CCGameManager.dat", saves / "CCGameManager.dat", std::filesystem::copy_options::overwrite_existing, error);
            std::filesystem::copy_file(dir / "ArchGDBackupedSave" / "CCLocalLevels.dat", saves / "CCLocalLevels.dat", std::filesystem::copy_options::overwrite_existing, error);
            std::filesystem::copy_file(dir / "ArchGDBackupedSave" / "CCGameManager2.dat", saves / "CCGameManager2.dat", std::filesystem::copy_options::overwrite_existing, error);
            std::filesystem::copy_file(dir / "ArchGDBackupedSave" / "CCLocalLevels2.dat", saves / "CCLocalLevels2.dat", std::filesystem::copy_options::overwrite_existing, error);;
            if (error) {
                FLAlertLayer::create("Error", "Unable to load your save data! Please retrieve it manually!! Error logs in logs", "Ok")->show();
                log::warn("Unable to restore save data: Error: {} Code: {}", error.message(), error.value());        
            }
            }
            auto apLabel = CCLabelBMFont::create("ArchipelagoGD: Not connected", "goldFont.fnt");
            apLabel->setPosition(CCDirector::get()->getWinSize().width / 2, CCDirector::get()->getWinSize().height - 10);
            apLabel->setScale(.45f);
            apLabel->setID("ap-status-label"_spr);
            this->addChild(apLabel);
        }

        return true;
    }
};