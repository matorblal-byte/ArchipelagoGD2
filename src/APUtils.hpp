#pragma once

namespace APUtils {
    void recieveItem(int64_t id, bool notify);

    void clearItemState();

    void checkLocationCallback(int64_t id);

    void createNotification(std::string name, bool location);

    void sendItem(int64_t id);

    void deathLinkRecieved();

    bool checkPortal(int id);

    void startArchipelago(const char* url, const char* slot, const char* pass);
}
