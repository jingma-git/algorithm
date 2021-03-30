cmake_minimum_required(VERSION 3.1)
project(algorithm)

set(CMAKE_CXX_STANDARD 11)
# find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Boost)
if(Boost_FOUND)
message("-- Boost_LIB ${Boost_LIBRARIES}")
endif()

# add_executable(main sort.cpp)

# add_executable(main graph.cpp)
# target_link_libraries(main ${Boost_LIBRARIES})

# add_executable(main dfs_con_comp.cpp)
# add_executable(main bfs_con_comp.cpp)
# add_executable(main bfs_shortest_path.cpp)
# add_executable(main skel.cpp)

# add_executable(main in_triag.cpp)

# add_executable(main mst_kruskal.cpp)
# add_executable(main dp_longest_path.cpp)
add_executable(main gauss_eliminate.cpp)



