#include "BaseWeapon.hpp"

BaseWeapon::BaseWeapon(const float reloadTime,
    const unsigned magazineSize,
    const bool infiniteReserve) :

    reloading(false),
    reloadTime(reloadTime),
    magazineSize(magazineSize),
    infiniteReserve(infiniteReserve)
{
}
