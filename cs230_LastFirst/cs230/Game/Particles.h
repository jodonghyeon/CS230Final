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

    class SmogeRed : public CS230::Particle {
    public:
        SmogeRed() : Particle("Assets/SmogeRed.spt") { };
        std::string TypeName() override { return "SmogeRed Particle"; }
        static constexpr int MaxCount = 2;
        static constexpr double MaxLife = 2.0;
    };

    class SmogeYellow : public CS230::Particle {
    public:
        SmogeYellow() : Particle("Assets/SmogeYellow.spt") { };
        std::string TypeName() override { return "SmogeYellow Particle"; }
        static constexpr int MaxCount = 2;
        static constexpr double MaxLife = 2.0;
    };

    class SmogeGreen : public CS230::Particle {
    public:
        SmogeGreen() : Particle("Assets/SmogeGreen.spt") { };
        std::string TypeName() override { return "SmogeGreen Particle"; }
        static constexpr int MaxCount = 2;
        static constexpr double MaxLife = 2.0;
    };

    class SmogeBlue : public CS230::Particle {
    public:
        SmogeBlue() : Particle("Assets/SmogeBlue.spt") { };
        std::string TypeName() override { return "SmogeBlue Particle"; }
        static constexpr int MaxCount = 2;
        static constexpr double MaxLife = 2.0;
    };

    class SmogeGrey : public CS230::Particle {
    public:
        SmogeGrey() : Particle("Assets/SmogeGrey.spt") { };
        std::string TypeName() override { return "SmogeGrey Particle"; }
        static constexpr int MaxCount = 2;
        static constexpr double MaxLife = 2.0;
    };

    class ParticleRed : public CS230::Particle {
    public:
        ParticleRed() : Particle("Assets/ParticleRed.spt") { };
        std::string TypeName() override { return "ParticleRed Particle"; }
        static constexpr int MaxCount = 50;
        static constexpr double MaxLife = 0.5;
    };

    class ParticleYellow : public CS230::Particle {
    public:
        ParticleYellow() : Particle("Assets/ParticleYellow.spt") { };
        std::string TypeName() override { return "ParticleYellow Particle"; }
        static constexpr int MaxCount = 50;
        static constexpr double MaxLife = 0.5;
    };

    class ParticleGreen : public CS230::Particle {
    public:
        ParticleGreen() : Particle("Assets/ParticleGreen.spt") { };
        std::string TypeName() override { return "ParticleGreen Particle"; }
        static constexpr int MaxCount = 50;
        static constexpr double MaxLife = 0.5;
    };

    class ParticleBlue : public CS230::Particle {
    public:
        ParticleBlue() : Particle("Assets/ParticleBlue.spt") { };
        std::string TypeName() override { return "ParticleBlue Particle"; }
        static constexpr int MaxCount = 50;
        static constexpr double MaxLife = 0.5;
    };

    class ParticleGrey : public CS230::Particle {
    public:
        ParticleGrey() : Particle("Assets/ParticleGrey.spt") { };
        std::string TypeName() override { return "ParticleGrey Particle"; }
        static constexpr int MaxCount = 50;
        static constexpr double MaxLife = 0.5;
    };
}
