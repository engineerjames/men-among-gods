[![CMake](https://github.com/engineerjames/men-among-gods/actions/workflows/cmake.yml/badge.svg)](https://github.com/engineerjames/men-among-gods/actions/workflows/cmake.yml)

# men-among-gods

Men Among Gods is based on the Mercenaries of Astonia engine by Daniel Brockhaus

## Useful Item #'s

Once you have made yourself a god, you can create items via `/createitem`:

### Quest Items
105 - Jamal's Amulet
113 - Golden belt (enhance weapon), (Sirjan)
115 - Ruby from skeleton area
127 - Greater Healing Potion (Ingrid)
107 - Ruby Amulet (Cirrus)
129 - Barbarians sword
118 - Joe's armor
131 - Greater Mana Potion (Magic Maze)
148 - Potion of Life
136 - Sword of Stealth
191 - Amulet of Resistance
338 - Silver Ring
337 - Plain Golden Ring
693 - bless of Skua
370 - Gold ring / big sapphires
781 - Golden belt with saphire
492 - Huge saph on gold
524 - tit sword
833 - gpot
768 - Ankh Amulet
1201 - ring of prophet

### Useful Positions
607,499 - Entrance to labrynth

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
6. Run from MSYS terminal
