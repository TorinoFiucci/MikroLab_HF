#include "lcd_driver_bsp.h"
#include "main.h"
#include <string.h>
#include "stdint.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_PAGES (SCREEN_HEIGHT / 8)

// screen_buffer[lap_száma][x_koordináta]
static uint8_t screen_buffer[SCREEN_PAGES][SCREEN_WIDTH];



void LCD_Buffer_Init() {
	memset(screen_buffer, 0x00, sizeof(screen_buffer));
}

void LCD_Set_Pixel(uint8_t x, uint8_t y, uint8_t color) {

	if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT) {
		return; // Koordinátán kívül
	}

	uint8_t page = y / 8;
	uint8_t bit_position = y % 8;

	if (color) {
		screen_buffer[page][x] |= (1 << bit_position);  // Pixel bekapcsolása
	} else {
		screen_buffer[page][x] &= ~(1 << bit_position); // Pixel kikapcsolása
	}
}

void LCD_Refresh_Display() {
	uint8_t page, col_on_chip;

	for (page = 0; page < SCREEN_PAGES; page++) {
		// Bal oldali chip (CS1)
		HAL_GPIO_WritePin(CS1_LCD_GPIO_Port, CS1_LCD_Pin, GPIO_PIN_RESET); // CS1 aktív
		HAL_GPIO_WritePin(CS2_LCD_GPIO_Port, CS2_LCD_Pin, GPIO_PIN_SET);   // CS2 inaktív

		Set_Page(page);  // CS1-re
		Set_Coloumn(0);  // CS1-re

		HAL_GPIO_WritePin(D_I_LCD_GPIO_Port, D_I_LCD_Pin, GPIO_PIN_SET); // Adat mód

		for (col_on_chip = 0; col_on_chip < 64; col_on_chip++) { // CS1 64 oszlopa
			Write_Data_Bits(screen_buffer[page][col_on_chip]);
			E_Pulse();
		}

		// Jobb oldali chip (CS2)
		HAL_GPIO_WritePin(CS1_LCD_GPIO_Port, CS1_LCD_Pin, GPIO_PIN_SET);   // CS1 inaktív
		HAL_GPIO_WritePin(CS2_LCD_GPIO_Port, CS2_LCD_Pin, GPIO_PIN_RESET); // CS2 aktív

		Set_Page(page);  // CS2-re
		Set_Coloumn(0);  // CS2-re

		HAL_GPIO_WritePin(D_I_LCD_GPIO_Port, D_I_LCD_Pin, GPIO_PIN_SET); // Adat mód

		for (col_on_chip = 0; col_on_chip < 64; col_on_chip++) { // CS2 64 oszlopa
			// A puffer 64-127. oszlopait olvassuk ki a jobb oldali chip számára
			Write_Data_Bits(screen_buffer[page][col_on_chip + 64]);
			E_Pulse();
		}
	}

	HAL_GPIO_WritePin(CS1_LCD_GPIO_Port, CS1_LCD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CS2_LCD_GPIO_Port, CS2_LCD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(D_I_LCD_GPIO_Port, D_I_LCD_Pin, GPIO_PIN_RESET); // Vissza parancs módba
}


void Display_On(){

	HAL_GPIO_WritePin(_RST_LCD_GPIO_Port, _RST_LCD_Pin, SET);



	HAL_GPIO_WritePin(CS1_LCD_GPIO_Port, CS1_LCD_Pin, RESET);
	HAL_GPIO_WritePin(CS2_LCD_GPIO_Port, CS2_LCD_Pin, RESET);

	HAL_Delay(1);

	HAL_GPIO_WritePin(D_I_LCD_GPIO_Port, D_I_LCD_Pin, RESET);

	HAL_GPIO_WritePin(Dir_R_W_LCD_GPIO_Port, Dir_R_W_LCD_Pin, RESET);



	HAL_GPIO_WritePin(DB7_LCD_GPIO_Port, DB7_LCD_Pin, RESET);
	HAL_GPIO_WritePin(DB6_LCD_GPIO_Port, DB6_LCD_Pin, RESET);

	HAL_GPIO_WritePin(DB1_LCD_GPIO_Port, DB1_LCD_Pin, SET);
	HAL_GPIO_WritePin(DB2_LCD_GPIO_Port, DB2_LCD_Pin, SET);
	HAL_GPIO_WritePin(DB3_LCD_GPIO_Port, DB3_LCD_Pin, SET);
	HAL_GPIO_WritePin(DB4_LCD_GPIO_Port, DB4_LCD_Pin, SET);
	HAL_GPIO_WritePin(DB5_LCD_GPIO_Port, DB5_LCD_Pin, SET);

	HAL_GPIO_WritePin(DB0_LCD_GPIO_Port, DB0_LCD_Pin, SET);

	HAL_Delay(1);

	E_Pulse();

	HAL_GPIO_WritePin(CS1_LCD_GPIO_Port, CS1_LCD_Pin, SET);
	HAL_GPIO_WritePin(CS2_LCD_GPIO_Port, CS2_LCD_Pin, SET);

}

void Display_Off()
{

	HAL_GPIO_WritePin(CS1_LCD_GPIO_Port, CS1_LCD_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CS2_LCD_GPIO_Port, CS2_LCD_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);


	HAL_GPIO_WritePin(D_I_LCD_GPIO_Port, D_I_LCD_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(Dir_R_W_LCD_GPIO_Port, Dir_R_W_LCD_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);


	// DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	//  0   0   1   1   1   1   1   0
	HAL_GPIO_WritePin(DB7_LCD_GPIO_Port, DB7_LCD_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DB6_LCD_GPIO_Port, DB6_LCD_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DB5_LCD_GPIO_Port, DB5_LCD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DB4_LCD_GPIO_Port, DB4_LCD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DB3_LCD_GPIO_Port, DB3_LCD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DB2_LCD_GPIO_Port, DB2_LCD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DB1_LCD_GPIO_Port, DB1_LCD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DB0_LCD_GPIO_Port, DB0_LCD_Pin, GPIO_PIN_RESET);

	HAL_Delay(1);
	E_Pulse();


	HAL_GPIO_WritePin(CS1_LCD_GPIO_Port, CS1_LCD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CS2_LCD_GPIO_Port, CS2_LCD_Pin, GPIO_PIN_SET);
}

void Clear_Display()
{

	HAL_GPIO_WritePin(CS1_LCD_GPIO_Port, CS1_LCD_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CS2_LCD_GPIO_Port, CS2_LCD_Pin, GPIO_PIN_RESET);

	for (uint8_t page = 0; page < 8; page++)
	{
		Set_Page(page);
		Set_Coloumn(0);


		HAL_GPIO_WritePin(D_I_LCD_GPIO_Port, D_I_LCD_Pin, GPIO_PIN_SET);

		for (uint8_t col = 0; col < 64; col++)
		{
			Write_Data_Bits(0x00);
			E_Pulse();

		}
	}


	Set_Page(0);
	Set_Coloumn(0);


	HAL_GPIO_WritePin(CS1_LCD_GPIO_Port, CS1_LCD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CS2_LCD_GPIO_Port, CS2_LCD_Pin, GPIO_PIN_SET);
}


int Set_Coloumn(uint8_t Y_address){

	if(Y_address < 0 || Y_address >= 64){
		return 0;
	}

	HAL_GPIO_WritePin(DB7_LCD_GPIO_Port, DB7_LCD_Pin, RESET);
	HAL_GPIO_WritePin(DB6_LCD_GPIO_Port, DB6_LCD_Pin, SET);
	HAL_GPIO_WritePin(D_I_LCD_GPIO_Port, D_I_LCD_Pin, RESET);
	HAL_GPIO_WritePin(Dir_R_W_LCD_GPIO_Port, Dir_R_W_LCD_Pin, RESET);


	if(Y_address & 0b00000001){
		HAL_GPIO_WritePin(DB0_LCD_GPIO_Port, DB0_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB0_LCD_GPIO_Port, DB0_LCD_Pin, RESET);
	}

	if(Y_address & 0b00000010){
		HAL_GPIO_WritePin(DB1_LCD_GPIO_Port, DB1_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB1_LCD_GPIO_Port, DB1_LCD_Pin, RESET);
	}

	if(Y_address & 0b00000100){
		HAL_GPIO_WritePin(DB2_LCD_GPIO_Port, DB2_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB2_LCD_GPIO_Port, DB2_LCD_Pin, RESET);
	}

	if(Y_address & 0b00001000){
		HAL_GPIO_WritePin(DB3_LCD_GPIO_Port, DB3_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB3_LCD_GPIO_Port, DB3_LCD_Pin, RESET);
	}

	if(Y_address & 0b00010000){
		HAL_GPIO_WritePin(DB4_LCD_GPIO_Port, DB4_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB4_LCD_GPIO_Port, DB4_LCD_Pin, RESET);
	}

	if(Y_address & 0b00100000){
		HAL_GPIO_WritePin(DB5_LCD_GPIO_Port, DB5_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB5_LCD_GPIO_Port, DB5_LCD_Pin, RESET);
	}

	Delay_us(1);

	E_Pulse();

	return 1;
}

int Set_Page(uint8_t X_address){

	if(X_address < 0 || X_address >= 8){
		return 0;
	}

	HAL_GPIO_WritePin(DB7_LCD_GPIO_Port, DB7_LCD_Pin, SET);
	HAL_GPIO_WritePin(DB6_LCD_GPIO_Port, DB6_LCD_Pin, RESET);
	HAL_GPIO_WritePin(D_I_LCD_GPIO_Port, D_I_LCD_Pin, RESET);
	HAL_GPIO_WritePin(Dir_R_W_LCD_GPIO_Port, Dir_R_W_LCD_Pin, RESET);

	HAL_GPIO_WritePin(DB3_LCD_GPIO_Port, DB3_LCD_Pin, SET);
	HAL_GPIO_WritePin(DB4_LCD_GPIO_Port, DB4_LCD_Pin, SET);
	HAL_GPIO_WritePin(DB5_LCD_GPIO_Port, DB5_LCD_Pin, SET);

	if(X_address & 0b00000001){
		HAL_GPIO_WritePin(DB0_LCD_GPIO_Port, DB0_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB0_LCD_GPIO_Port, DB0_LCD_Pin, RESET);
	}

	if(X_address & 0b00000010){
		HAL_GPIO_WritePin(DB1_LCD_GPIO_Port, DB1_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB1_LCD_GPIO_Port, DB1_LCD_Pin, RESET);
	}

	if(X_address & 0b00000100){
		HAL_GPIO_WritePin(DB2_LCD_GPIO_Port, DB2_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB2_LCD_GPIO_Port, DB2_LCD_Pin, RESET);
	}

	Delay_us(1);

	E_Pulse();

	return 1;
}


void E_Pulse(){
	HAL_GPIO_WritePin(E_LCD_GPIO_Port, E_LCD_Pin, SET);

	//HAL_Delay(1);
	Delay_us(1);


	HAL_GPIO_WritePin(E_LCD_GPIO_Port, E_LCD_Pin, RESET);
}

void Delay_us(volatile uint32_t microseconds)
{
	uint32_t delay_loops = (SystemCoreClock / 1000000) * microseconds;
	//  ciklus overhead kompenzálása egy osztóval
	delay_loops = ( (SystemCoreClock / 1000000) * microseconds ) / 6; // lehet, hogy a 6 helyett más kell majd
	if (delay_loops == 0 && microseconds > 0) delay_loops = 1;

	for (volatile uint32_t i = 0; i < delay_loops; ++i)
	{
		__NOP();
	}
}

void Write_Data_Bits(uint8_t data){

	if(data & 0b00000001){
		HAL_GPIO_WritePin(DB0_LCD_GPIO_Port, DB0_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB0_LCD_GPIO_Port, DB0_LCD_Pin, RESET);
	}

	if(data & 0b00000010){
		HAL_GPIO_WritePin(DB1_LCD_GPIO_Port, DB1_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB1_LCD_GPIO_Port, DB1_LCD_Pin, RESET);
	}

	if(data & 0b00000100){
		HAL_GPIO_WritePin(DB2_LCD_GPIO_Port, DB2_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB2_LCD_GPIO_Port, DB2_LCD_Pin, RESET);
	}

	if(data & 0b00001000){
		HAL_GPIO_WritePin(DB3_LCD_GPIO_Port, DB3_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB3_LCD_GPIO_Port, DB3_LCD_Pin, RESET);
	}

	if(data & 0b00010000){
		HAL_GPIO_WritePin(DB4_LCD_GPIO_Port, DB4_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB4_LCD_GPIO_Port, DB4_LCD_Pin, RESET);
	}

	if(data & 0b00100000){
		HAL_GPIO_WritePin(DB5_LCD_GPIO_Port, DB5_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB5_LCD_GPIO_Port, DB5_LCD_Pin, RESET);
	}

	if(data & 0b01000000){
		HAL_GPIO_WritePin(DB6_LCD_GPIO_Port, DB6_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB6_LCD_GPIO_Port, DB6_LCD_Pin, RESET);
	}
	if(data & 0b10000000){
		HAL_GPIO_WritePin(DB7_LCD_GPIO_Port, DB7_LCD_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(DB7_LCD_GPIO_Port, DB7_LCD_Pin, RESET);
	}

}



void Draw_R_Letter(){

	HAL_GPIO_WritePin(CS1_LCD_GPIO_Port, CS1_LCD_Pin, RESET);
	HAL_GPIO_WritePin(CS2_LCD_GPIO_Port, CS2_LCD_Pin, RESET);



	uint8_t R_array[] = {0, 0x7f, 0x09, 0x19, 0x29, 0x46};

	Set_Coloumn(0);
	Set_Page(0);

	HAL_GPIO_WritePin(D_I_LCD_GPIO_Port, D_I_LCD_Pin, SET);
	HAL_GPIO_WritePin(Dir_R_W_LCD_GPIO_Port, Dir_R_W_LCD_Pin, RESET);


	for(int i = 0; i < 6; i++){

		Write_Data_Bits(R_array[i]);
		HAL_Delay(10);
		E_Pulse();

	}
}



