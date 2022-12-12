
# Find the dependencies

find_package(GTest REQUIRED)

# Configure test target

add_executable (defer_call_test main.cc defer_call_test.cc)

target_link_libraries (defer_call_test Wormhole::utils GTest::GTest GTest::Main)

add_test (
    NAME defer_call_test
    COMMAND $<TARGET_FILE:defer_call_test>
)

if(MSVC)
    set_target_properties(defer_call_test PROPERTIES
        FOLDER Tests
    ) 
endif()