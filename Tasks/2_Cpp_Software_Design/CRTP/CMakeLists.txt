#==================================================================================================
#
#  CMakeLists for subchapter "CRTP" of chapter "C++ Software Design"
#
#  Copyright (C) 2015-2026 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(CRTP
   CRTP.cpp
   )

add_executable(CRTP_Concept
   CRTP_Concept.cpp
   )

add_executable(DeducingThis
   DeducingThis.cpp
   )

add_executable(StaticInterfaces
   StaticInterfaces.cpp
   )

add_executable(Mixins
   Mixins.cpp
   )

add_executable(StrongType_CRTP
   StrongType_CRTP.cpp
   )

set_target_properties(
   CRTP
   CRTP_Concept
   DeducingThis
   Mixins
   StaticInterfaces
   StrongType_CRTP
   PROPERTIES
   FOLDER "2_Cpp_Software_Design/CRTP"
   )
