#include <Geode/Geode.hpp>
#include <Geode/modify/GManager.hpp>

using namespace geode::prelude;

class $modify(APGManager, GManager) {
    void setup() {
        auto saves = geode::dirs::getSaveDir();
        if (std::filesystem::exists(saves / "CCGameManager.datSaved") && std::filesystem::exists(saves / "CCLocalLevels.datSaved") && !std::filesystem::exists(saves / "inArchModeFlag.txt")) {
            std::error_code error;
            std::filesystem::rename(saves / "CCLocalLevels.datSaved", saves / "CCLocalLevels.dat", error);
            std::filesystem::rename(saves / "CCLocalLevels2.datSaved", saves / "CCLocalLevels2.dat", error);
            std::filesystem::rename(saves / "CCGameManager.datSaved", saves / "CCGameManager.dat", error);
            std::filesystem::rename(saves / "CCGameManager2.datSaved", saves / "CCGameManager2.dat", error);
            if (error) {
                geode::log::warn("Could not rename saves: Error {} Code: {}, backups saved in your gd folder! (where the application is)", error.message(), error.value());
            }
        }
        GManager::setup();
    }
};