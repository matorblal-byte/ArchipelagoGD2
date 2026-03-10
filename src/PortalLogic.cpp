#include <Geode/modify/PlayLayer.hpp>
#include "APUtils.hpp"

using namespace geode::prelude

class $modify(APPlayLayer, PlayLayer) {
    void addObject(GameObject* p0) {
        if (APUtils::checkPortal(p0->m_objectID)) 
          PlayLayer::addObject(p0);
        }
    };
};

