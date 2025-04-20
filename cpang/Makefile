game.exe: player.c bubble.c harpoon.c
	gcc game.c player.c bubble.c harpoon.c -o game.exe -I. -L. -I ../glfw/include -L ../glfw/lib -I ../gl2d/include -L ../gl2d/lib -lgl2d -lglfw -lopengl32 -lglu32 

.PHONY: clean

clean:
	del game.exe
