
# Find the dependencies

find_package(GTest REQUIRED)

# Configure test target

add_executable (deserializer_test main.cc deserializer_test.cc)

target_link_libraries (deserializer_test wh::utils GTest::GTest GTest::Main)

add_test (
    NAME deserializer_test
    COMMAND $<TARGET_FILE:deserializer_test>
)

if(MSVC)
    set_target_properties(deserializer_test PROPERTIES
        FOLDER Tests
    ) 
endif()