### CMake instructions -- skip to next section if you've done this already

Make sure that you have the following version of Visual Studio:
Visual Studio (17) 2022 Community Edition

In the root directory, make a folder called build and cd into the build folder.
You will be using the following commands:

cmake ..<br />
cmake --build .

This will create and link the necessary files as well as build the project. The build folder is blocked off
because it's not necessary for the repository.

## I'm ready, let's build

In the root directory, cd into thirdparty/SFML-2.6.1. Run:
<br />
cmake ..
<br />

cd back to the root directory and into the build folder. Run:<br />
cmake ..<br />
cmake --build .<br />
=======
This will create and link the necessary files as well as build the project.
