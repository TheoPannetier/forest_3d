# CMakeList.txt : CMake project for forest_3d, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("forest_3d")

# Add source to this project's executable.
add_executable (forest_3d "src/main.cpp"  "src/Vox.h" "src/Branch.h" "src/VoxArray.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET forest_3d PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
