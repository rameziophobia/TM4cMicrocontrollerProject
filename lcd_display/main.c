/*
section 14.4 page 902
To enable and initialize the UART, the following steps are necessary: 
1. Enable the UART module using the RCGCUART register (see page 344). 
2. EnabletheclocktotheappropriateGPIOmoduleviatheRCGCGPIOregister(seepage340). 
    To find out which GPIO port to enable, refer to Table 23-5 on page 1351. 
3. SettheGPIO AFSEL bitsfortheappropriatepins(seepage671).To determine
    which GPIOs to configure, see Table 23-4 on page 1344. 
4. Configure the GPIO current level and/or slew rate as specified for the mode 
    selected (see page 673 and page 681).
5. Configure thePMCn fields in the GPIOPCTL register to assign the UART signals
    to the appropriate pins (see page 688 and Table 23-5 on page 1351).

The first thing to consider when programming the UART is the baud-rate divisor (BRD), 
because the UARTIBRD and UARTFBRD registers must be written before the UARTLCRH register. 
Using the equation described in “Baud-Rate Generation” on page 896, 
the BRD can be calculated: BRD = 20,000,000 / (16 * 115,200) = 10.8507 
which means that the DIVINT field of the UARTIBRD register (see page 914) 
should be set to 10 decimal or 0xA. The value to be loaded into the UARTFBRD 
register (see page 915) is calculated by the equation: 
UARTFBRD[DIVFRAC] = integer(0.8507 * 64 + 0.5) = 54 
With the BRD values in hand, the UART configuration is written to the module in
the following order: 
1. Disable the UART by clearing the UARTEN bit in the UARTCTL register. 
2. Write the integer portion of the BRD to the UARTIBRD register. 
3. Write the fractional portion of the BRD to the UARTFBRD register. 
4. Write the desired serial parameters to the UARTLCRH register 
    (in this case, a value of 0x0000.0060). 
5. Configure the UART clock source by writing to the UARTCC register. 
6. Optionally,configuretheµDMAchannel(see“MicroDirectMemoryAccess(µDMA)”onpage585)
    and enable the DMA option(s) in the UARTDMACTL register. 
7. Enable the UART by setting the UARTEN bit in the UARTCTL register. 
*/
int main()
{
  return 0;
}
