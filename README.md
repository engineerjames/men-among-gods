[![Build server](https://github.com/engineerjames/men-among-gods/actions/workflows/build.yml/badge.svg)](https://github.com/engineerjames/men-among-gods/actions/workflows/build.yml)

# men-among-gods

Men Among Gods is based on the Mercenaries of Astonia engine by Daniel Brockhaus.  Currently, the developmental focus is on eliminating the use of the DirectDraw graphics API in favor of [SFML](https://www.sfml-dev.org/).  While SFML supports cross platform development, the initial focus is on porting the legacy capabilities into the Windows client.

Currently you can connect to a server and play the game mostly as you would expect.

### Building the client on Windows with VCPKG
1. [Follow the instructions to install VCPKG](https://vcpkg.io/en/getting-started.html) - Add the vcpkg binary to the system path
2. Clone the repository (after installing Microsoft Visual Studio of some variety)
3. Install CMake, and add its binary directory to the Windows system path
4. Load up the CMake-GUI--select the source and build directories and VCPKG should do the rest.
5. Alternatively, you could open VSCode from a Developer Command Prompt (to ensure that the MSVC compiler is on your PATH)

Once you have everything build with CMake, you will want to manually execute the `create_release` CMake target.  This will copy all the required libraries, configuration files, and graphics to a centralized location.  You can then copy everything from <build_dir>/client_files to src/tauri_frontend/resources.  Then, in order to build and test the new front-end application you can navigate to the src/tauri_frontend folder and run `pnpm run tauri dev`.

Alternatively, you can run the `create_release_packages` script--this will do all the aforementioned steps and build the two installers (.msi and NSIS .exe).

### Further instructions TBD - Most up to date information will be held on the Wiki.
