### CMake instructions -- skip to next section if you've done this already

Make sure that you have the following version of Visual Studio:
Visual Studio (17) 2022 Community Edition

This will create and link the necessary files as well as build the project. The build folder is blocked off
because it's not necessary for the repository.

### I'm ready, let's build

### Steps for Windows

cd back to the root directory and into the build folder. Run:<br />
cmake ..<br />
cmake --build .<br />

### Steps for Linux

First things first, we need to get into the linux branch to build the project properly:<br />
git checkout linux<br />
The thirdparty/SFML folder should be empty, so cd into thirdparty. From there, type git clone https://github.com/SFML/SFML to get your SFML root directory.

On some Linux distributions, certain libraries need to be installed prior to running the CMake script. These libs worked for me,
but may vary on different linux distributions:<br />
libx11-dev<br />
libgl1-mesa-dev<br />
libudev-dev<br />
libxrandr-dev<br />
libxcursor-dev<br />
libfreetype-dev<br />
libopenal-dev<br />
libvorbis-dev<br />
libflac-dev<br />

You'll likely need to restart the OS after installing these libraries prior to the CMake.<br />

In the root directory, cd into thirdparty/SFML. Run:
<br />
mkdir build && cd build<br />
cmake ..<br />
make -j 8<br />

That's it! Your sfml libs should be available in thirdparty/SFML/build/lib.
