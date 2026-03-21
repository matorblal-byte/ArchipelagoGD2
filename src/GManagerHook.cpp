#include <Geode/Geode.hpp>
#include <Geode/modify/GManager.hpp>

using namespace geode::prelude;

class $modify(APGManager, GManager) {
    void setup() {
        auto saves = geode::dirs::getSaveDir();
        if (std::filesystem::exists(saves / "CCGameManagerSaved.dat") && std::filesystem::exists(saves / "CCLocalLevelsSaved.dat") && !std::filesystem::exists(saves / "inArchModeFlag.txt")) {
            std::error_code error;
            std::filesystem::rename(saves / "CCLocalLevelsSaved.dat", saves / "CCLocalLevels.dat", error);
            std::filesystem::rename(saves / "CCLocalLevelsSaved2.dat", saves / "CCLocalLevels2.dat", error);
            std::filesystem::rename(saves / "CCGameManagerSaved.dat", saves / "CCGameManger.dat", error);
            std::filesystem::rename(saves / "CCGameManagerSaved2.dat", saves / "CCGameManger2.dat", error);
            if (error) {
                geode::log::warn("Could not rename saves: Error {} Code: {}, backups saved in your gd folder! (where the application is)", error.message(), error.value());
            }
        }
        if (std::filesystem::exists(saves / "inArchModeFlag.txt")) {
            std::filesystem::remove(saves / "inArchModeFlag.txt");
        }
        GManager::setup();
    }
};