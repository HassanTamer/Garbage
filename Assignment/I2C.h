#include <stdint.h>
#include "Registers.h"

#define MaxFreq 50
#define MinFreq 2
#define TrSCL 1.0
#define TwSCLH 4.0


uint8_t ccr;
uint8_t trise;

void begin(int8_t addr);
void requestFrom(uint8_t addr, uint8_t quantity);
uint8_t available(void);
void Write(uint8_t data);
void end(void);
void setClock(uint8_t freq);