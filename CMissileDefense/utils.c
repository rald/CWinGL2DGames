#include "utils.h"



void die(char *format,...) {
	va_list args;
	va_start(args,format);
		vprintf(format,args);
	va_end(args);
	exit(EXIT_FAILURE);
}



double distance(double x1,double y1,double x2,double y2) {
  return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}



double radians(double degrees)  {
	return degrees*M_PI/180.0;
}



double degrees(double radians)  {
	return radians*180.0/M_PI;
}
