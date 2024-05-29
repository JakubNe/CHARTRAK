/*
 * license.h
 *
 *  Created on: Feb 13, 2024
 *      Author: Admin
 */

#ifndef LICENSE_H_
#define LICENSE_H_

void confirmLicenseKey(uint64_t licenseKey, uint32_t* ProductNumber, uint16_t* Features);
void voidLicenseKey(uint16_t* Features);

#endif /* LICENSE_H_ */
