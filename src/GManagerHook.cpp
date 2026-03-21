#include <Geode/Geode.hpp>
#include <Geode/modify/GManager.hpp>

using namespace geode::prelude;

class $modify(APGManager, GManager) {
    void setup() {
        auto saves = geode::dirs::getSaveDir();
        if (std::filesystem::exists(saves / "ArchGDBackupedSave" / "CCGameManager.dat") && std::filesystem::exists(saves / "ArchGDBackupedSave" / "CCLocalLevels.dat") && !std::filesystem::exists(saves / "inArchModeFlag.txt")) {
            std::error_code error;
            std::filesystem::copy_file(saves / "ArchGDBackupedSave" / "CCGameManager.dat", saves / "CCGameManager.dat", std::filesystem::copy_options::overwrite_existing, error);
            std::filesystem::copy_file(saves / "ArchGDBackupedSave" / "CCGameManager.dat", saves / "CCLocalLevels.dat", std::filesystem::copy_options::overwrite_existing, error);
            std::filesystem::copy_file(saves / "ArchGDBackupedSave" / "CCGameManager2.dat", saves / "CCGameManager2.dat", std::filesystem::copy_options::overwrite_existing, error);
            std::filesystem::copy_file(saves / "ArchGDBackupedSave" / "CCGameManager2.dat", saves / "CCLocalLevels2.dat", std::filesystem::copy_options::overwrite_existing, error);
            if (error) {
                geode::log::warn("Could not rename saves: Error {} Code: {}, backups saved in your gd folder! (where the application is)", error.message(), error.value());
            }
        }
        GManager::setup();
    }
};