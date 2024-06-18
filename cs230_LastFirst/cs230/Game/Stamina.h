/*
File Name:  Stamina.h
Project:    CS230 Final
Author:     Donghyeon Jo
Created:    June 18, 2024
*/

#pragma once
#include "..\Engine\GameObject.h"

class Stamina : public CS230::Component {
public:
    Stamina(CS230::GameObject& object, double stamina_max)
        : object(object), stamina_max(stamina_max), stamina(stamina_max)
    { }

    void SetStaminaMax(double new_stamina_max) { stamina_max = new_stamina_max; }
    double GetStaminaMax() { return stamina_max; }

    void SetStamina(double new_stamina) { stamina = new_stamina; }
    void UpdateStamina(double delta) {
        if(delta>0.0&&stamina >= stamina_max-delta) {
            stamina = stamina_max;
        }
        else if (delta<0.0&&stamina <= -delta) {
            stamina = 0.0;
        }
        else {
            stamina += delta;
        }
    }
    double GetStamina()const { return stamina; }
    
private:
    CS230::GameObject& object;
    double stamina_max;
    double stamina;
};