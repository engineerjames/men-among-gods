[![Build server](https://github.com/engineerjames/men-among-gods/actions/workflows/build.yml/badge.svg)](https://github.com/engineerjames/men-among-gods/actions/workflows/build.yml)

# men-among-gods

Men Among Gods is based on the Mercenaries of Astonia engine by Daniel Brockhaus.  Currently, the developmental focus is on eliminating the use of the DirectDraw graphics API in favor of [SFML](https://www.sfml-dev.org/).  While SFML supports cross platform development, the initial focus is on porting the legacy capabilities into the Windows client.

The legacy client front-end has been replaced with electron, but is still in a fairly infantile state.  Currently you can connect to a server and play the game mostly as you would expect.

### Building the client on Windows with VCPKG
1. [Follow the instructions to install VCPKG](https://vcpkg.io/en/getting-started.html) - Add the vcpkg binary to the system path
2. Clone the repository (after installing Microsoft Visual Studio of some variety)
3. Install CMake, and add its binary directory to the Windows system path
4. Load up the CMake-GUI--select the source and build directories and VCPKG should do the rest.

### Further instructions TBD - Most up to date information will be held on the Wiki.
Docker build commands:
sudo docker build -t men-among-gods -f ./server.Dockerfile ./
sudo docker run -p <hostPort>:5555 <imageName>