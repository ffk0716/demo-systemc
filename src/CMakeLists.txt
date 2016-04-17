
#find_package(SystemC REQUIRED)

include_directories($ENV{SYSTEMC_HOME}/include)
link_directories($ENV{SYSTEMC_HOME}/lib)
add_executable(sim main.cpp)
target_link_libraries(sim systemc)
	
	
#CXXFLAGS = -I$ -L${SYSTEMC_HOME}/lib -lsystemc
