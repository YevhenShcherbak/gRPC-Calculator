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
Run two separate terminal (one from Docker CLI) for server and client

## Run project
```bash
./build/grpc/calculator/calculator_server
```

```bash
./build/grpc/calculator/calculator_client
```

