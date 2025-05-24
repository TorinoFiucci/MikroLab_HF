#include "main.h"

void Display_On();
void Display_Off();
void Clear_Display();
int Set_Coloumn(uint8_t Y_address);
int Set_Page(uint8_t X_address);
void E_Pulse();

void Write_Data_Bits(uint8_t data);

void Draw_R_Letter();
void LCD_Buffer_Init();
void LCD_Set_Pixel(uint8_t x, uint8_t y, uint8_t color);
void LCD_Refresh_Display();
void Delay_us(volatile uint32_t microseconds);
