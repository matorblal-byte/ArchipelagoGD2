#pragma once

namespace APUtils {

    static std::vector<std::string> levels = {
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
        /*
        "The Tower: Unlock",
        "The Sewers: Unlock",
        "The Cellar: Unlock",
        "The Secret Hollow: Unlock",
        */
    };

    void recieveItem(int64_t id, bool notify);

    void clearItemState();

    void checkLocationCallback(int64_t id);

    void createNotification(std::string name, bool location);

    void sendItem(int64_t id);

    void deathLinkRecieved();

    bool checkPortal(int id);

    void getStartingLevels(std::map<int64_t,int64_t> ids);

    void startArchipelago(const char* url, const char* slot, const char* pass);
}
