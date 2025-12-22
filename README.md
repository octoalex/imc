# imc

Inline Minecraft launcher, a Minecraft launcher that allows you to easily launch the game from the command line

## Features

None yet :sob:

### Planned

- Launch the game (duh)
- Log in (Legally required feature)
- Create, Import, Edit and Remove Instances (that separate mods, worlds and everything else)
- Download mods, resource packs, shader packs, data packs, and anything else
- Play offline (if you have at least 1 valid login)
- Mod dependency resolution and automatic dependency download
- Automatic download of libraries and assets
- Browse instances, mods, resource packs, shader packs, and data packs
- Use API Keys for services
- Safely store said Login info and API Keys (well, at least not saved unencrypted)
- Java version management

## Commands

none yet :P

## Installing

not yet

## Building

For a more complete guide, check out [the full guide](BUILDING.md)

For a quick build, find the section for your operating system, and just run the commands

### Debian/Ubuntu

```bash
# Install stuff
sudo apt install clang cmake git ninja-build -y
# Clone the repo
git clone https://github.com/octoalex/imc.git
# Prepare the build
mkdir imc/cmake-build-release
cd imc/cmake-build-release
# Configure
cmake -G Ninja -D CMAKE_C_COMPILER=clang -D BUILD_TESTING=OFF -D CMAKE_COMPILE_WARNING_AS_ERROR=OFF \
      -D CMAKE_BUILD_TYPE=Release ..
# Build
cmake --build .
if [ $? -eq 0 ]; then
  echo "The Launcher built successfully! You can find it at app/imc/imc";
fi
```

If the build was successful, the single executable should be found at `cmake-build-release/app/imc/imc` (it's a single
file executable by the way)

## License

All software components are distributed under the GNU GPLv3 License found [here (file `/LICENSE`)](LICENSE)
