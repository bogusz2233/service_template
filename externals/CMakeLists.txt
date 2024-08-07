set(CLI11_PRECOMPILED ON)
add_subdirectory(CLI11)
add_subdirectory(fmt)

set(SPDLOG_FMT_EXTERNAL ON)
add_subdirectory(spdlog)

if(BUILD_UNIT_TESTS)
    add_subdirectory(googletest)
endif()

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    spdlog::spdlog
    CLI11::CLI11
    $<$<BOOL:${BUILD_UNIT_TESTS}>:GTest::gtest>
    $<$<BOOL:${BUILD_UNIT_TESTS}>:GTest::gtest_main>
)
