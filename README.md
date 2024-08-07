# Vulkan-Engine
## Project Description
This project is an implementation of a graphics engine using Vulkan.
It uses ___ for window and event handling.

This project is a way to learn Vulkan, I am following [the official Vulkan tutorial](https://docs.vulkan.org/tutorial/latest).

## Setup
### Dependencies
On a Debian system you can install the needed dependencies using:
```shell
sudo apt install g++ cmake make
```

### Clone Repository
```shell
git clone https://github.com/llikian/Vulkan-Engine.git
cd Vulkan-Engine
```

### Build
To build you can simply run the `release.sh` script at the root of the project using:
```shell
bash release.sh
```

You can also manually build it using:
```shell
cmake -B build && \
cmake --build build -j
```

Then you can run it using:
```shell
bin/Vulkan-Engine
```

## Credits
