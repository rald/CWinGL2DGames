game.e: main.c utils.c list.c turret.c missile.c explosion.c building.c
	gcc main.c utils.c list.c turret.c missile.c explosion.c building.c -o game.exe -I. -L. -I ../glfw/include -L ../glfw/lib -I gl2d/include -L gl2d/lib -lgl2d -lglfw -lopengl32 -lglu32

clean:
	del game.exe
