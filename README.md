[![Build server](https://github.com/engineerjames/men-among-gods/actions/workflows/build.yml/badge.svg)](https://github.com/engineerjames/men-among-gods/actions/workflows/build.yml)

# men-among-gods

Men Among Gods is based on the Mercenaries of Astonia engine by Daniel Brockhaus

## Useful Item #'s

Once you have made yourself a god, you can create items via `/create`:

### Quest Items
* 105 - Jamal's Amulet
* 113 - Golden belt (enhance weapon), (Sirjan)
* 115 - Ruby from skeleton area
* 127 - Greater Healing Potion (Ingrid)
* 107 - Ruby Amulet (Cirrus)
* 129 - Barbarians sword
* 118 - Joe's armor
* 131 - Greater Mana Potion (Magic Maze)
* 148 - Potion of Life
* 136 - Sword of Stealth
* 191 - Amulet of Resistance
* 338 - Silver Ring
* 337 - Plain Golden Ring
* 693 - bless of Skua
* 370 - Gold ring / big sapphires
* 781 - Golden belt with saphire
* 492 - Huge saph on gold
* 524 - tit sword
* 833 - gpot
* 768 - Ankh Amulet
* 1201 - ring of prophet

### Useful Positions
* 607,499 - Entrance to labrynth

### Building on Windows
1. Install MSYS, follow the instructions here: https://www.msys2.org/
2. Add <MSYS_INSTALL_DIR>/usr/bin and <MSYS_INSTALL_DIR>/mingw64/bin to your path in Windows
3. Use `pacman` to install all dependencies:
```bash
pacman -Syu # After this command, restart the MSYS executable
pacman -Su
pacman -S --needed base-devel mingw-w64-x86_64-toolchain # Hit enter to select all packages, ~1GB

# Remainder of build dependencies
pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-boost git mingw-w64-x86_64-sfml mingw-w64-x86_64-libzip
```
4. Install CMake (in Windows), and add its binary directory to the Windows system path
5. Use CMake from a regular command prompt at the top level of the repository to build via:
```bash
cmake -G"MinGW Makefiles" -S ./ -B ./build
cmake --build ./build --parallel
```
> Note: Do not attempt to run "Make" from the build directory as you normally could do; it will not work.
6. Run the executable as you normally would.

Alternatively, you can install WSL2 (Windows Subsystem for Linux - 2) via [this guide](https://www.digitalocean.com/community/tutorials/how-to-install-the-windows-subsystem-for-linux-2-on-microsoft-windows-10).  Note, you will need to install Xming (and follow the instructions outlined [here](https://stackoverflow.com/questions/61110603/how-to-set-up-working-x11-forwarding-on-wsl2)) in order to display the GUI to your Windows desktop via the X11 server.

### Building on Windows with VCPKG
1. [Follow the instructions to install VCPKG](https://vcpkg.io/en/getting-started.html) - Add the vcpkg binary to the system path
2. Clone the repository (after installing Microsoft Visual Studio of some variety)
3. Install CMake, and add its binary directory to the Windows system path
4. Load up the CMake-GUI--select the source and build directories and VCPKG should do the rest.
