CC=emcc
SOURCES:=main.cpp $(wildcard src/*.cpp) $(wildcard src/imgui/*.cpp)
LDFLAGS=-O2 --llvm-opts 2
OUTPUT=out/bossrushzero.js
INCLUDE=-Isrc -Isrc/imgui -I/usr/local/include/
FLAGSS=-std=c++11 -s USE_OGG=1 -s USE_VORBIS=1 -s USE_GLFW=3 -s USE_WEBGL2=1 -s ALLOW_MEMORY_GROWTH=1 -s ASSERTIONS=1 -s WASM=1 -lGLU -lGL -lopenal --preload-file data

#-s USE_WEBGL2=1 

all: $(SOURCES) $(OUTPUT)

$(OUTPUT): $(SOURCES) 
	$(CC) $(SOURCES) $(LDFLAGS) $(INCLUDE) -o $(OUTPUT) $(FLAGSS)

clean:
	rm $(OUTPUT)
	
