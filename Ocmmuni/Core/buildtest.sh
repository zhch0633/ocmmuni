rm -rf build
mkdir build
cd build

mkdir math
cd math

# build for dev environment os debug
mkdir dev
cd dev
cmake ../../../math/
make
make install
cd ..
cd ..


mkdir ocmtcp
cd ocmtcp

# build for dev environment os debug
mkdir dev
cd dev
cmake ../../../ocmtcp/
make
make install
cd ..
cd ..


mkdir portal
cd portal

# build for dev environment os debug
mkdir dev
cd dev
cmake ../../../
make
make install
cd ..
cd ..
