cmake_minimum_required(VERSION 3.16)
project(ScoreArena)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

#include(FetchContent)
#FetchContent_Declare(SFML
    #GIT_REPOSITORY https://github.com/SFML/SFML.git
    #GIT_TAG 2.6.x)
#FetchContent_MakeAvailable(SFML)

add_subdirectory(thirdparty)

set(ScoreArena-SRC
	main.cpp
	arsenal.h arsenal.cpp
	attackArsenal.h attackArsenal.cpp
	chooser.h chooser.cpp
	map.h map.cpp
	mapIcon.h mapIcon.cpp
	menu.h menu.cpp
	message.h message.cpp
	player.h player.cpp
	point.h point.cpp
	power.h power.cpp
	selector.h selector.cpp
	res/
	)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ScoreArena)
add_executable( ScoreArena ${ScoreArena-SRC} )

target_link_libraries(ScoreArena PRIVATE sfml-system sfml-window sfml-graphics)
include_directories(ScoreArena ${SFML_INCLUDE_DIR})

if(WIN32)
    add_custom_command(
        TARGET ScoreArena
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:ScoreArena>
        VERBATIM)
endif()

install(TARGETS ScoreArena)