# DDL_robot
Francesca: The cutest lil robot 


#define ADCRES 12
#define ADCMAX (2<<ADCRES-1)
#define REFVOLT 3.3
#define UNITCONVERSION 2.54
#define SENSORCONST 27

float distance_calc(uint16_t raw){
	return SENSORCONST/(UNITCONVERSION*raw/ADCMAX*REFVOLT);
}
