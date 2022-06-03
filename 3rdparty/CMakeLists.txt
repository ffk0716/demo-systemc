
include(ExternalProject)

ExternalProject_add(ep_systemc
    URL https://www.accellera.org/images/downloads/standards/systemc/systemc-2.3.3.tar.gz
    URL_HASH SHA256=5781b9a351e5afedabc37d145e5f7edec08f3fd5de00ffeb8fa1f3086b1f7b3f
    CMAKE_ARGS
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}
    -DDISABLE_COPYRIGHT_MESSAGE=TRUE
    -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>)

function(target_link_systemc target)
    ExternalProject_Get_Property(ep_systemc INSTALL_DIR)
    target_include_directories(${target} PRIVATE ${INSTALL_DIR}/include)
    target_link_directories(${target} PRIVATE ${INSTALL_DIR}/lib)
    target_link_libraries(${target} PRIVATE systemc)
    add_dependencies(${target} ep_systemc)
endfunction()

