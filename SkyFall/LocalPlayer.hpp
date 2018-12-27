#pragma once
#include "BaseEntity.hpp"
#include "BaseWeapon.hpp"
#include <vector>

class LocalPlayer : public BaseEntity
{
private:
    std::vector<BaseWeapon*> weapons;
public:
    virtual void draw(sf::RenderTarget& renderTarget);
    virtual void update(float f_delta);
};

// TODO: Move this code somewhere else...
class PlayerSave {
public:
	std::string NName;	//Is the name the player wants to enter in for the new game save.
	std::string setName(std::string NName, std::string PS); //Will get the private string that's the name of the save and set the new name of the save.

private:
	std::string Psave1;	//Player Save 1
	std::string Psave2;	//Player Save 2
	std::string Psave3;	//Player Save 3

};

class PlayerInfo {
public:
	double PHealth = 100;	//Players Health
	double PShield = 50;	//Players shield
	double PStamina = 200;	//Players Stamina
	double StaminaRegenRate = .1;	//Stamina Regen tic rate

private:


};

class PlayerWeapon {
public:
	void ChoosePrimary();	//Player chooses there primary weapon
	void ChooseSecondary();	//Player chooses there secondary weapon
	void PrimaryAmmoPickup();	//Function that will add random amount of bullets to the local player current amount of primary ammo
	void SecondaryAmmoPickup();	//Function that will add random amount of bullets to the local player current amount of secondary ammo

	int PA = 0;	//Players Primary Weapon ammo amount
	int SA = 0;	//Players Secondary Weapon ammo amount  
	int SAmmo = SA;	//Players Secondary Ammo
	int PAmmo = PA;	//Players Primary ammo

private:

};

class PlayerPickup : PlayerInfo {
public:
	double HealthPickup();	//Adds Health to the local players current Health
	double ShieldPickup();	//Adds Shield to the local players current shield
	double StaminaRegenPickup();	//Adds a increase to the stamina regen rate for a short period of time

};