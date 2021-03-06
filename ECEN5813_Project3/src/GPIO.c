/*
* @file uart.c
* @brief Defines GPIO operation and provides functions for GPIO operation and initialization
* @author Karros Huang & Girish Narayanswamy
* @date 3/3/2017
*/

#include "GPIO.h"

void GPIO_Configure(){

	/*Enable System Clock for PORT B&D*/
	SIM->SCGC5 |= SIM_SCGC5_PORTB(1);
	SIM->SCGC5 |= SIM_SCGC5_PORTD(1);

	/* Set PCR MUX to GPIO Mode */
	PORTB->PCR[18] = PORT_PCR_MUX(1); /*PortB Pin 18 GPIO Mode*/
	PORTB->PCR[19] = PORT_PCR_MUX(1); /*PortB Pin 19 GPIO Mode*/
	PORTD->PCR[1] = PORT_PCR_MUX(1); /*PortD Pin 1 GPIO Mode*/


	/*Data Direction for LED's set out*/
	GPIOB->PDDR |= (0x03<<18); /*Setting Red and Green LED Direction to Out*/
	GPIOD->PDDR |= (0x01<<1); /*Setting Blue LED Direction to Out*/

	/*Data output for LED's set low*/
	GPIOB->PDOR |= 0x03<<18;	/*Set Output of RED and Green LED Low*/
	GPIOD->PDOR |= 0x01<<1; /*Set Output of Blue LED Low*/
}

void Toggle_Red_LED(){
	GPIOB->PDOR ^= (0x01<<18); /*Flipping the RED LED Output bit to toggle between 0 & 1 */
}

__attribute__((always_inline)) inline void PORTB_Set(uint8_t bit_num){
	GPIOB->PSOR |= (0x01<<bit_num); /* Sets port B pin X Data output bit to 1 */
}

__attribute__((always_inline)) inline void PORTD_Set(uint8_t bit_num){
	GPIOD->PSOR |= (0x01<<bit_num); /* Sets port D pin X Data output bit to 1 */
}

__attribute__((always_inline)) inline void PORTB_Clear(uint8_t bit_num){
	GPIOB->PCOR |= (0x01<<bit_num); /* Sets port B pin X Data output bit to 0 */
}

__attribute__((always_inline)) inline void PORTD_Clear(uint8_t bit_num){
	GPIOD->PCOR |= (0x01<<bit_num); /* Sets port D pin X Data output bit to 0 */
}

__attribute__((always_inline)) inline void PORTB_Toggle(uint8_t bit_num){
	GPIOB->PTOR |= (0x01<<bit_num); /* Flips port B pin X Data output bit */
}

__attribute__((always_inline)) inline void PORTD_Toggle(uint8_t bit_num){
	GPIOD->PTOR |= (0x01<<bit_num); /* Flips port D pin X Data output bit */
}

__attribute__((always_inline)) inline void GPIO_nrf_init(){
	/*Enable System Clock for Port C & SPI0*/
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;

	/*Put GPIO Pins in SPI Mode*/
	PORTC->PCR[6] |= PORT_PCR_MUX(0x02); /*Set SPI0_MOSI to PTC6*/
	PORTC->PCR[5] |= PORT_PCR_MUX(0x02); /*Set SPI0_SCK to PTC5*/
	PORTC->PCR[7] |= PORT_PCR_MUX(0x02); /*Set SPI0_MISO to PTC7*/
	PORTC->PCR[9] |= PORT_PCR_MUX(0x01); /*Set GPIO mode to PTC9*/
	GPIOC->PDDR |= 1<<9;  				 /*Set PTC9 (PCS) to Output*/
	GPIOC->PSOR |= 1<<9; 				 /*Set PTC9 (PCS) to High*/
}
