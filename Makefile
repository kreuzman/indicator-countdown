CFLAGS=-Wall -g `pkg-config --cflags gtk+-3.0 appindicator3-0.1 libnotify gmodule-2.0`
LIBS=`pkg-config --libs gtk+-3.0 appindicator3-0.1 libnotify gmodule-2.0`
SRC_PATH = ./src
BIN_PATH = ./bin

all:
	rm -f ${BIN_PATH}/main && gcc ${CFLAGS} ${SRC_PATH}/menu_glade.c ${SRC_PATH}/indicator_countdown.c ${LIBS} -o ${BIN_PATH}/main && ${BIN_PATH}/main
clean:
	rm -f ${BIN_PATH}/main
build:
	gcc ${CFLAGS} ${SRC_PATH}/menu_glade.c ${SRC_PATH}/indicator_countdown.c ${LIBS} -o ${BIN_PATH}/main
run:
	${BIN_PATH}/main
run-valgrind:
	valgrind ${BIN_PATH}/main --track-origins=yes
publish:
	gcc ${CFLAGS} ${SRC_PATH}/menu_glade.c ${SRC_PATH}/indicator_countdown.c ${LIBS} -o ${BIN_PATH}/indicator-countdown
