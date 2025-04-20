game.exe: game.c player.c enemy.c bomb.c explosion.c
	gcc game.c player.c enemy.c bomb.c explosion.c -o game.exe -I. -L. -I ../glfw/include -L ../glfw/lib -I ../gl2d/include -L ../gl2d/lib -lgl2d -lglfw -lopengl32 -lglu32

clean:
	del game.exe
