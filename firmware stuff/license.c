#include <stdint.h>
#include "license.h"

void confirmLicenseKey(uint64_t licenseKey, uint32_t* ProductNumber, uint16_t* Features)
{
	for (uint32_t i = 0; i < 0xf1f5a3; i++)	// dehashing license
	{
		uint8_t byte = ((licenseKey & 0x4000000000000000) != 0) ^ ((licenseKey & 0x0000000000000001) != 0);
		licenseKey = licenseKey >> 1;
		if (byte != 0) licenseKey |= 0x8000000000000000;
	}

	if (((licenseKey >> 16) & 0xffffffffffff) == ((uint64_t)*ProductNumber | 0x0000fa5f00000000))
		*Features |= (uint16_t)(licenseKey & 0xffff);	// if License is valid, return unlocked features
}

void voidLicenseKey(uint16_t* Features)
{
	*Features = 0b0000000000000001;	// Loads basic functions
}
