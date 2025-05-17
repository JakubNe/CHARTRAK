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

#define Depth 2048 // AWG samples
#define PhaseAccumilatorBits 48

void AWG_Load_Waveform(AWG_struct* AWG, HFDAC_struct* HFDAC)
{
	LOLA_enable_features(AWG_EN, 0); // disable AWG

	uint8_t byte[4];
	int32_t data;

	//uint16_t depth = trimInt((int)round(DACmaxFreq/AWG->Freq), 1, (MaxDepth-1));

	uint16_t DepthPos = trimInt((int)round(Depth*AWG->DutyCycle/100.0), 1, (Depth-1));
	uint16_t DepthNeg = trimInt((int)(Depth-DepthPos), 1, (Depth-1));

	/*
	// setting sample count
	byte[0] = 0;
	byte[1] = (uint8_t)((depth>>8)&0x00ff);
	byte[2] = (uint8_t)(depth&0x00ff);
	byte[3] = (uint8_t)AWG_MAXADRESS;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);*/

	//Setting up DDS control word
	uint64_t D = (uint64_t)round(AWG->Freq*(((uint64_t)1<<(PhaseAccumilatorBits-1))/(uint64_t)DACmaxFreq));

	// DDS control word LSB setup
	data = (int32_t)(D&0xffffff);

	byte[0] = (uint8_t)((data>>16)&0x00ff);
	byte[1] = (uint8_t)((data>>8)&0x00ff);
	byte[2] = (uint8_t)(data&0x00ff);
	byte[3] = (uint8_t)AWG_D_LSB;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);

	// DDS control word MSB setup
	data = (int32_t)((D>>24)&0xffffff);

	byte[0] = (uint8_t)((data>>16)&0x00ff);
	byte[1] = (uint8_t)((data>>8)&0x00ff);
	byte[2] = (uint8_t)(data&0x00ff);
	byte[3] = (uint8_t)AWG_D_MSB;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);

	// loading waveform
	float relativeDACcode = 0;
	switch(HFDAC1.mode)
	{
		case Voltage_output: relativeDACcode = trimFloat((AWG->Uamp * HFDAC->relativeDACcodeCoefU_V), 0, 4095); break;
		case Current_output: relativeDACcode = trimFloat((AWG->Iamp * HFDAC->relativeDACcodeCoefI_mA), 0, 4095); break;

	}

	for(int16_t addr = 0; addr < Depth; addr++)
	{

		switch(AWG->waveform)
		{
			case Square: data = 2*(int16_t)round((addr<=(Depth*AWG->DutyCycle/100))*relativeDACcode-(relativeDACcode/2.0)); break;

			case Triangle:	if(addr <= DepthPos) data = 2*(int16_t)round(relativeDACcode*addr/(DepthPos*1.0)-(relativeDACcode/2.0)); // rising edge
							else data = 2*(int16_t)round(relativeDACcode*(1-(addr-DepthPos)/(DepthNeg*1.0))-(relativeDACcode/2.0)); break; // falling edge

			case Sine: data = (int16_t)round(relativeDACcode*(AWG->Uavg+sinf((addr*3.14159*2)/(1.0*Depth)))); break;

			case Func: data = 0; break;
		}

		byte[0] = (int8_t)((addr>>4)&0x00ff);
		byte[1] = (int8_t)(((data>>8)&0x000f)|((addr<<4)&0x00f0));
		byte[2] = (int8_t)(data&0x00ff);
		byte[3] = (int8_t)AWG_DATA;

		HAL_SPI_Transmit(&hspi1, byte, 4, 100);
		HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
		HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);
	}

	LOLA_enable_features(AWG_EN, 1); // enable AWG
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

void NOISE_Load_param(Noise_struct* NOISE, HFDAC_struct* HFDAC)
{
	LOLA_enable_features(NOISE_EN, 0); // disable Noise generator

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

	Noise_Set_CLK1(NOISE->Freq);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// FIX!!!!!!!!!
	float relativeDACcode = NOISE->Uamp * HFDAC->relativeDACcodeCoefU_V;

	data = (uint16_t)relativeDACcode;

	byte[0] = 0;
	byte[1] = (uint8_t)((data>>8)&0x0007);
	byte[2] = (uint8_t)(data&0x00ff);
	byte[3] = (uint8_t)NOISE_AMPLITUDE;

	HAL_SPI_Transmit(&hspi1, byte, 4, 100);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 1);
	HAL_GPIO_WritePin(SPI1_FPGAS_GPIO_Port, SPI1_FPGAS_Pin, 0);

	LOLA_enable_features(NOISE_EN, 1); // enable Noise generator
}
