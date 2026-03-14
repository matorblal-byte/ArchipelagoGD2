#pragma once

namespace APUtils {

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

    void recieveItem(int64_t id, bool notify);

    void clearItemState();

    void checkLocationCallback(int64_t id);

    void createNotification(std::string name, bool location);

    void sendItem(int64_t id);

    void deathLinkRecieved();

    bool checkPortal(int id);

    void getStartingLevels(std::string ids);

    void startArchipelago(const char* url, const char* slot, const char* pass);
}
