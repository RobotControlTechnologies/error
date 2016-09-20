cmake -E make_directory build
cmake -E chdir build cmake .. -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=..
cmake --build build --target install --clean-first