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

find_package(Boost REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Add source to this project's executable.
add_executable (forest_3d main.cpp ${SOURCES} "src/Utils.h" "src/Utils.cpp" "src/Simulation.h" "src/Simulation.cpp" "src/Parameters.h" "src/Parameters.cpp")

#if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET forest_3d PROPERTY CXX_STANDARD 20)
#endif()

# TODO: Add tests and install targets if needed.
enable_testing()

add_executable (test_forest_3d tests/test_main.cpp ${SOURCES} "src/Utils.h" "src/Utils.cpp" "src/Simulation.h" "src/Simulation.cpp" "src/Parameters.h" "src/Parameters.cpp")

target_link_libraries(test_forest_3d PRIVATE Boost::headers)

add_test(NAME forest_test COMMAND test_forest_3d)
