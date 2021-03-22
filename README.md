
## soci-test
- SOCI : The C++ Database Access Library 
    - https://github.com/SOCI/soci


### Package install & Build
```sh
$ vcpkg.exe install soci[odbc]:x64-windows-static
```

- Build
```sh
$ mkdir build && cd build
$ cmake .. 
$ cmake --build . --config Release
```

## soci oracle install 
- vcpkg 내에서 제공되지 않아 별도 빌드 필요 

### oracle client & devel 설치 
https://www.oracle.com/kr/database/technologies/instant-client/linux-x86-64-downloads.html

```
$ curl -OL https://download.oracle.com/otn_software/linux/instantclient/211000/oracle-instantclient-basic-21.1.0.0.0-1.x86_64.rpm
$ curl -OL https://download.oracle.com/otn_software/linux/instantclient/211000/oracle-instantclient-devel-21.1.0.0.0-1.x86_64.rpm

$ yum install oracle-instantclient-basic-21.1.0.0.0-1.x86_64.rpm
$ yum install oracle-instantclient-devel-21.1.0.0.0-1.x86_64.rpm
```

### soci oracle build 
위의 설치만으로 oracle library를 cmake가 찾지 못함, 수동 설정 

```
$ cmake .. -DCMAKE_BUILD_TYPE=Release -DWITH_ORACLE=ON -DOracle_FOUND=ON \
	-DOracle_INCLUDE_DIR=/usr/include/oracle/21/client64 \
	-DOracle_LIBRARIES=/usr/lib/oracle/21/client64/lib \
	-DORACLE_NNZ_LIBRARY=/usr/lib/oracle/21/client64/lib/libnnz21.so
  
$ make -j4
$ sudo make install
```

```
$ tree lib
lib
├── libsoci_core.a
├── libsoci_core.so -> libsoci_core.so.4.0
├── libsoci_core.so.4.0 -> libsoci_core.so.4.0.1
├── libsoci_core.so.4.0.1
├── libsoci_empty.a
├── libsoci_empty.so -> libsoci_empty.so.4.0
├── libsoci_empty.so.4.0 -> libsoci_empty.so.4.0.1
├── libsoci_empty.so.4.0.1
├── libsoci_oracle.a
├── libsoci_oracle.so -> libsoci_oracle.so.4.0
├── libsoci_oracle.so.4.0 -> libsoci_oracle.so.4.0.1
└── libsoci_oracle.so.4.0.1
```

### application build 

- CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.11)

project(main)

set(CMAKE_CXX_STANDARD 17)
add_executable(main main.cpp)

target_compile_options(main PRIVATE -DSOCI_HAVE_CXX11)
target_include_directories(main PRIVATE /usr/include/oracle/21/client64)
target_link_directories(main PRIVATE /usr/lib/oracle/21/client64/lib)
target_link_libraries(main PRIVATE soci_core soci_oracle clntsh)
```
