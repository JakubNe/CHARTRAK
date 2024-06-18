/*
 * AWG.c
 *
 *  Created on: Feb 13, 2024
 *      Author: Admin
 */

#include "AWG.h"
#include <stdint.h>
#include "main.h" // for GPIO names
#include "board.h"
#include "LOLA.h"
#include "ProgRef.h"
#include "trim.h"
#include "math.h"

#define MaxDepth 256 // max AWG samples

void AWG_Load_Waveform(AWG_setup_struct AWG1, Noise_setup_struct NOISE1)
{
	uint8_t byte[4];
	int16_t data;

	uint16_t depth = trimInt((int)(DACmaxFreq/AWG1.Freq), 1, (MaxDepth-1));


	uint16_t DepthPos = trimInt((int)(depth*AWG1.DutyCycle/100), 1, (MaxDepth-1));
	uint16_t DepthNeg = trimInt((int)(depth-DepthPos), 1, (MaxDepth-1));

	// setting frequency
	//LOLA_Set_CLK1(AWG1.Freq*depth);


	// setting sample count
	byte[0] = 0;
	byte[1] = 0;
	byte[2] = (uint8_t)(depth-1);
	byte[3] = (uint8_t)AWG_MAXADRESS;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);

	//NOISE_Load_param(NOISE1);

	// loading waveform
	float relativeDACcode = 2047*AWG1.Upp/(2*MAX_AMPLITUDE); // multiply any number from -1 to 1 and you will get direct code for DAC

	for(uint16_t addr = 0; addr < depth; addr++)
	{

		switch(AWG1.waveform)
		{
			case Square: data = (int16_t)((addr>=(depth*AWG1.DutyCycle/100))*relativeDACcode); break;

			case Triangle:	if(addr <= DepthPos) data = (int16_t)(relativeDACcode*addr/(DepthPos*1.0)); // rising edge
							else data = (int16_t)(relativeDACcode*(1-(addr-DepthPos)/(DepthNeg*1.0))); break; // falling edge

			case Sine: data = (int16_t)(relativeDACcode*sinf((addr*3.14159*2)/(1.0*depth))); break;

			case Func: break;
		}

		byte[0] = (int8_t)((addr>>4)&0x000f);
		byte[1] = (int8_t)(((data>>8)&0x000f)|((addr<<4)&0x00f0));
		byte[2] = (int8_t)(data&0x00ff);
		byte[3] = (int8_t)AWG_DATA;

		HAL_SPI_Transmit(&hspi1, byte, 4, 100);
		HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
		HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	}

}

/*void AWG_Set_CLK1(uint32_t freq)
{
#define ClkMultiplier 15 //DCM fixed frequency multiplier
   #define MaxMultiplierOutputFreq 300 //MHz
   #define maxreg 16777216 //max division register value 2^24

   long M, D, Matt, Datt = 1; // Multiplier, Divider
   int precision = 1; // Max tolerated error of Fraction optimizer
   int success = 0;

   /*          Output frequency calcultaion:
    *  Fout = Fref*(M/maxreg)*ClkMultiplier*(1/D)
    *        Fref*(M/maxreg)*ClkMultiplier < MaxMultiplierOutputFreq
    */

   /*do{
       M = (long)(Fout*1000/(ClkMultiplier*1.0))/(1000000.0*Mclk*MclkMult/(maxreg*1.0));
       //printf("num: %lf\t%lf\n",input,maxreg);
       D = 1000;

       /*while((long)(input*100)%100!=0 && input < 100000)   // make simple fraction
       {
           input*=10.0;
           D*=10;
       }
       M = (long)input;*/

       //printf("Start: %d/%d\n",M,D);

       /*do{ // optimize fraction
           //printf("precision: %d\n",precision);
           success = 0;
           Matt, Datt = 1;
           for(long cmndiv = 2; cmndiv < 100000; cmndiv++)   //finding common denominator
               {
                   //printf("%d/%d=%d   %d/%d=%d\n",multiply,cmndiv,(multiply*100)%(100*cmndiv),divide,cmndiv,(divide*100)%(100*cmndiv));
                   if((M*10)%(10*cmndiv)<=precision && (D*10)%(10*cmndiv)<=precision)
                   {
                       Matt = M/cmndiv;
                       Datt = D/cmndiv;
                       success = 1;
                       printf("attempt: %d/%d\n",Matt,Datt);
                   }
               }
           if(Matt==0 || Datt==0) break; // failsafe

           precision+=1;
       }while(!(success && Matt<maxreg && Datt<maxreg && precision <= 10 && Mclk*MclkMult*(Matt/(maxreg*1.0))*ClkMultiplier < MaxMultiplierOutputFreq)); // attempt
       if(!success) Fout+=0.01;
   }while(!success);

       M = Matt;
       D = Datt;

   printf("Fout= %lfHz\tFmul= %fMHz\t",1000000*Mclk*MclkMult*(M/(maxreg*1.0))*ClkMultiplier*(1/(D*1.0)),Mclk*MclkMult*(M/(maxreg*1.0))*ClkMultiplier);
   double err = fabs(1000000*(1000000*Mclk*MclkMult*(M/(maxreg*1.0))*ClkMultiplier*(1/(D*1.0))-Fout)/Fout);
   printf("error = %lfppm\n",err);
   averangeErr+=err;
   if(err>maxErr) maxErr = err;

   return success;
}
}*/

void Noise_Set_CLK1(uint32_t freq)
{
	uint8_t byte[4];


	uint32_t prescaler = (uint32_t)MCLKfreq/(1.0*freq);

	// setting prescaler
	byte[0] = (uint8_t)((prescaler>>16)&0x00ff);
	byte[1] = (uint8_t)((prescaler>>8)&0x00ff);
	byte[2] = (uint8_t)(prescaler&0x00ff);
	byte[3] = (uint8_t)NOISE_PRESCALER;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
}

void NOISE_Load_param(Noise_setup_struct NOISE1)
{
	uint8_t byte[4];
	uint16_t data;

		// Clear noise amplitude (enable Seed insertion)
	byte[0] = 0;
	byte[1] = 0;
	byte[2] = 0;
	byte[3] = (uint8_t)NOISE_AMPLITUDE;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);

	for(uint8_t part = 0; part < 4; part++)	// Load noise seed
	{
		byte[0] = (uint8_t)((NOISE1.Seed>>(8+(16*part)))&0x00ff);
		byte[1] = (uint8_t)((NOISE1.Seed>>(16*part))&0x00ff);
		byte[2] = (uint8_t)(part&0x000f);
		byte[3] = (uint8_t)NOISE_SEED;

		HAL_SPI_Transmit(&hspi1, byte, 4, 100);
		HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
		HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	}

	Noise_Set_CLK1(NOISE1.Freq);

	data = (uint16_t)trimInt((int)(1023*NOISE1.Upp/(2.0*DACref)), 0, 1023); // Load noise amplitude

	byte[0] = 0;
	byte[1] = (uint8_t)((data>>8)&0x0003);
	byte[2] = (uint8_t)(data&0x00ff);
	byte[3] = (uint8_t)NOISE_AMPLITUDE;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
}
