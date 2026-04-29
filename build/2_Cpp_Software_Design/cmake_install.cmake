# Install script for directory: C:/Users/tobis/Documents/Software/Weiterbildung/CppTraining_2026_R-S/Tasks/2_Cpp_Software_Design

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/CppTraining")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/msys64/ucrt64/bin/objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/tobis/Documents/Software/Weiterbildung/CppTraining_2026_R-S/build/2_Cpp_Software_Design/Bridge/cmake_install.cmake")
  include("C:/Users/tobis/Documents/Software/Weiterbildung/CppTraining_2026_R-S/build/2_Cpp_Software_Design/CRTP/cmake_install.cmake")
  include("C:/Users/tobis/Documents/Software/Weiterbildung/CppTraining_2026_R-S/build/2_Cpp_Software_Design/Decorator/cmake_install.cmake")
  include("C:/Users/tobis/Documents/Software/Weiterbildung/CppTraining_2026_R-S/build/2_Cpp_Software_Design/Expression_Templates/cmake_install.cmake")
  include("C:/Users/tobis/Documents/Software/Weiterbildung/CppTraining_2026_R-S/build/2_Cpp_Software_Design/External_Polymorphism/cmake_install.cmake")
  include("C:/Users/tobis/Documents/Software/Weiterbildung/CppTraining_2026_R-S/build/2_Cpp_Software_Design/Motivation/cmake_install.cmake")
  include("C:/Users/tobis/Documents/Software/Weiterbildung/CppTraining_2026_R-S/build/2_Cpp_Software_Design/Prototype/cmake_install.cmake")
  include("C:/Users/tobis/Documents/Software/Weiterbildung/CppTraining_2026_R-S/build/2_Cpp_Software_Design/Strategy/cmake_install.cmake")
  include("C:/Users/tobis/Documents/Software/Weiterbildung/CppTraining_2026_R-S/build/2_Cpp_Software_Design/Type_Erasure/cmake_install.cmake")
  include("C:/Users/tobis/Documents/Software/Weiterbildung/CppTraining_2026_R-S/build/2_Cpp_Software_Design/Visitor/cmake_install.cmake")

endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/tobis/Documents/Software/Weiterbildung/CppTraining_2026_R-S/build/2_Cpp_Software_Design/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
