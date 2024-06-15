#pragma once
#include "..\Engine\GameObject.h"
#include "..\Engine\Rect.h"
#include "GameObjectTypes.h"

class Portal : public CS230::GameObject {
public:
    Portal(int to_state, Math::irect boundary);
    std::string TypeName() override { return "Portal"; }
    virtual GameObjectType Type() override { return GameObjectType::Portal; }

    void GoToState();
private:
    int to_state;
};
