clang++ -g llvmgenerator.h llvmgenerator.cpp func.cpp -std=c++11 -ldl -lncurses `llvm-config --cxxflags --libs core support jit native` `llvm-config --ldflags --system-libs` -O0
# clang++ -g *.h *.cpp -std=c++11 -lncurses `llvm-config --cxxflags --ldflags --libs` -O0