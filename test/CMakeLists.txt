add_executable(test test.cpp)
target_link_libraries(test mpnn)

add_executable(test_cloud_cover test_cloud_cover.cpp)
target_link_libraries(test_cloud_cover mpnn)

