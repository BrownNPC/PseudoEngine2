# mingw-w64-toolchain.cmake

# Specify the target system name
set(CMAKE_SYSTEM_NAME Windows)

# Set the compiler paths for MinGW-w64
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

# Set the archiver for static libraries
set(CMAKE_AR x86_64-w64-mingw32-ar)

# Set the path for the Windows resource compiler
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

# Set the system root if needed (optional)
#set(CMAKE_SYSROOT /usr/x86_64-w64-mingw32)

# Specify the linker settings
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

# Search for libraries and includes in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

