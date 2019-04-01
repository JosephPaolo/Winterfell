
#include "MobComponent.h"

void MobComponent::ApplyDamage(int getDamage) {

	if (getDamage >= health) { //If mobile loses all health apply death
		health = 0;
		ApplyDeath();
		return;
	}
	else if (getDamage < maxhealth * -1) { //If mobile heals more than max health, set health to max health
		health = maxhealth;
	}

	health = health - getDamage;
}

void MobComponent::ApplyDeath() {

}