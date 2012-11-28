# Project: Pong

CPP  = g++.exe
CC   = gcc.exe
WINDRES = windres.exe
RES  = pong_private.res
OBJ  = pong.o ball.o paddle.o font.o keyPress.o $(RES)
LINKOBJ  = pong.o ball.o paddle.o font.o keyPress.o $(RES)
LIBS =  -L"C:/Dev-Cpp/lib" -mwindows -lopengl32  
INCS =  -I"C:/Dev-Cpp/include" 
CXXINCS =  -I"C:/Dev-Cpp/lib/gcc/mingw32/3.4.2/include"  -I"C:/Dev-Cpp/include/c++/3.4.2/backward"  -I"C:/Dev-Cpp/include/c++/3.4.2/mingw32"  -I"C:/Dev-Cpp/include/c++/3.4.2"  -I"C:/Dev-Cpp/include" 
BIN  = Pong.exe
CXXFLAGS = $(CXXINCS)  
CFLAGS = $(INCS)  
DEL = del

.PHONY: all all-before all-after clean clean-custom

all: all-before Pong.exe all-after


clean: clean-custom
	${DEL} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "Pong.exe" $(LIBS)

pong.o: pong.cpp
	$(CPP) -c pong.cpp -o pong.o $(CXXFLAGS)

ball.o: ball.cpp
	$(CPP) -c ball.cpp -o ball.o $(CXXFLAGS)

paddle.o: paddle.cpp
	$(CPP) -c paddle.cpp -o paddle.o $(CXXFLAGS)

font.o: font.cpp
	$(CPP) -c font.cpp -o font.o $(CXXFLAGS)

keyPress.o: keyPress.cpp
	$(CPP) -c keyPress.cpp -o keyPress.o $(CXXFLAGS)

pong_private.res: pong_private.rc pong.rc 
	$(WINDRES) -i pong_private.rc --input-format=rc -o pong_private.res -O coff 
