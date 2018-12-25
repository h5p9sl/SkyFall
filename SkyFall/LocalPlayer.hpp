#pragma once
#include "BaseEntity.hpp"

class LocalPlayer : public BaseEntity
{
public:
};

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
	int PA = 0;	//Players Primary Weapon ammo amount
	int SA = 0;	//Players Secondary Weapon ammo amount  
	int PHealth = 100;	//Players Health
	int PShield = 50;	//Players shield
	int SAmmo = SA;	//Players Secondary Ammo
	int PAmmo = PA;	//Players Primary ammo
	double Pstamina = 200;	//Players Stamina

private:


};

class PlayerWeapon {
public:
	void ChoosePrimary();	//Player chooses there primary weapon
	void ChooseSecondary();	//Player chooses there secondary weapon

private:

};
