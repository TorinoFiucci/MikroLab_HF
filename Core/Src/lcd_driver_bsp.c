#include "lcd_driver_bsp.h"
#include "main.h"


void Display_On(){

HAL_GPIO_WritePin(_RST_LCD_GPIO_Port, _RST_LCD_Pin, SET);

HAL_Delay(10);

HAL_GPIO_WritePin(CS1_LCD_GPIO_Port, CS1_LCD_Pin, RESET);
HAL_GPIO_WritePin(CS2_LCD_GPIO_Port, CS2_LCD_Pin, RESET);

HAL_Delay(10);

HAL_GPIO_WritePin(D_I_LCD_GPIO_Port, D_I_LCD_Pin, RESET);

HAL_GPIO_WritePin(Dir_R_W_LCD_GPIO_Port, Dir_R_W_LCD_Pin, RESET);

HAL_Delay(10);

HAL_GPIO_WritePin(DB7_LCD_GPIO_Port, DB7_LCD_Pin, RESET);
HAL_GPIO_WritePin(DB6_LCD_GPIO_Port, DB6_LCD_Pin, RESET);

HAL_GPIO_WritePin(DB1_LCD_GPIO_Port, DB1_LCD_Pin, SET);
HAL_GPIO_WritePin(DB2_LCD_GPIO_Port, DB2_LCD_Pin, SET);
HAL_GPIO_WritePin(DB3_LCD_GPIO_Port, DB3_LCD_Pin, SET);
HAL_GPIO_WritePin(DB4_LCD_GPIO_Port, DB4_LCD_Pin, SET);
HAL_GPIO_WritePin(DB5_LCD_GPIO_Port, DB5_LCD_Pin, SET);

HAL_GPIO_WritePin(DB0_LCD_GPIO_Port, DB0_LCD_Pin, SET);

HAL_Delay(10);

E_Pulse();

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

	HAL_Delay(10);

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

		HAL_Delay(10);

		E_Pulse();

		return 1;
}


void E_Pulse(){
	HAL_GPIO_WritePin(E_LCD_GPIO_Port, E_LCD_Pin, SET);

	HAL_Delay(1);

	HAL_GPIO_WritePin(E_LCD_GPIO_Port, E_LCD_Pin, RESET);
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
