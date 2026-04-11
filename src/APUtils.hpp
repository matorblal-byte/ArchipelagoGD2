#pragma once

namespace APUtils {

    extern std::string errorMessage; // used for errors before the main menu is up because them it will just crash

    extern int speed;

    extern int manaOrbsToAdd;
    extern int diamondsToAdd;

    extern bool inLoadingLayer;
    extern bool GManagerRan;
    extern bool coinsEnabled;
    extern bool coinLocksEnabled;
    extern bool ultimatesEnabled;
    extern bool checkShopEnabled;
    //extern bool modifiers;

    static std::vector<std::string> levels = {
        "Stereo Madness",
        "Back On Track",
        "Polargeist",
        "Dry Out",
        "Base After Base",
        "Cant Let Go",
        "Jumper",
        "Time Machine",
        "Cycles",
        "xStep",
        "Clutterfunk",
        "Theory of Everything",
        "Electroman Adventures",
        "Clubstep",
        "Electrodynamix",
        "Hexagon Force",
        "Blast Processing",
        "Theory of Everything 2",
        "Geometrical Dominator",
        "Deadlocked",
        "Fingerdash",
        "Dash",
        "The Tower",
        "The Sewers",
        "The Cellar",
        "The Secret Hollow",
    };

    static std::vector<std::string> shopItems = {
        "Check Shop #1",
        "Check Shop #2",
        "Check Shop #3",
        "Check Shop #4",
        "Check Shop #5",
        "Check Shop #6"
    };
    
    int checkIfTower(int id);

    void recieveItem(int64_t id, bool notify);

    void clearItemState();

    void checkLocationCallback(int64_t id);

    void createNotification(std::string name, bool location);

    void sendItem(int64_t id);

    void deathLinkRecieved();

    bool checkPortal(int id);

    void getStartingLevels(std::string ids);

    void setSpeed(int val);

    void setCoinsBool(int val);

    void setCoinLocksBool(int val);

    void setUltimatesBool(int val);

    void setCheckShopBool(int val);

    void goal();

    void startArchipelago(const char* url, const char* slot, const char* pass);
}