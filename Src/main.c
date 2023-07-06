// Where is the LED connected?
// Port: A
// Pin : 5
// offset
//0x4000 0000 + 0x0002 0000 = 0x4002 0000//GPIOAsTARTINGpOINT


#define PERIPH_BASE				(0x40000000UL)
#define AHB1PERIPH_OFFSET		(0x00020000UL)
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET            (0x0000U)	// 0x 0000 0000

#define GPIOA_BASE				(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET				(0x3800UL)
#define RCC_BASE				(AHB1PERIPH_BASE+RCC_OFFSET)

#define AHB1EN_R_OFFSET			(0x30UL)
#define RCC_AHB1EN_R 			(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET)) // AHB ENABLE REG


#define MODE_R_OFFSET			 (0x00UL)
#define GPIOA_MODE_R			 (*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET)) // MOD REG


#define OD_R_OFFSET				 (0x14UL)
#define GPIOA_OD_R			     (*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))	 // OUTPUT DATA REG

#define GPIOAEN					(1U<<0)	// 0.bit = 1 -> 0000 0001

#define PIN5					(1U<<5)
#define LED_PIN					PIN5

/*
 * (1u<<10) // SET BIT 10 TO 1
 * &=~(1U<<11) // SET BIT 11 TO 0 //*/

/*
 * RCC_ahbenr REG = 0b 0000 0000 0000 0000 1000 1111 0000 0000
 * RCC_ahbenr REG = 0b 0000 0000 0000 0000 0000 0000 0000 0001
 * */
int main(void)
{
	/*1.Enable Clock Access to GPIOA*/
	RCC_AHB1EN_R |= GPIOAEN; // 0b 0000 0000 0000 0000 1000 1111 0000 0001
	/*2.Set PA5 as Output Pin*/
	GPIOA_MODE_R |= (1U<<10); // SET BIT 10 TO 1
	GPIOA_MODE_R &=~(1U<<11); // SET BIT 11 TO 0

	while(1)
	{
		/*3.Set PA5 High*/
		GPIOA_OD_R |= LED_PIN;

		/*4:Experiment 2 : Toggle PA5 */
		GPIOA_OD_R ^= LED_PIN; // on off on off on off ? 10101010
		for(int i = 0 ;i<100000;i++){}
	}
}








