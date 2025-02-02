build:
	g++ *.cpp **/*.cpp -o snake -lraylib

run:
	./snake  

clean:
	rm snake

brc:
	make build && make run && make clean

build-web:
	emcc -o snake.html *.cpp **/*.cpp -Os -Wall -std=c++11 \
		/home/${USER}/raylib/src/web/libraylib.web.a \
		-I. -I /home/${USER}/raylib/src \
		-L. -L /home/${USER}/raylib/src \
		-s USE_GLFW=3 \
		-s ASYNCIFY \
		--shell-file /home/${USER}/raylib/src/shell.html \
		-DPLATFORM_WEB
