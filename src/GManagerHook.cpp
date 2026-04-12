#include <Geode/Geode.hpp>
#include <Geode/modify/GManager.hpp>
#include "APUtils.hpp"
using namespace geode::prelude;

class $modify(APGManager, GManager) {
    void setup() {
        geode::log::debug("Called GManager::setup()");
        if (APUtils::GManagerRan) { // gmanager runs twice i guess ???
            GManager::setup();
            return;
        }
        auto saves = geode::dirs::getSaveDir();
        if (std::filesystem::exists(saves / "inArchModeFlag.txt")) {
            std::error_code error;
            auto dir = dirs::getGameDir();
            if (!std::filesystem::exists(saves / "ArchGDBackupedSave")) {
                std::filesystem::create_directory(saves / "ArchGDBackupedSave", error);
            }
            auto normalSize = std::filesystem::file_size(saves / "CCGameManager.dat", error);
            std::filesystem::rename(saves / "CCGameManager.dat", saves / "CCGameManagerSaved.datSaved", error);
            std::filesystem::rename(saves / "CCLocalLevels.dat", saves / "CCLocalLevelsSaved.datSaved", error);
            if (std::filesystem::exists(saves / "CCGameManager2.dat") && std::filesystem::exists(saves / "CCLocalLevels2.dat")) {
                std::filesystem::rename(saves / "CCLocalLevels2.dat", saves / "CCLocalLevels2Saved.datSaved", error);
                std::filesystem::rename(saves / "CCGameManager2.dat", saves / "CCGameManager2Saved.datSaved", error);
            }
            if (error) {
                APUtils::errorMessage = fmt::format("Unable to rename save data. Error: {} Code: {}", error.message(), error.value());
                log::warn("Unable to rename save. Error: {} Code: {}", error.message(), error.value());
                std::filesystem::remove(saves / "inArchModeFlag.txt", error);
            }
            std::filesystem::copy_file(saves / "CCGameManagerSaved.datSaved", saves / "ArchGDBackupedSave" / "CCGameManager.dat", std::filesystem::copy_options::overwrite_existing, error);
            std::filesystem::copy_file(saves / "CCLocalLevelsSaved.datSaved", saves / "ArchGDBackupedSave" / "CCLocalLevels.dat", std::filesystem::copy_options::overwrite_existing, error);
            // backup the backups too
            if (std::filesystem::exists(saves / "CCGameManagerSaved2.datSaved") && std::filesystem::exists(saves / "CCLocalLevelsSaved2.datSaved")) {
            std::filesystem::copy_file(saves / "CCGameManager2Saved.datSaved", saves / "ArchGDBackupedSave" / "CCGameManager2.dat", std::filesystem::copy_options::overwrite_existing, error);
            std::filesystem::copy_file(saves / "CCLocalLevels2Saved.datSaved", saves / "ArchGDBackupedSave" / "CCLocalLevels2.dat", std::filesystem::copy_options::overwrite_existing, error);
            }
            std::filesystem::create_directory(saves / "inArchModeFlag.txt", error);
            if (error) {
                APUtils::errorMessage = fmt::format("Unable to backup your save data, Error: {} Code: {} Extra information printed to logs", error.message(), error.value());
                log::warn("Unable to copy file to ArchGDBackupedSave: Error: {} Code: {}", error.message(), error.value());
                if (!std::filesystem::exists(dirs::getSaveDir())) {
                    log::warn("The save directory is literally not existent.");
                }
                if (!std::filesystem::exists(dirs::getGameDir())) {
                    log::warn("The game directory is literally not existent.");
                }
                if (!std::filesystem::exists(saves / "ArchGDBackupedSave")) {
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
                std::filesystem::remove(saves / "inArchModeFlag.txt", error);
            }
                if (!std::filesystem::exists(saves / "inArchModeFlag.txt")) {
                    log::warn("Couldnt find the flag!!!!");
                }
            log::info("renaming files");
                // to be 100%%%%%%%%%%%%% safe 
                auto backupSize = std::filesystem::file_size(saves / "CCGameManagerSaved.datSaved", error);
                auto backup2Size = std::filesystem::file_size(saves / "ArchGDBackupedSave" / "CCGameManager.dat", error);
                if (normalSize == backupSize && normalSize == backup2Size) {
                    log::info("Backup success");
                } else {
                    // i would put an error message but 1 its too big to fit and 2 its the result of another error
                    // APUtils::errorMessage = fmt::format("The file size of your data and the backed up one is not the same: The normal save file size is {}, but the backup that was renamed size was {}, and the copied saved file size was {}.", normalSize, backupSize, backup2Size);
                    log::warn("The normal save file size is {}, but the backup that was renamed size was {}, and the copied saved file size was {}.", normalSize, backupSize, backup2Size);
                    std::filesystem::remove(saves / "inArchModeFlag.txt", error);
                }
                if (error) {
                    APUtils::errorMessage = fmt::format("couldnt confirm file sizes: Error: {} Code: {}", error.message(), error.value());
                    log::warn("couldnt confirm file sizes: Error: {} Code: {}", error.message(), error.value());
                    std::filesystem::remove(saves / "inArchModeFlag.txt", error);
                }  
        }
        if (std::filesystem::exists(saves / "ArchGDBackupedSave" / "CCGameManager.dat") && std::filesystem::exists(saves / "ArchGDBackupedSave" / "CCLocalLevels.dat") && !std::filesystem::exists(saves / "inArchModeFlag.txt") && Mod::get()->getSavedValue("LoadBackup", false)) {
            std::error_code error;
            if (std::filesystem::exists(saves / "CCGameManagerSaved.datSaved") && std::filesystem::exists(saves / "CCLocalLevelsSaved.datSaved")) {
                std::filesystem::rename(saves / "CCGameManagerSaved.datSaved", saves / "CCGameManager.dat", error);
                std::filesystem::rename(saves / "CCLocalLevelsSaved.datSaved", saves / "CCLocalLevels.dat", error);
                if (std::filesystem::exists(saves / "CCGameManagerSaved2.datSaved") && std::filesystem::exists(saves / "CCLocalLevelsSaved2.datSaved")) {
                std::filesystem::rename(saves / "CCGameManagerSaved2.datSaved", saves / "CCGameManager2.dat", error);
                std::filesystem::rename(saves / "CCLocalLevelsSaved2.datSaved", saves / "CCLocalLevels2.dat", error);
                }
            } else {
            std::filesystem::copy_file(saves / "ArchGDBackupedSave" / "CCGameManager.dat", saves / "CCGameManager.dat", std::filesystem::copy_options::overwrite_existing, error);
            std::filesystem::copy_file(saves / "ArchGDBackupedSave" / "CCLocalLevels.dat", saves / "CCLocalLevels.dat", std::filesystem::copy_options::overwrite_existing, error);
            if (std::filesystem::exists(saves / "ArchGDBackupedSave" / "CCGameManager2.dat") && std::filesystem::exists(saves / "ArchGDBackupedSave" / "CCLocalLevels2.dat")) {
            std::filesystem::copy_file(saves / "ArchGDBackupedSave" / "CCGameManager2.dat", saves / "CCGameManager2.dat", std::filesystem::copy_options::overwrite_existing, error);
            std::filesystem::copy_file(saves / "ArchGDBackupedSave" / "CCLocalLevels2.dat", saves / "CCLocalLevels2.dat", std::filesystem::copy_options::overwrite_existing, error);
            }
            }
            if (error) {
                auto message = fmt::format("Could not rename saves: Error {} Code: {}, backups saved in your gd folder! (where the application is)", error.message(), error.value());
                geode::log::warn("Could not rename saves: Error {} Code: {}, backups saved in your gd folder! (where the application is)", error.message(), error.value());
                APUtils::errorMessage = message;
            }
            Mod::get()->setSavedValue("LoadBackup", false);
            auto res = Mod::get()->saveData();
            if (!res.isOk()) {
                APUtils::errorMessage = fmt::format("Couldn't save mod data: {}", res.unwrapErr());
            }
        }
        APUtils::GManagerRan = true;
        geode::log::debug("Finished GManager::setup()");
        GManager::setup();
    }
};