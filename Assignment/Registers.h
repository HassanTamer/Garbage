/* RCC AHB1 Clock Register */
#define RCC_AHB1ENR   (*((unsigned long volatile *)(0x40023830) ) )
/* Port_B I/O Registers */
#define GPIOB_MODER   (*((unsigned long volatile *)(0x40020400) ) )
#define GPIOB_IDR     (*((unsigned long volatile *)(0x40020410) ) )
#define GPIOB_ODR     (*((unsigned long volatile *)(0x40020414) ) )


/*RCC APB1 peripheral clock enable register*/
#define RCC_APB1ENR   (*((unsigned long volatile *)(0x40023840) ) )
  /*   I2C   Registers Mapping         */
#define I2C1_CR1      (*((unsigned long volatile *)(0x40005400) ) )

#define I2C1_OAR1     (*((unsigned long volatile *)(0x40005408) ) )

#define I2C1_OAR2     (*((unsigned long volatile *)(0x4000540C) ) )

#define I2C1_DR       (*((unsigned long volatile *)(0x40005410) ) )

#define I2C1_SR1      (*((unsigned long volatile *)(0x40005414) ) )

#define I2C1_SR2      (*((unsigned long volatile *)(0x40005418) ) )

#define I2C1_CCR      (*((unsigned long volatile *)(0x4000541C) ) )

#define I2C1_TRISE    (*((unsigned long volatile *)(0x40005420) ) )
































































































































































// .. / .-- .- -. - / - --- / ..-. ..- -.-. -.- .. -. --. / -.- .. .-.. .-.. / -- -.-- ... . .-.. ..-.