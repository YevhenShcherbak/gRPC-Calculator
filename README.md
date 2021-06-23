# gRPC-Calculator
 Calculator realization with gRPC

## Build Docker Image
```bash
docker build -f docker/grpc.Dockerfile --build-arg GPRC_VERSION=1.38.0 --build-arg NUM_JOBS=8 --tag grpc-cmake:1.38.0 .
```
## Run Docker Container
```bash
docker run -it --rm --network host -v %cd%:/mnt grpc-cmake:1.38.0
```
Run two separate docker containers for server and client

## Build

```bash
cd mnt
cmake -B build
```
```bash
cmake --build build --config Release --parallel
```
If you have problem with building, use this command to copy abseil-cpp files in /include directory
```bash
cp -r /tmp/grpc/third_party/abseil-cpp/absl /include
```
## Run project
```bash
./build/grpc/calculator/calculator_server
```

```bash
./build/grpc/calculator/calculator_client
```

## Thank to Leo Mai (https://github.com/leimao/gRPC-Examples) for examples
