
# Find the dependencies

find_package(GTest REQUIRED)

# Configure test target

add_executable (serializer_test main.cc serializer_test.cc)

target_link_libraries (serializer_test Wormhole::utils GTest::GTest GTest::Main)

add_test (
    NAME serializer_test
    COMMAND $<TARGET_FILE:serializer_test>
)

if(MSVC)
    set_target_properties(serializer_test PROPERTIES
        FOLDER Tests
    ) 
endif()