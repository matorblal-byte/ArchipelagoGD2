#include "APUtils.hpp"
#include "Archipelago.h"
#include "Geode/binding/PlayLayer.hpp"
#include "Geode/loader/Loader.hpp"
#include "Geode/loader/Log.hpp"

using namespace geode::prelude;

std::vector<std::string> items = {
    "Stereo Madness: Unlock",
    "Back On Track: Unlock",
    "Polargeist: Unlock",
    "Dry Out: Unlock",
    "Base After Base: Unlock",
    "Cant Let Go: Unlock",
    "Jumper: Unlock",
    "Time Machine: Unlock",
    "Cycles: Unlock",
    "xStep: Unlock",
    "Clutterfunk: Unlock",
    "Theory of Everything: Unlock",
    "Electroman Adventures: Unlock",
    "Clubstep: Unlock",
    "Electrodynamix: Unlock",
    "Hexagon Force: Unlock",
    "Blast Processing: Unlock",
    "Theory of Everything 2: Unlock",
    "Geometrical Dominator: Unlock",
    "Deadlocked: Unlock",
    "Fingerdash: Unlock",
    "Dash: Unlock",
    "The Tower: Unlock",
    "The Sewers: Unlock",
    "The Cellar: Unlock",
    "The Secret Hollow: Unlock",
    "Ship Portal",
    "Ball Portal",
    "UFO Portal",
    "Wave Portal",
    "Robot Portal",
    "Spider Portal",
    "Swing Portal",
    "100 Mana Orbs",
    "Secret Coin"
};

int gdBaseID = 130820130;
    // note to index staff: this is due to the way Archipelago itself works 
    // fun fact, this is the GD release date in DD/MM/YYYY and a 0

void APUtils::recieveItem(int64_t id, bool notify) {
    std::string itemToRecieve = items[id - gdBaseID];
    // orbs and coins are wip and have no real code
    /*
    if (itemToRecieve == "100 Mana Orbs") {
        AchievementNotifier::sharedState()->notifyAchievement("100 mana orvs", "mana orb", "GJ_lockGray_001.png", true);
    }
    else if (itemToRecieve == "Secret Coin") {
        AchievementNotifier::sharedState()->notifyAchievement("secret coin", "coiner", "GJ_lockGray_001.png", true);
    }
    */
        Mod::get()->setSavedValue<bool>(itemToRecieve, true);
        if (notify) {
                Loader::get()->queueInMainThread(
                    [itemToRecieve]{APUtils::createNotification(itemToRecieve, false);}
                );
        }
    }

void APUtils::clearItemState() {
    std::size_t itemAmount = items.size();
    for (std::size_t index = 0; index < itemAmount; ++index) {
        std::string itemToClear = items[index];
        Mod::get()->setSavedValue<bool>(itemToClear, false);
    }
    Mod::get()->setSavedValue<bool>("Cant Let Go: Unlock", false);
}

void APUtils::checkLocationCallback(int64_t id) {
    Loader::get()->queueInMainThread(
        []{APUtils::createNotification("ligma balls", true);}
    );
}

void APUtils::sendItem(int64_t id) {
    if (id < 23) {
        AP_SendItem(id + gdBaseID);
    } else {
        switch (id) {
            case 5001:
            geode::log::info("g");
        }
    }
};

void APUtils::createNotification(std::string name, bool location) {
    const char* title;
    std::string desc;
    if (location) {
        title = "Location checked!";
        desc = "You checked <cg>" + name + " </c>and sent an item.";
    } else {
        title = "Item recieved!";
        desc = "You have recieved <cg>" + name + "</c>.";
    }
    geode::log::info("{}", title);
    geode::log::info("{}", desc);
    geode::log::info("{}", name);
    geode::log::info("location = {}", location);
    AchievementNotifier::sharedState()->notifyAchievement(title, desc.c_str(), "APLogo.png"_spr, true);
}

void APUtils::deathLinkRecieved() {
    Loader::get()->queueInMainThread(
        []{
            if (PlayLayer* playLayer = GameManager::get()->getPlayLayer()) playLayer->destroyPlayer(playLayer->m_player1, nullptr);
            geode::log::info("deathlink received. time to die");
        }
    );
}

bool APUtils::checkPortal(int id) {
    switch (id) {
        default:
        return true;
        case 13:
        return Mod::get()->getSavedValue<bool>("Ship Portal", true);
        case 47:
        return Mod::get()->getSavedValue<bool>("Ball Portal", true);
        case 111:
        return Mod::get()->getSavedValue<bool>("UFO Portal", true);
        case 660:
        return Mod::get()->getSavedValue<bool>("Wave Portal", true);
        case 745:  
        return Mod::get()->getSavedValue<bool>("Robot Portal", true);
        case 1331:
        return Mod::get()->getSavedValue<bool>("Spider Portal", true);
        case 1933:
        return Mod::get()->getSavedValue<bool>("Swing Portal", true);
    }
}

void APUtils::getStartingLevels(std::string ids) {
    Loader::get()->queueInMainThread(
        [ids]{
    std::istringstream iss(ids);
    std::vector<std::string> levelIds((std::istream_iterator<std::string>(iss)),
    std::istream_iterator<std::string>());
    
    levelIds.pop_back(); // rem,ove rnadom "
    for (auto& id : levelIds) {
        if (id.contains("\"")) {
            size_t pos = id.find("\"");
            id.erase(pos, 1);
        }
        geode::log::info("got starting level {}", id);
        auto levelIntRes = geode::utils::numFromString<int>(id, 10);
        int levelInt = levelIntRes.unwrap();
        auto level = APUtils::levels.at(levelInt);
        geode::log::info("aka {}", level);
        Mod::get()->setSavedValue<bool>(level + ": Unlock", true);
    }
}
);
}

void APUtils::startArchipelago(const char *url, const char *slot, const char *pass) {
    auto values = Mod::get()->getSaveDir();
        for (auto& level : APUtils::levels) {
            if (Mod::get()->getSavedValue<bool>(level, true)) {
                Mod::get()->setSavedValue<bool>(level, false);
            }
        }
    AP_Init(url, "Geometry Dash", slot, pass);
    AP_SetItemClearCallback(&APUtils::clearItemState);
    AP_SetItemRecvCallback(&APUtils::recieveItem);
    AP_SetLocationCheckedCallback(&APUtils::checkLocationCallback);
    AP_SetDeathLinkSupported(true);
    AP_SetDeathLinkRecvCallback(&APUtils::deathLinkRecieved);
    AP_RegisterSlotDataRawCallback("startinglevels", &APUtils::getStartingLevels);
    AP_Start();
}
