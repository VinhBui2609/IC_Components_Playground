#ifndef BH1750_H_
#define BH1750_H_


// Slave address
#define ADDR_HIGH_ADDRESS_WRITE 	(0xB8 + 0)
#define ADDR_HIGH_ADDRESS_READ 		(0xB8 + 1)
#define ADDR_LOW_ADDRESS_WRITE		(0x46 + 0)
#define ADDR_LOW_ADDRESS_READ 		(0x46 + 1)



// Commands table
#define POWER_DOWN			0x00
#define POWER_ON			0x01
#define RESET				0x07
#define CON_H_RES_MODE		0x10
#define CON_H_RES_MODE2		0x11
#define CON_L_RES_MODE		0x13
#define ONE_H_RES_MODE		0x20
#define ONE_H_RES_MODE2		0x21
#define ONE_L_RES_MODE		0x23
#define CHANGE_HIGH_MT		0x08	//01000_XXX
#define CHANGE_LOW_MT		0x03	//011_XXXXX

// Sending data
#define POW_2_OF_15 	32768
#define POW_2_OF_9 		512
#define POW_2_OF_8		256
#define POW_2_OF_7 		128
#define POW_2_OF_4 		16


#endif
