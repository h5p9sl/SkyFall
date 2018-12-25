#include <iostream>
#include <string>
#include "LocalPlayer.hpp"


std::string PlayerSave::setName(std::string NName, std::string PS) {

	PS = NName;
	return PS;
}


void PlayerWeapon::ChoosePrimary(){
	std::string DMR;	//Desinated Marksman Rifle
	std::string AR;		//Assult Rifle
	std::string PAR;	//Plasma Assult Rifle
	std::string PMR;	//Plasma Marksman Rifle

	int DMRAmmo = 40;	//The maximum number of bullets the DMR can carry 
	int ARAmmo = 120;	//The maximum number of bullets the Assult Rifle can carry
	int PARAmmo = 100;	//The maximum number of bullets the Plasma Assult Rifle can carry
	int PMRAmmo = 35;	//The maximum numerb of bullets the Plasma Marksman Rifle can carry

	int DMRClip = 5;	//The Maximum number of bullets the DMR can carry in the clip
	int ARClip = 30;	//The Maximum number of bullets the Assult Rifle can carry in the clip
	int PARClip = 20;	//The Maximum number of bullets the Plasma Assult Rifle can carry in the clip 
	int PMRClip = 7;	//The Maximum number of bullets the Plasma Marksman Rifle can carry in the clip
}

void PlayerWeapon::ChooseSecondary() {
	std::string BPistol;	//Balistic Pistol
	std::string PPistol;	//Plasma Pistol

	int BPistolAmmo = 80;	//The maximum number of bullets the Balistic Pistol can carry
	int PPistolAmmo = 77;	//The maximum number of bullets the Plasma Pistol can carry

	int BPistolClip = 8;	//The Maximum number of bullets the Balistic Pistol can carry in the clip
	int PPistolClip = 7;	//The Maximum numbre of bullets the Plasma Pistol can carry in the clip
}

