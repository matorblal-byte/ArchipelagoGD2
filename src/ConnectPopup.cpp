#include "ConnectPopup.h"
#include <Geode/binding/ButtonSprite.hpp>
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>
#include <Geode/binding/FLAlertLayer.hpp>
#include <Geode/loader/Dirs.hpp>
#include <Geode/cocos/cocoa/CCObject.h>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/TextInput.hpp>
#include <Geode/loader/ModSettingsManager.hpp>
#include <fmt/core.h>
#include <string>
#include <wincrypt.h>
#include <Archipelago.h>
#include "APUtils.hpp"

using namespace geode::prelude; 
class ConnectPopup : public Popup {
    protected:

bool init() {
    auto const layerSize = CCSize { 346.f, 280.f };
    
    if (!Popup::init(layerSize)) {
        return false;
    }
    m_noElasticity = true;
    //this->setTitle("Connect to Archipelago");

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto const layerPos = (winSize - layerSize) / 2;
    urlInput = TextInput::create(260, "archipelago.gg:12345", "chatFont.fnt");
    slotInput = TextInput::create(260, "1257Plays", "chatFont.fnt");
    passInput = TextInput::create(260, "topsecretpassword", "chatFont.fnt");
    urlInput->setFilter("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.:;*/");
    urlInput->setString(Mod::get()->getSavedValue<std::string>("recent-url", ""));

    slotInput->setFilter("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-_;:/?!.,[]{}/=+* ");
    slotInput->setString(Mod::get()->getSavedValue<std::string>("recent-slot", ""));

    passInput->setFilter("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-_;:/?!.,[]{}/=+* ");
    passInput->setString(Mod::get()->getSavedValue<std::string>("recent-pass", ""));
    
    auto urlLabel = CCLabelBMFont::create("Archipelago URL", "bigFont.fnt");
    auto slotLabel = CCLabelBMFont::create("Slot Name", "bigFont.fnt");
    auto passLabel = CCLabelBMFont::create("Password (if not set, leave empty)", "bigFont.fnt");
    urlLabel->setScale(.5f);
    urlLabel->setPosition(0.f, 85.f);
    urlInput->setPosition(0.f, urlLabel->getPositionY()-25.f);

    slotLabel->setScale(.5f);
    slotLabel->setPosition(0.f, 25.f);
    slotInput->setPosition(0.f, slotLabel->getPositionY()-25.f);

    passLabel->setScale(.5f);
    passLabel->setPosition(0.f, -35.f);
    passInput->setPosition(0.f, passLabel->getPositionY()-25.f);

    auto menu = CCMenu::create();
    auto connectButton = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Connect"),
        this,
        menu_selector(ConnectPopup::onClick)
    );
    connectButton->setPosition(0.f, -105.f);
    menu->addChild(urlInput);
    menu->addChild(slotInput);
    menu->addChild(passInput);
    menu->addChild(urlLabel);
    menu->addChild(slotLabel);
    menu->addChild(passLabel);
    menu->addChild(connectButton);
    this->addChild(menu);

    return true;
}
    TextInput* urlInput;
    TextInput* slotInput;
    TextInput* passInput;

public:
void onClick(CCObject* sender) {
    log::info("Clicked connect");
    geode::createQuickPopup(
        "Connect",
        "Are you sure you want to connect to Archipelago? When you agree to this, your game will restart into Archipelago mode. This will <cr>RESET YOUR GAME</c> (including settings) and back your save data up locally. You might want to save on the cloud. To leave Archipelago mode, open this menu when connected and choose <cr>\"Disconnect\".</c>\n<cg>Server:</c> " + urlInput->getString() + "\n<cb>Slot</c>: " + slotInput->getString(),
        "No", "Yes",
        [this](auto, bool btn2) { 
            if (btn2) {
                std::error_code error;
                std::string url = urlInput->getString();
                std::string slot = slotInput->getString();
                std::string pass = passInput->getString();
                Mod::get()->setSavedValue<std::string>("recent-url", url);
                Mod::get()->setSavedValue<std::string>("recent-slot", slot);
                Mod::get()->setSavedValue<std::string>("recent-pass", pass);
                Mod::get()->saveData();
                auto saves = dirs::getSaveDir();
                auto dir = dirs::getGameDir();
                if (!std::filesystem::exists(dir / "ArchGDBackupedSave")) {
                    std::filesystem::create_directory(dir / "ArchGDBackupedSave", error);
                }
                /*
                std::filesystem::copy_file(saves / "CCGameManager.dat", dir / "ArchGDBackupedSave" / "CCGameManager.dat", std::filesystem::copy_options::overwrite_existing, error);
                std::filesystem::copy_file(saves / "CCLocalLevels.dat", dir / "ArchGDBackupedSave" / "CCLocalLevels.dat", std::filesystem::copy_options::overwrite_existing, error);
                // backup the backups too
                std::filesystem::copy_file(saves / "CCGameManager2.dat", dir / "ArchGDBackupedSave" / "CCGameManager2.dat", std::filesystem::copy_options::overwrite_existing, error);
                std::filesystem::copy_file(saves / "CCLocalLevels2.dat", dir / "ArchGDBackupedSave" / "CCLocalLevels2.dat", std::filesystem::copy_options::overwrite_existing, error);
                */
                std::filesystem::create_directory(saves / "ArchGDBackupedSave" / "inArchModeFlag.txt", error);
                if (error) {
                    FLAlertLayer::create("Error", "Unable to backup your save data, errors printed to logs please check that!", "Ok")->show();
                    log::warn("Unable to copy file to ArchGDBackedupSave: Error: {} Code: {}", error.message(), error.value());
                    if (!std::filesystem::exists(dirs::getSaveDir())) {
                        log::warn("The save directory is literally not existent.");
                    }
                    if (!std::filesystem::exists(dirs::getGameDir())) {
                        log::warn("The game directory is literally not existent.");
                    }
                    if (!std::filesystem::exists(dir / "ArchGDBackupedSave")) {
                        log::warn("The backup dir is literally not existent.");
                    }
                    if (!std::filesystem::exists(saves / "CCGameManager.dat")) {
                        log::warn("The save file is literally not existent.");
                    }
                    if (!std::filesystem::exists(saves / "CCGameManager2.dat")) {
                        log::warn("The backup save file is literally not existent.");
                    }
                    if (!std::filesystem::exists(saves / "CCLocalLevels.dat")) {
                        log::warn("The level file is literally not existent.");
                    }
                    if (!std::filesystem::exists(saves / "CCLocalLevels.dat")) {
                        log::warn("The backup level file is literally not existent.");
                    }
                    return;
                }
                if (!std::filesystem::exists(saves / "ArchGDBackupedSave" / "inArchModeFlag.txt")) {

                    log::warn("Couldnt find the flag!!!!");
                    return;
                }
                log::info("renaming files");
                std::filesystem::rename(saves / "CCGameManager.dat", saves / "CCGameManagerSaved.dat", error);
                std::filesystem::rename(saves / "CCLocalLevels.dat", saves / "CCLocalLevelsSaved.dat", error);
                std::filesystem::rename(saves / "CCLocalLevels2.dat", saves / "CCLocalLevelsSaved2.dat", error);
                std::filesystem::rename(saves / "CCGameManager2.dat", saves / "CCGameManagerSaved2.dat", error);
                if (error) {
                    FLAlertLayer::create("Error", "Unable to rename save data. Please check the logs for errors!", "Ok")->show();
                    log::warn("Unable to rename save. Error: {} Code: {}", error.message(), error.value());
                    return;
                }
                geode::utils::game::restart(false);
                /*
                APUtils::startArchipelago(url.c_str(), slot.c_str(), pass.c_str());
                log::info("Connected to AP with url {}, slot {}, pass {}", url, slot, pass);
                */
            }
        }
     );
}

static ConnectPopup* create() {
    auto* ret = new ConnectPopup();

   
    if (ret && ret->init()) {
        ret->autorelease();   
    } else {
        CC_SAFE_DELETE(ret);
    }

    return ret;
};
};