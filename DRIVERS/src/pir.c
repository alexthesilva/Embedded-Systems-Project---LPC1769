#include "pir.h"
#include "fgpio.h"


//PIR_PIN 13
//PIR_PORT 2
/*
 *
 */
void PIR_Init ( ){
	iotype(PIR_PORT, PIR_PIN, GPIO);
	gpiodir(PIR_PORT, PIR_PIN, IN);

}
/*
 *
 */
bool PIR_GetPresence ( ){
	return gpiordpin(PIR_PORT, PIR_PIN);
}
