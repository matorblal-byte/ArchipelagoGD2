#include <Geode/modify/AchievementBar.hpp>

using namespace geode::prelude;

class $modify(APAchievementBar, AchievementBar) {
    bool init(char const* title, char const* desc, char const* icon, bool quest) {
        if (!AchievementBar::init(title, desc, icon, quest)) return false;
        if (icon == "APLogo.png"_spr) {
            auto size = this->m_bg->getContentSize();
            this->m_bg->initWithFile("GJ_square04.png");
            this->m_bg->setContentSize(size);
        };
        return true;
    }
};