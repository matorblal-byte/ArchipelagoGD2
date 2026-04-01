#include <Geode/Geode.hpp>
#include <Geode/modify/GJItemIcon.hpp>

using namespace geode::prelude;

class $modify(APGJItemIcon, GJItemIcon) {
    void darkenStoreItem(ShopType type) {
        return; // if it works it works i guess ????
        GJItemIcon::darkenStoreItem(type);
    }
};