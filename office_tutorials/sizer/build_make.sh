#! /bin/bash 

if [ $# -eq 0 ]; then
    cmake -S . -B ./build/ -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ 
    make -C ./build/
elif [ $# -eq 1 ]; then 
    if [ "$1" == "-c" ]; then 
        cmake -S . -B ./build/ -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ 
    fi

    if [ "$1" == "-b" ]; then
        make -C ./build/
    fi
else
    echo "paramters error"
fi