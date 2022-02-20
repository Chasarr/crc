#include <stdlib.h>
#include <stdio.h>		//IO
#include <stdint.h>		//uint8_t, included in Arduino library
#include <stdbool.h>	//1 or 0
#define G 0xA7			//generator polynomial

//Function prototypes
uint8_t crc_gen(uint8_t data, uint8_t crc);
uint8_t data = 194;

int main() {
	uint8_t crc = crc_gen(data, 0);
	printf("Data = %u, crc = %u\n", data, crc);
	crc = crc_gen(data, crc);
	if(crc == 0){
		printf("crc = 0! We made it!\n");
	}else{
		printf("Oh no! crc = %u. This is not good!\n", crc);
	}
	return 0;
}

//For generating crc, crc = 0
//for validating crc, crc =... well, the crc of course!
uint8_t crc_gen(uint8_t data, uint8_t crc){
	// The grade is 8. Register should have 8 bits
	// msbMask and invertMsbMask to more easily get Msb
	uint8_t msbMask = 0x80;
	uint8_t invertMsbMask = ~msbMask;

	//Shift through data with a for loop
	for(unsigned short i = 0; i < 8; i++){
		bool crcMsb = (crc & msbMask);
		if(msbMask & data){
			//perform XOR performed between data and g
			//since we know that g's and data's first bit both are 1
			// we can safely say that this is going to be zero
			// so we'll bit shift
			data <<= 1;
			//if we're generating CRC, the variable crc is 0.
			data += crcMsb;
			//we have already XORed g's first bit, so lets remove that from g
			//and lets XOR data with G (generator polynomial)
			data ^= (G & invertMsbMask);
		}else{
			//MSB is zero, just bit shift until 1 is found
			data <<= 1;
			data += crcMsb;
		}
		//Bit shift crc as well
		crc <<= 1;
	}
	return data;
}
