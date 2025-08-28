
# Prerequisites

Before building or running the C++ project, ensure you have the following software installed:

- **CMake** (version 3.10 or newer)
- **C++ Compiler** with C++17 support (e.g., `g++`, `clang++`)

## Installation on macOS

- Install Homebrew if you don't have it: https://brew.sh/
- Install CMake and a compiler:
	```sh
	brew install cmake gcc
	```
	(You can use `clang++` which comes with Xcode Command Line Tools, or `g++` from Homebrew)

## Installation on Ubuntu/Debian

```sh
sudo apt update
sudo apt install cmake g++
```

## Installation on Windows

- Download and install CMake: https://cmake.org/download/
- Install a compiler (e.g., Visual Studio or MinGW)


# cpp_engine: Build & Run Instructions (CMake)

## Building the C++ Project with CMake

1. Open a terminal and navigate to the `cpp_engine` directory:
	```sh
	cd cpp_engine
	```
2. Create a build directory and navigate into it:
	```sh
	mkdir -p build
	cd build
	```
3. Run CMake to configure the project:
	```sh
	cmake ..
	```
4. Build the project:
	```sh
	cmake --build .
	```
	This will compile the sources and produce an executable named `main` in the `build` directory.

## Running the Program

After building, run the executable from the `build` directory:
```sh
./main
```

## Cleaning Build Files

To remove all build artifacts, simply delete the `build` directory:
```sh
rm -rf build
```

---
For any issues, ensure you have CMake (version 3.10+) and a C++17 compatible compiler (e.g., `g++`).


# Python Lab Usage Guide

## 1. Environment Setup

This project uses a Python virtual environment. To set it up and install dependencies:

1. Open a terminal and navigate to the `python_lab` directory:
   ```sh
   cd python_lab
   ```
2. (Recommended) Create a virtual environment (if not already created):
   ```sh
   python3 -m venv .venv
   source .venv/bin/activate
   ```
3. Install required packages:
   ```sh
   pip install -r requirements.txt
   ```

## 2. Running the Code

- To run the data analysis script:
  ```sh
  python data_analyze.py
  ```
- To plot distributions:
  ```sh
  python plot_distribution.py
  ```
- To open and run the Jupyter notebook:
  ```sh
  jupyter notebook notebooks/analysis.ipynb
  ```

## 3. Notes
- All output plots and data will be saved in the `plots/` and `data/` folders respectively.
- Make sure your virtual environment is activated before running any scripts.

