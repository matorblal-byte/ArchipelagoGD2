#include <Geode/Geode.hpp>
#include <Geode/modify/GManager.hpp>

using namespace geode::prelude;

class $modify(APGManager, GManager) {
    void setup() {
        auto saves = geode::dirs::getSaveDir();
        if (std::filesystem::exists(saves / "CCGameManagerSaved.datSaved") && std::filesystem::exists(saves / "CCLocalLevelsSaved.datSaved") && !std::filesystem::exists(saves / "inArchModeFlag.txt")) {
            std::error_code error;
            std::filesystem::rename(saves / "CCLocalLevelsSaved.datSaved", saves / "CCLocalLevels.dat", error);
            std::filesystem::rename(saves / "CCLocalLevels2Saved.datSaved", saves / "CCLocalLevels2.dat", error);
            std::filesystem::rename(saves / "CCGameManagerSaved.datSaved", saves / "CCGameManager.dat", error);
            std::filesystem::rename(saves / "CCGameManager2Saved.datSaved", saves / "CCGameManager2.dat", error);
            if (error) {
                geode::log::warn("Could not rename saves: Error {} Code: {}, backups saved in your gd folder! (where the application is)", error.message(), error.value());
            }
        }
        GManager::setup();
    }
};