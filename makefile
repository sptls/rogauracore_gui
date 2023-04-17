CXX=g++ -Wall -std=c++20
LIBS=`pkg-config --libs gtkmm-3.0`
CFLAGS=`pkg-config --cflags gtkmm-3.0`

all:
	@echo -n Creating resource file...
	@glib-compile-resources --target=resource.cpp --generate-source resources.gresource.xml
	@cp resource.cpp src/resource.cpp
	@rm resource.cpp
	@echo Done
	@echo -n Compiling...
	@${CXX} -p main.cpp src/*.cpp -o roggui ${CFLAGS} ${LIBS}
	@echo Done
install:
	cp roggui /usr/local/bin	
