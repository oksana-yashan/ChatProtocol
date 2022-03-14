
In file CommonGraph.cmake change 21 line:

include(CommonTarget) 
=>
include(${CMAKE_CURRENT_LIST_DIR}/CommonTarget.cmake)
