

/* Function to send the command to LCD */
void cmd_write(char cmd)
{
  LcdDataBus=cmd;    // Send the command to LCD
  LCD_RS=0;          // Select the Command Register by pulling RS LOW
  LCD_RW=0;          // Select the Write Operation  by pulling RW LOW
  LCD_EN=1;          // Send a High-to-Low Pusle at Enable Pin
  delay_us(10);
  LCD_EN=0;
  delay_us(1000);
}

/* Function to send the Data to LCD */
void LCD_DataWrite(char dat)
{
    LcdDataBus=dat;	  // Send the data to LCD
    LCD_RS=1;	      // Select the Data Register by pulling RS HIGH
    LCD_RW=0;          // Select the Write Operation by pulling RW LOW
    LCD_EN=1;	      // Send a High-to-Low Pusle at Enable Pin
    delay_us(10);
    LCD_EN=0;
    delay_us(1000);
}

void LCD_command(unsigned char command)
{
    LCD_CTRL_DATA = 0;     	/* RS = 0, R/W = 0 */
    LCD_DATA_DATA = command;
    LCD_CTRL_DATA = EN;    	/* pulse E */
    delayUs(1);		/* Enable pulse Width */
    LCD_CTRL_DATA = 0;
    if (command < 4)
        delayMs(2);         	/* command 1 and 2 needs up to 1.64ms */
    else
        delayUs(40);        /* all others 40 us */
}

void LCD_data(unsigned char data)
{
    LCD_CTRL_DATA = RS;    /* RS = 1, R/W = 0 */
    LCD_DATA_DATA = data;
    LCD_CTRL_DATA = EN | RS;   /* pulse E */
    delayUs(1);
    LCD_CTRL_DATA = 0;
    delayUs(40);

}

void LCD_start(unsigned char command)
{
    delayMs(20);            /* initialization sequence */// Wait >15 ms after power is applied
    LCD_command(0x30);		// command 0x30 = Wake up
    delayMs(5);				// must wait 5ms, busy flag not available
    LCD_command(0x30);		// command 0x30 = Wake up #2
    delayUs(100);			// must wait 100us, busy flag not available
    LCD_command(0x30);		// command 0x30 = Wake up #3
    delayUs(100);			// must wait 100us, busy flag not available
  // Prepare LCD Operation and Function  
    LCD_command(0x38);      /* set 8-bit data, 2-line, 5x7 font */
    LCD_command(0x06);      /* move cursor right */
    LCD_command(0x01);      /* clear screen, move cursor to home */
    LCD_command(0x0F);      /* turn on display, cursor blinking */
}