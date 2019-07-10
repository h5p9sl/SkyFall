#include "weapon.hpp"

BaseWeapon::BaseWeapon(const float reloadTime,
    const float fireRate,
    const unsigned magazineSize,
    const bool infiniteReserve) :

    reloading(false),
    reloadTime(reloadTime),
    fireRate(fireRate),
    magazineSize(magazineSize),
    infiniteReserve(infiniteReserve),
    currentAmmo(magazineSize),
    reserveAmmo(magazineSize * 3)
{
}

BaseWeapon::~BaseWeapon() {
	// Erase all projectiles (and free memory)
	this->projectiles.clear();
}
