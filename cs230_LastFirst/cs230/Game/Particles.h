/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Particles.h
Project:    CS230 Engine
Author:     Donghyeon Jo
Created:    June 9, 2024
*/

#pragma once
#include "..\Engine\Particle.h"


namespace Particles {
    class Smoke : public CS230::Particle {
    public:
        Smoke() : Particle("Assets/Smoke.spt") { };
        std::string TypeName() override { return "Smoke Particle"; }
        static constexpr int MaxCount = 3;
        static constexpr double MaxLife = 5.0;
    };

    class Hit : public CS230::Particle {
    public:
        Hit() : Particle("Assets/Hit.spt") { };
        std::string TypeName() override { return "Hit Particle"; }
        static constexpr int MaxCount = 10;
        static constexpr double MaxLife = 1.0;
    };

    class MeteorBit : public CS230::Particle {
    public:
        MeteorBit() : Particle("Assets/MeteorBit.spt") { };
        std::string TypeName() override { return "MeteorBit Particle"; }
        static constexpr int MaxCount = 150;
        static constexpr double MaxLife = 1.25;
    };
    class SmokeRed : public CS230::Particle {
    public:
        SmokeRed() : Particle("Assets/SmokeRed.spt") { };
        std::string TypeName() override { return "Smoke Particle"; }
        static constexpr int MaxCount = 3;
        static constexpr double MaxLife = 5.0;
    }; 
    class SmokeYellow : public CS230::Particle {
    public:
        SmokeYellow() : Particle("Assets/SmokeYellow.spt") { };
        std::string TypeName() override { return "Smoke Particle"; }
        static constexpr int MaxCount = 3;
        static constexpr double MaxLife = 5.0;
    };
    class SmokeBlue : public CS230::Particle {
    public:
        SmokeBlue() : Particle("Assets/SmokeBlue.spt") { };
        std::string TypeName() override { return "Smoke Particle"; }
        static constexpr int MaxCount = 3;
        static constexpr double MaxLife = 5.0;
    };
    class SmokeGreen : public CS230::Particle {
    public:
        SmokeGreen() : Particle("Assets/SmokeGreen.spt") { };
        std::string TypeName() override { return "Smoke Particle"; }
        static constexpr int MaxCount = 3;
        static constexpr double MaxLife = 5.0;
    };
    class SmokeGray : public CS230::Particle {
    public:
        SmokeGray() : Particle("Assets/SmokeGray.spt") { };
        std::string TypeName() override { return "Smoke Particle"; }
        static constexpr int MaxCount = 3;
        static constexpr double MaxLife = 5.0;
    };
    class ParticleYellow : public CS230::Particle {
    public:
        ParticleYellow() : Particle("Assets/ParticleYellow.spt") { };
        std::string TypeName() override { return "MeteorBit Particle"; }
        static constexpr int MaxCount = 150;
        static constexpr double MaxLife = 1.25;
    };
    class ParticleGreen : public CS230::Particle {
    public:
        ParticleGreen() : Particle("Assets/ParticleGreen.spt") { };
        std::string TypeName() override { return "MeteorBit Particle"; }
        static constexpr int MaxCount = 150;
        static constexpr double MaxLife = 1.25;
    };
    class ParticleBlue : public CS230::Particle {
    public:
        ParticleBlue() : Particle("Assets/ParticleBlue.spt") { };
        std::string TypeName() override { return "MeteorBit Particle"; }
        static constexpr int MaxCount = 150;
        static constexpr double MaxLife = 1.25;
    };
    class ParticleGray : public CS230::Particle {
    public:
        ParticleGray() : Particle("Assets/ParticleGray.spt") { };
        std::string TypeName() override { return "MeteorBit Particle"; }
        static constexpr int MaxCount = 150;
        static constexpr double MaxLife = 1.25;
    };
    class ParticleRed : public CS230::Particle {
    public:
        ParticleRed() : Particle("Assets/ParticleRed.spt") { };
        std::string TypeName() override { return "MeteorBit Particle"; }
        static constexpr int MaxCount = 150;
        static constexpr double MaxLife = 1.25;
    };
}
