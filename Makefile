CFLAGS=-Wall -g `pkg-config --cflags gtk+-3.0 appindicator3-0.1 libnotify gmodule-2.0`
LIBS=`pkg-config --libs gtk+-3.0 appindicator3-0.1 libnotify gmodule-2.0`
SRC_PATH = ./src
BIN_PATH = ./bin
RESOURCES_PATH = ./resources
ICONS_PATH = ./icons

SOURCES = ${SRC_PATH}/countdown.c ${SRC_PATH}/about_dialog.c ${SRC_PATH}/indicator.c ${SRC_PATH}/main.c ${SRC_PATH}/preferences_dialog.c

all:
	rm -f ${BIN_PATH}/main && gcc ${CFLAGS} ${SOURCES} ${LIBS} -o ${BIN_PATH}/main && ${BIN_PATH}/main
install:
	sudo cp ${RESOURCES_PATH}/com.kreuzman.indicator.countdown.gschema.xml /usr/share/glib-2.0/schemas && sudo glib-compile-schemas /usr/share/glib-2.0/schemas && sudo cp -R ${ICONS_PATH}/* /usr/share/icons && sudo update-icon-caches /usr/share/icons/*
clean:
	rm -f ${BIN_PATH}/main
build:
	gcc ${CFLAGS} ${SOURCES} ${LIBS} -o ${BIN_PATH}/main
run:
	${BIN_PATH}/main
run-valgrind:
	valgrind ${BIN_PATH}/main --track-origins=yes --leak-check=full
release:
	gcc ${CFLAGS} ${SOURCES} ${LIBS} -o ${BIN_PATH}/indicator-countdown
