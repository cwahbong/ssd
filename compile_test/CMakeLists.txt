AUX_SOURCE_DIRECTORY(. compile_test_SOURCES)
ADD_EXECUTABLE(compile_test ${compile_test_SOURCES})
TARGET_LINK_LIBRARIES(compile_test ssd)
