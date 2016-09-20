cmake -E make_directory build
cmake -E chdir build cmake .. -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_INSTALL_PREFIX=..
cmake --build build --target install --clean-first