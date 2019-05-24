PROJECT(cquic)

CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

INCLUDE_DIRECTORIES(src)

SET(SRC_LISTS
    src/invariants/packet.cpp
    src/invariants/longpkt.cpp
    src/invariants/shortpkt.cpp
    src/invariants/vernegopkt.cpp
)

ADD_LIBRARY(cquic STATIC ${SRC_LISTS})

ADD_EXECUTABLE(test_invariants test/test_invariants.cpp)
TARGET_LINK_LIBRARIES(test_invariants cquic)

