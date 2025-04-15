## Build Instructions

To build the `arcade` project, you need to have CMake and a C++ compiler installed. Follow the instructions below:

1. **Clone the Repository**: 
   ```bash
   git clone <repository_url>
   cd <repository_directory>
   ```

2. **Install Dependencies**: 
   The project requires `ncurses` to be built and installed. The CMake configuration will take care of this using the `ExternalProject_Add` command.

3. **Create a Build Directory**: 
   ```bash
   mkdir build
   cd build
   ```

4. **Run CMake**:
   ```bash
   cmake ..
   ```

5. **Build the Project**:
   ```bash
   cmake --build .
   ```

6. **Run the Executable**:
   After building, the executable `arcade` will be available in the build directory. Run it using:
   ```bash
   ./arcade
   ```

Note: Make sure you have the necessary permissions to install dependencies and write to the directories used during the build process.
