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
    //"Ship Portal",
    "Ball Portal",
    "UFO Portal",
    "Wave Portal",
    "Robot Portal",
    "Spider Portal",
    "Swing Portal",
    "100 Mana Orbs",
    "5 Diamonds"
};

std::vector<std::string> APUtils::shopItemsItem = {
        "None",
        "None",
        "None",
        "None",
        "None",
        "None"
    };

std::string APUtils::errorMessage = "";

int gdBaseID = 130820130;
    // note to index staff: this is due to the way Archipelago itself works 
    // fun fact, this is the GD release date in DD/MM/YYYY and a 0

int APUtils::speed = 100;

int APUtils::manaOrbsToAdd = 0;
int APUtils::diamondsToAdd = 0;

bool APUtils::inLoadingLayer = true;
bool APUtils::GManagerRan = false;

bool APUtils::coinsEnabled = true;
bool APUtils::coinLocksEnabled = true;
bool APUtils::ultimatesEnabled = false;
bool APUtils::checkShopEnabled = true;

int APUtils::checkIfTower(int id) {
    switch (id) {
        case 5001:
            return 23; // The Tower
        case 5002:
            return 24; // The Sewers
        case 5003:
            return 25; // The Cellar
        case 5004:
            return 26; // The Secret Hollow
        default:
            return id;
        }
    }
void APUtils::recieveItem(int64_t id, bool notify) {
    geode::log::debug("Called APUtils::recieveItem()");
    std::string itemToRecieve = items[id - gdBaseID];
    if (itemToRecieve == "100 Mana Orbs") {
        if (APUtils::inLoadingLayer) {
            APUtils::manaOrbsToAdd += 100; // buffering the addition of mana orbs cuz it will crash
            geode::log::info("{} orbs", APUtils::manaOrbsToAdd);
        } else {
            GameStatsManager::sharedState()->incrementStat("14", 100);
        }
        Loader::get()->queueInMainThread(
        []{APUtils::createNotification("100 Mana Orbs", false);}
    );
        geode::log::debug("Finished APUtils::recieveItem()");
        return;
    }
    else if (itemToRecieve == "5 Diamonds") {
        if (APUtils::inLoadingLayer) {
            APUtils::diamondsToAdd += 5;
            geode::log::info("{} diamonds", APUtils::diamondsToAdd);
        } else {
            GameStatsManager::sharedState()->incrementStat("13", 5);
        }
        Loader::get()->queueInMainThread(
        []{APUtils::createNotification("5 Diamonds", false);}
    );
        geode::log::debug("Finished APUtils::recieveItem()");
        return;
    }
        Mod::get()->setSavedValue<bool>(itemToRecieve, true);
        if (notify) {
                Loader::get()->queueInMainThread(
                    [itemToRecieve]{APUtils::createNotification(itemToRecieve, false);}
                );
        }
        geode::log::debug("Finished APUtils::recieveItem()");
    }

void APUtils::clearItemState() {
    geode::log::debug("Called APUtils::clearItemState()");
    std::size_t itemAmount = items.size();
    for (std::size_t index = 0; index < itemAmount; ++index) {
        std::string itemToClear = items[index];
        Mod::get()->setSavedValue<bool>(itemToClear, false);
    }
    geode::log::debug("Finished APUtils::clearItemState()");
}

void APUtils::checkLocationCallback(int64_t id) {
    geode::log::debug("Called APUtils::checkLocationCallback");
    id -= gdBaseID;
    if (id >= 1000) {
        auto coinNum = id % 1000;
        id -= coinNum;
        id /= 1000;
        id -= 1;
        if (id > APUtils::levels.size() || id < 0) {
            geode::log::warn("The id of {} was not in the levels vector!", id);
            return;
        }
        auto levelName = APUtils::levels.at(id);
        geode::log::info("checked location {}, coin number {}", levelName, coinNum);
        levelName += " - Coin " + geode::utils::numToString(coinNum);
        Loader::get()->queueInMainThread(
        [levelName]{APUtils::createNotification(levelName, true);}
    );
    } else {
        if (id > 99) {
            if (id > APUtils::shopItems.size() || id < 0) {
                geode::log::warn("The id of {} was not in the shopItems vector!", id);
                return;
            }
            auto locationChecked = APUtils::shopItems.at(id - 100);
            Loader::get()->queueInMainThread(
            [locationChecked]{APUtils::createNotification(locationChecked, true);}
        );
        geode::log::debug("Finished APUtils::checkLocationCallback()");
        return;
        }
    }
    if (id < 99) {
        if (id > APUtils::levels.size() || id < 0) {
            geode::log::warn("The id of {} was not in the levels vector!", id);
            return;
        }
        auto locationChecked = APUtils::levels.at(id);
        Loader::get()->queueInMainThread(
            [locationChecked]{APUtils::createNotification(locationChecked, true);}
        );
    }
    geode::log::debug("Finished APUtils::checkLocationCallback()");
}


void APUtils::sendItem(int64_t id) {
    if (id >= 1000) {
        AP_SendItem(id);
        return;
    } else {
        if (id < 128) {
            AP_SendItem(id + gdBaseID);
        } else {
            switch (id) {
                case 5001:
                geode::log::info("g");
            }
        }
}
};

void APUtils::createNotification(std::string name, bool location) {
    if (APUtils::inLoadingLayer) return;
    geode::log::debug("Called APUtils::createNotification()");
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
    geode::log::debug("Finished APUtils::createNotification()");
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
    if (!coinsEnabled) return true;
    switch (id) {
        default:
        return true;
        case 13:
        //return Mod::get()->getSavedValue<bool>("Ship Portal", true);
        return true;
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
    geode::log::debug("Called APUtils::getStartingLevels()");
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
        levelInt = checkIfTower(levelInt);
        auto level = APUtils::levels.at(levelInt);
        geode::log::info("aka {}", level);
        Mod::get()->setSavedValue<bool>(level + ": Unlock", true);
        geode::log::debug("Finished APUtils::getStartingLevels()");
    }
}
);
}

void APUtils::goal() {
    AP_StoryComplete();
}
void APUtils::setSpeed(int val) {
    APUtils::speed = val;
}

void APUtils::setCoinsBool(int val) {
    if (val == 0) {
      APUtils::coinsEnabled = false;  
    } else {
      APUtils::coinsEnabled = true;
    }
}

void APUtils::setUltimatesBool(int val) {
    errorMessage = "Your APWorld is outdated. (Ultimates value passed)"; // had to be brief because text to  big
    if (val == 0) {
      APUtils::ultimatesEnabled = false;  
    } else {
      APUtils::ultimatesEnabled = true;
    }
}

void APUtils::setCoinLocksBool(int val) {
    if (val == 0) {
      APUtils::coinLocksEnabled = false;  
    } else {
      APUtils::coinLocksEnabled = true;
    }
}

void APUtils::setCheckShopBool(int val) {
    if (val == 0) {
      APUtils::checkShopEnabled = false;  
    } else {
      APUtils::checkShopEnabled = true;
    }
}

void APUtils::setShop1Item(std::string item) { // set what item is binded to the shop item if that makes sense - same goes for the next functions below
    // remove both quotation marks in the item name
    item = item.erase(item.find("\""), 1);
    item = item.erase(item.find("\""), 1);
    if (item.contains("\n")) {
        item.pop_back(); // WHY is there a new line
    }
    APUtils::shopItemsItem.at(0) = item;
}

void APUtils::setShop2Item(std::string item) {
    item = item.erase(item.find("\""), 1);
    item = item.erase(item.find("\""), 1);
    if (item.contains("\n")) {
        item.pop_back();
    }
    APUtils::shopItemsItem.at(1) = item;
}

void APUtils::setShop3Item(std::string item) {
    item = item.erase(item.find("\""), 1);
    item = item.erase(item.find("\""), 1);
    if (item.contains("\n")) {
        item.pop_back();
    }
    APUtils::shopItemsItem.at(2) = item;
}

void APUtils::setShop4Item(std::string item) {
    item = item.erase(item.find("\""), 1);
    item = item.erase(item.find("\""), 1);
    if (item.contains("\n")) {
        item.pop_back();
    }
    APUtils::shopItemsItem.at(3) = item;
}

void APUtils::setShop5Item(std::string item) {
    item = item.erase(item.find("\""), 1);
    item = item.erase(item.find("\""), 1);
    if (item.contains("\n")) {
        item.pop_back();
    }
    APUtils::shopItemsItem.at(4) = item;
}

void APUtils::setShop6Item(std::string item) {
    item = item.erase(item.find("\""), 1);
    item = item.erase(item.find("\""), 1);
    if (item.contains("\n")) {
        item.pop_back();
    }
    APUtils::shopItemsItem.at(5) = item;
}

const char* APUtils::getImageForShopItem(std::string item) { // there has GOTTA be a easier way to do ts
    if (item == "Ball Portal") {
        return "ballUnlock.png"_spr;
    } else if (item == "UFO Portal") {
        return "ufoUnlock.png"_spr;
    } else if (item == "Wave Portal") {
        return "waveUnlock.png"_spr;
    } else if (item == "Robot Portal") {
        return "robotUnlock.png"_spr;
    } else if (item == "Spider Portal") {
        return "spiderUnlock.png"_spr;
    } else if (item == "Swing Portal") {
        return "swingUnlock.png"_spr;
    } else if (item == "Stereo Madness: Unlock") {
        return "stereoUnlock.png"_spr;
    } else if (item == "Back On Track: Unlock") {
        return "backOnTrackUnlock.png"_spr;
    } else if (item == "Polargeist: Unlock") {
        return "polargeistUnlock.png"_spr;
    } else if (item == "Dry Out: Unlock") {
        return "dryOutUnlock.png"_spr;
    } else if (item == "Base After Base: Unlock") {
        return "baseAfterBaseUnlock.png"_spr;
    } else if (item == "Cant Let Go: Unlock") {
        return "cantLetGoUnlock.png"_spr;
    } else if (item == "Jumper: Unlock") {
        return "jumperUnlock.png"_spr;
    } else if (item == "Time Machine: Unlock") {
        return "timeMachineUnlock.png"_spr;
    } else if (item == "Cycles: Unlock") {
        return "cyclesUnlock.png"_spr;
    } else if (item == "xStep: Unlock") {
        return "xStepUnlock.png"_spr;
    } else if (item == "Clutterfunk: Unlock") {
        return "clutterfunkUnlock.png"_spr;
    } else if (item == "Theory of Everything: Unlock") {
        return "toeUnlock.png"_spr;
    } else if (item == "Electroman Adventures: Unlock") {
        return "electromanAdventuresUnlock.png"_spr;
    } else if (item == "Clubstep: Unlock") {
        return "clubstepUnlock.png"_spr;
    } else if (item == "Electrodynamix: Unlock") {
        return "electrodynamixUnlock.png"_spr;
    } else if (item == "Hexagon Force: Unlock") {
        return "hexagonForceUnlock.png"_spr;
    } else if (item == "Blast Processing: Unlock") {
        return "blastProcessingUnlock.png"_spr;
    } else if (item == "Theory of Everything 2: Unlock") {
        return "toe2Unlock.png"_spr;
    } else if (item == "Geometrical Dominator: Unlock") {
        return "geometricalDominatorUnlock.png"_spr;
    } else if (item == "Deadlocked: Unlock") {
        return "deadlockedUnlock.png"_spr;
    } else if (item == "Fingerdash: Unlock") {
        return "fingerdashUnlock.png"_spr;
    } else if (item == "Dash: Unlock") {
        return "dashUnlock.png"_spr;
    } else if (item == "The Tower: Unlock") {
        return "theTowerUnlock.png"_spr;
    } else if (item == "The Sewers: Unlock") {
        return "theSewersUnlock.png"_spr;
    } else if (item == "The Cellar: Unlock") {
        return "theCellarUnlock.png"_spr;
    } else if (item == "The Secret Hollow: Unlock") {
        return "theSecretHollowUnlock.png"_spr;
    } else if (item == "100 Mana Orbs") {
        return "currencyOrbIcon_001.png";
    } else if (item == "5 Diamonds") {
        return "GJ_diamondsIcon_001.png";
    } else {
        return "APLogo.png"_spr;
    }
}

void APUtils::startArchipelago(const char *url, const char *slot, const char *pass) {
    geode::log::debug("Called APUtils::startArchipelago()");
        for (auto& level : APUtils::levels) {
            if (Mod::get()->getSavedValue<bool>(level + ": Unlock", true)) {
                Mod::get()->setSavedValue<bool>(level + ": Unlock", false);
            }
        }
    AP_Init(url, "Geometry Dash", slot, pass);
    AP_SetItemClearCallback(&APUtils::clearItemState);
    AP_SetItemRecvCallback(&APUtils::recieveItem);
    AP_SetLocationCheckedCallback(&APUtils::checkLocationCallback);
    AP_SetDeathLinkSupported(true);
    AP_SetDeathLinkRecvCallback(&APUtils::deathLinkRecieved);
    AP_RegisterSlotDataRawCallback("startinglevels", &APUtils::getStartingLevels);
    AP_RegisterSlotDataIntCallback("speed", &APUtils::setSpeed);
    AP_RegisterSlotDataIntCallback("coins", &APUtils::setCoinsBool);
    AP_RegisterSlotDataIntCallback("coin_locks", &APUtils::setCoinLocksBool);
    AP_RegisterSlotDataIntCallback("ultimate", &APUtils::setUltimatesBool);
    AP_RegisterSlotDataRawCallback("shop_item1", &APUtils::setShop1Item);
    AP_RegisterSlotDataRawCallback("shop_item2", &APUtils::setShop2Item);
    AP_RegisterSlotDataRawCallback("shop_item3", &APUtils::setShop3Item);
    AP_RegisterSlotDataRawCallback("shop_item4", &APUtils::setShop4Item);
    AP_RegisterSlotDataRawCallback("shop_item5", &APUtils::setShop5Item);
    AP_RegisterSlotDataRawCallback("shop_item6", &APUtils::setShop6Item);
    AP_Start();
    geode::log::debug("Finished APUtils::startArchipelago()");
}
