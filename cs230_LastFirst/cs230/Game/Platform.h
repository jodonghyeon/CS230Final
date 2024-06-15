#pragma once
#include "..\Engine\GameObject.h"
#include "..\Engine\Vec2.h"
#include "Platforms.h"
#include "GameObjectTypes.h"
#include "..\Engine\Matrix.h"
#include "..\Engine\Texture.h"

class Platform : public CS230::GameObject {
public:
    Platform(Math::vec2 position, int length, Platforms type);

    GameObjectType Type() override {
        return GameObjectType::Platform;
    }

    std::string TypeName() override {
        return "Platform";
    }

    void Draw(Math::TransformationMatrix camera_matrix)override;

    static constexpr int platform_unit_width = 40;
    static constexpr int platform_height = 40;

private:
    int length;
    CS230::Texture* texture;
};