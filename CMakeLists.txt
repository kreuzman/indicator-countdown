project(indicator-countdown)
cmake_minimum_required(VERSION 3.6)

find_package(PkgConfig REQUIRED)
pkg_check_modules(DEPENDENCIES REQUIRED gtk+-3.0 appindicator3-0.1 libnotify gmodule-2.0)

include_directories(${DEPENDENCIES_INCLUDE_DIRS})
link_directories(${DEPENDENCIES_LIBRARY_DIRS})
add_definitions(${DEPENDENCIES_CFLAGS_OTHER})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(SOURCE_FILES src/countdown.c src/indicator.c src/about_dialog.c src/main.c src/preferences_dialog.c src/settings.c)

add_custom_target(install-test sudo cp ./resources/com.kreuzman.indicator.countdown.gschema.xml /usr/share/glib-2.0/schemas && sudo glib-compile-schemas)
add_executable(indicator-countdown ${SOURCE_FILES})

target_link_libraries(indicator-countdown ${DEPENDENCIES_LIBRARIES})
