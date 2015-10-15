CFLAGS=-Wall -g `pkg-config --cflags gtk+-3.0 appindicator3-0.1 libnotify`
LIBS=`pkg-config --libs gtk+-3.0 appindicator3-0.1 libnotify`
SRC_PATH = ./src
BIN_PATH = ./bin

all:
	gcc ${CFLAGS} ${SRC_PATH}/indicator-countdown.c ${LIBS} -o ${BIN_PATH}/indicator-countdown
clean:
	rm -f ${BIN_PATH}/indicator-countdown
run:
	${BIN_PATH}/indicator-countdown
