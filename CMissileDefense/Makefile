CC=gcc
INCS=-I.
LIBS=-L.
OBJS=main.o gl2d.o utils.o list.o turret.o missile.o explosion.o building.o
EXE=game

%.o: %.c %.h
	$(CC) -c -o $@ $< $(INCS) -Wall -g

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE) $(LIBS) -lglfw -lGL -lGLU -lX11 -lXrender -lXi -lXext -lXdamage -lXrandr -lXxf86vm -lm -lpthread -Wall -g

clean:
	rm $(OBJS) $(EXE)

.PHONY: clean
