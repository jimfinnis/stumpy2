cmake_minimum_required(VERSION 2.6)
project(SERVERBASE)

set(SERVERSOURCES 
    ../serverbase/controller.cpp 
    ../serverbase/errors.cpp 
    ../serverbase/model.cpp 
    ../serverbase/server.cpp 
    ../serverbase/util/time.cpp
    ../serverbase/stdConns.cpp)


add_executable(music 
    main.cpp midi.cpp globals.cpp
    components/time.cpp components/state.cpp
    components/math.cpp components/output.cpp
    components/chord.cpp components/players.cpp
    components/sequencers.cpp components/env.cpp
    ${SERVERSOURCES})
    
target_include_directories(music PUBLIC ../serverbase)    
target_link_libraries(music -ljack)

