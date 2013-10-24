vpath src include database scanner sqlite3

CXX=g++
CXXFLAGS=
SRC=main.cpp controler.cpp opendevice.cpp database.cpp fsDatabase.cpp scanner.cpp timer.cpp 
OBJECTS=$(patsubst %.cpp,obj/%.o,%(SRC))
NAME=FSControl
LIBS=


default:$(NAME)

$(NAME): $(OBJECTS)
	
	
$(OBJECTS): | obj

obj:
	@mkdir -p $@
	
obj/%.o : %.cpp
	@echo $<
	@$(CXX) $(CXXFLAGS) -c $< -o $@
