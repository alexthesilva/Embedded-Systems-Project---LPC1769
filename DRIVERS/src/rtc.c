#include "rtc.h"


//HAL
void RTC_Init ( time_t seconds ){
	RTC_HallInit (  );

	//Segundos desde 1 janeiro 1970
    if(seconds!=0)
    	time(&seconds);							//Atribui o valor em segundos
}

//HAL
void RTC_GetValue ( struct tm *dateTime ){
	RTC_HallGetValue ( dateTime );

}

//HAL
void RTC_SetValue ( struct tm *dateTime ){
	RTC_HallSetValue ( dateTime );

}


void RTC_SetSeconds ( time_t seconds ){
	time(&seconds);							//Atribui o valor em segundos
}


time_t RTC_GetSeconds ( void){
	return time(NULL);						////Retorna os segundos que passaram
}
