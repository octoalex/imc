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

### 0. Prerequisites

You will need:

- CMake
- Any C compiler
- Any C compatible build system
- Any command line

Additionally, you may find it useful to have:

- Git
- Python 3
  - You may need to install the `python3.13-venv` package on Debian/Ubuntu

### 1. Get the source

Download the source code from the `< > Code` button, and then download the code from
[libfyaml](https://github.com/pantoniou/libfyaml/tree/master) using the same method, then extract the contents

**OR**

Run the following command

```bash
git clone https://github.com/octoalex/imc.git --recurse-submodules
```

### 2. Configure CMake

Run the following command, and replace `<build_folder>` with your build folder of choice

```bash
cmake -B <build_folder>
```

### 3. Build!

Run the following command, and replace `<build_folder>` with the same folder you put in the last step

```bash
cmake --build <build_folder>
```

All done for now!

### E.1. Python developer scripts

If you're interested in using the analysis commands (to help analyze the version manifests), then you must make sure
python 3 is installed, and that virtual environments can be created (see [Prerequisites](#0-prerequisites))

Run

```bash
cmake -B <build_folder> -DENABLE_SCRIPTS=ON
```

## License

All software components are distributed under the GNU GPLv3 License found [here (file `/LICENSE`)](LICENSE)
