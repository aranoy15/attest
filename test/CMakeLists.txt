add_executable(
    unit_tests
    atcommandtest.cpp
    timeouttest.cpp
    gsmmodetest.cpp
    splittest.cpp
    sgpiotest.cpp
    )

target_link_libraries(
    unit_tests
    gtest_main
    attestsource
    )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )