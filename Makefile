CFLAGS=-Wall -g `pkg-config --cflags gtk+-3.0 appindicator3-0.1 libnotify`
LIBS=`pkg-config --libs gtk+-3.0 appindicator3-0.1 libnotify`
SRC_PATH = ./src
BIN_PATH = ./bin

all:
	gcc ${CFLAGS} ${SRC_PATH}/main.c ${LIBS} -o ${BIN_PATH}/main
clean:
	rm -f ${BIN_PATH}/main
run:
	${BIN_PATH}/main
