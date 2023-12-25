#include "I2C.h"
uint8_t temp;      //temp variable to read SR1 and SR2 to clear ADDR flag
uint8_t dataFlag;  // a flag to detect if the transmitted bytes are more more than 1 byte


void main() {
}

void begin(int8_t addr) {
  // Enable the I2C CLOCK and GPIO CLOCK
  RCC_APB1ENR |= (1 << 21);  // enable I2C1 CLOCK
  RCC_AHB1ENR |= (1 << 1);   // Enable GPIOB CLOCK


  // Configure the I2C PINs for ALternate Functions
  GPIOB_MODER |= (2 << 16) | (2 << 18);    // Bits (17:16)= 1:0 --> Alternate Function for Pin PB8; Bits (19:18)= 1:0 --> Alternate Function for Pin PB9
  GPIOB_OTYPER |= (1 << 8) | (1 << 9);     //  Bit8=1, Bit9=1  output open drain
  GPIOB_OSPEEDR |= (3 << 16) | (3 << 18);  // Bits (17:16)= 1:1 --> High Speed for PIN PB8; Bits (19:18)= 1:1 --> High Speed for PIN PB9
  GPIOB_PUPDR |= (1 << 16) | (1 << 18);    // Bits (17:16)= 0:1 --> Pull up for PIN PB8; Bits (19:18)= 0:1 --> pull up for PIN PB9
  GPIOB_AFRH |= (4 << 0) | (4 << 4);       // Bits (3:2:1:0) = 0:1:0:0 --> AF4 for pin PB8;  Bits (7:6:5:4) = 0:1:0:0 --> AF4 for pin PB9

  // Reset the I2C
  I2C1_CR1 |= (1 << 15);
  I2C1_CR1 &= ~(1 << 15);  // Normal operation
  setClock(45);            //if clock not set ...the default frequency is 45MHZ
  // Program the I2C_CR1 register to enable the peripheral
  I2C1_CR1 |= (1 << 0);  // Enable I2C
   switch (addr) {
    case -1:  //master mode
      // master send start condition
      I2C1_CR1 |= (1 << 10);  // Enable the ACK
      I2C1_CR1 |= (1 << 8);   // Generate START
      while (!(I2C1_SR1 & (1 << 0)))
        ;  // Wait fror SB bit to set
      break;

    default:
      I2C1_OAR1 &= ~(1 << 15);      // set the 15th bit in I2C1_OAR1 to zero for 7-bit addressing mode
      I2C1_OAR1 = (addr << 1) | 0;  // Set the address(addr -> 8 bits) of slave in bits from 1 to 8 (since we use 7bit address mode the 8th bit is don't care)
      break;
  }
 }
  void setClock(uint8_t freq) {
    if (freq < MinFreq) freq = MinFreq;
    if (freq > MaxFreq) freq = MaxFreq;
    ccr = (TrSCL + TwSCLH) * freq;  //CCR = (Tr(SCL) + Tw(SCLH)) / TPCLK1 = 1us + 4us / (1/freq)us
    trise = TrSCL * freq + 1;       // TRISE = TrSCL / TPCLK1
    // Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
    I2C1_CR2 |= (freq << 0);  // PCLK1 FREQUENCY in MHz
    // Configure the clock control registers
    I2C1_CCR = ccr << 0;

    // Configure the rise time register
    I2C1_TRISE = trise;
    // the calculations are for operation in standard mode not fm...
  }
  

void requestFrom(uint8_t addr, uint8_t quantity) {
  I2C1_DR = addr;
  while (!(I2C1_SR1 & (1 << 0)));                                  // Wait fror ADDR bit to set (address matched)
  uint8_t temp = I2C1_SR1 | I2C1_SR2;  //read SR1 and SR2 to clear ADDR bit
  if (quantity == 1) { dataFlag = 0 };
    else if (quantity > 1) {
    dataFlag = 1
  };
}

void Write(uint8_t data) {
  while (!(I2C1_SR1 & (1 << 7)))
    ;  // wait for TXE bit to set
  I2C1_DR = data;
  while (!(I2C1_SR1 & (1 << 2)))
    ;  // wait for BTF bit to set
}
uint8_t available(void) {
  /* Check if RxNE (Receive buffer not empty) bit is set */
  if (I2C1_SR1 & (1 << 6)) {
    return 1;  // Data is available
  } else {
    return 0;  // No data available
  }
}
void end(void) {
  I2C1_CR1 |= (1 << 9);   // set the 9th bit in CR1 to stop the I2c after the current byte transfer
  I2C1_CR1 &= ~(1 << 0);  // disable the I2C1 peripheral
}
