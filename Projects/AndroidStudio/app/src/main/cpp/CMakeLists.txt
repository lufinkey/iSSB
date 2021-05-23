# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.10.2)

project("issb")

# Add flags
add_definitions(-DSMASHBROS_P2P_DISABLE -DSMASHBROS_SCRIPT_DISABLE)
option(SUPPORT_OGG "Support loading OGG Vorbis music via Tremor" ON)

# Add Dependency Directories
set(ISSB_EXTERNAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../External")
add_subdirectory("${ISSB_EXTERNAL_DIR}/SDL/SDL" "${CMAKE_BINARY_DIR}/SDL2")
add_subdirectory("${ISSB_EXTERNAL_DIR}/SDL/SDL_image" "${CMAKE_BINARY_DIR}/SDL2_image")
add_subdirectory("${ISSB_EXTERNAL_DIR}/SDL/SDL_mixer" "${CMAKE_BINARY_DIR}/SDL2_mixer")
#add_subdirectory("${ISSB_EXTERNAL_DIR}/SDL/SDL_ttf/external/freetype-2.9.1" "${CMAKE_BINARY_DIR}/freetype")
add_subdirectory("${ISSB_EXTERNAL_DIR}/SDL/SDL_ttf" "${CMAKE_BINARY_DIR}/SDL2_ttf")
include_directories("${ISSB_EXTERNAL_DIR}/SDL/SDL_p2p/include")

# find iSSB source files
file(
		GLOB_RECURSE
		ISSB_SOURCES
		../../../../../../Source/*.cpp ../../../../../../Source/*.mm)

# find SDL_p2p source files
file(
		GLOB_RECURSE
		SDL_P2P_SOURCES
		../../../../../../External/SDL/SDL_p2p/src/*.cpp)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
			iSSBLib
			# Sets the library as a shared library.
			SHARED

			# Provides a relative path to your source file(s).
			native-lib.cpp
			${ISSB_SOURCES}
			${SDL_P2P_SOURCES})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
					iSSBLib

					SDL2 SDL2_image SDL2_mixer SDL2_ttf

					# Links the target library to the log library
					# included in the NDK.
					${log-lib} )