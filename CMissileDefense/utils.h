#ifndef UTILS_H
#define UTILS_H

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<math.h>

void die(char *format,...);

double distance(double x1,double y1,double x2,double y2);
double radians(double degrees);
double degrees(double radians);

#endif
