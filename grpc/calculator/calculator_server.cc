#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "calculator.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using calculator::TwoValueRequest;
using calculator::OneValueReply;
using calculator::Calculator;

class CalculatorServiceImpl final : public Calculator::Service{
    Status Add(ServerContext* context, const TwoValueRequest* request, OneValueReply* reply) override{
        reply->set_c(request->a() + request->b());
        return Status::OK;
    }

    Status Minus(ServerContext* context, const TwoValueRequest* request, OneValueReply* reply) override{
        reply->set_c(request->a() - request->b());
        return Status::OK;
    }

    Status Multiply(ServerContext* context, const TwoValueRequest* request, OneValueReply* reply) override{
        reply->set_c(request->a() * request->b());
        return Status::OK;
    }

    Status Divide(ServerContext * context, const TwoValueRequest* request, OneValueReply* reply) override{
        reply->set_c(request->a() / request->b());
        return Status::OK;
    }
};

void RunServer(){
    std::string server_address("0.0.0.0:50051");
    CalculatorServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}

int main(int args, char** argv){
    RunServer();
    return 0;
}