#include "turret.h"

Turret *Turret_New(double x,double y,double radius,double heading,double lifeMax,GLuint stroke,GLuint fill) {
  Turret *turret=malloc(sizeof(*turret));
  if(turret) {
    turret->x1=x;
    turret->y1=y;
    turret->x2=x;
    turret->y2=y;
    turret->radius=radius;
    turret->heading=heading;
    turret->stroke=stroke;
    turret->fill=fill;
    turret->lifeMax=lifeMax;
    turret->life=lifeMax;
  }
  return turret;
}

void Turret_Update(Turret *turret) {
  turret->heading=atan2(mouseY-turret->y1,mouseX-turret->x1);
	turret->x2=turret->radius*cos(turret->heading)+turret->x1;
	turret->y2=turret->radius*sin(turret->heading)+turret->y1;
}

void Turret_Draw(Turret *turret) {
  double radius=turret->life/turret->lifeMax*turret->radius;
  glEllipseFilled(turret->x1,turret->y1,radius,radius,0,turret->fill);
  glEllipse(turret->x1,turret->y1,turret->radius,turret->radius,0,turret->stroke);
  glLine(turret->x1,turret->y1,turret->x2,turret->y2,turret->stroke);
}

void Turret_Delete(Turret *turret) {
  free(turret);
  turret=NULL;
}
