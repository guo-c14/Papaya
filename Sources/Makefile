cxx = g++
cxxflags = -Wall -std=c++11 -O3
linkflags = -pthread
prom = Papaya
deps = $(shell find ./ -name "*.hpp")
src = $(shell find ./ -name "*.cpp")
obj = $(src:%.cpp=%.o)

$(prom): $(obj)
	$(cxx) $(linkflags) $(cxxflags) -o $(prom) $(obj)

%.o: %.cpp $(deps)
	$(cxx) $(cxxflags) -c  $< -o $@

clean:
	rm -rf $(obj) $(prom)
