#include <iostream>
#include <memory>
#include <string>

#include <cstdio>
#include <vector>

#include <grpc++/grpc++.h>

#include "calculator.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using calculator::TwoValueRequest;
using calculator::OneValueReply;
using calculator::Calculator;

class CalculatorClient {
    public:
    CalculatorClient(std::shared_ptr<Channel> channel) : stub_(Calculator::NewStub(channel)) {}

    std::string Compute(double a, double b, char sign) {
        TwoValueRequest request;
        request.set_a(a);
        request.set_b(b);

        OneValueReply reply;
        ClientContext context;

        Status status;
        if (sign == '+'){
            status = stub_->Add(&context, request, &reply);
        }
        else if (sign == '-'){
            status = stub_->Minus(&context, request, &reply);
        }
        else if (sign == '*'){
            status = stub_->Multiply(&context, request, &reply);
        }
        else if (sign == '/'){
            status = stub_->Divide(&context, request, &reply);
        }
        else{
            std::cout << "Wrong operation!" << std::endl;
        }
        
        if (status.ok()){
            return std::to_string(reply.c());
        }
        else{
            std::cout << status.error_code() << "; " << status.error_message() << std::endl;
            return "RPC failed";
        }
    }

    private:
    std::unique_ptr<Calculator::Stub> stub_;
};

void InterativeGRPC(){
    CalculatorClient calculator(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    while (true)
    {
        std::string expression;
        std::cout << "Enter binary arithmetic expression: " << std::endl;
        std::getline(std::cin, expression);
        std::vector<std::string> tokens;

        std::size_t prev = 0, pos;
        char sign;
        while ((pos = expression.find_first_of("+-*/", prev)) != std::string::npos)
        {
            sign = expression[pos];
            if (pos > prev)
            {
                tokens.push_back(expression.substr(prev, pos - prev));
            }
            prev = pos + 1;
        }
        if (prev < expression.length())
        {
            tokens.push_back(expression.substr(prev, std::string::npos));
        }
        if (tokens.size() > 2)
        {
            std::cout << "Your expression has more than 2 tokens!" << std::endl;
            continue;
        }
		else if (tokens.size() < 2)
		{
			std::cout << "Your expression has less than 2 tokens!" << std::endl;
            continue;
		}

        double a = std::stof(tokens[0]);
        double b = std::stof(tokens[1]);
        
        std::string reply = calculator.Compute(a, b, sign);
        if (reply == "gRPC failed")
        {
            std::cout << "gRPC failed" << std::endl;
        }
        std::cout << "gRPC returned: " << std::endl;
        std::cout << reply << std::endl;
        
    }
    
}

int main() {
    InterativeGRPC();
    return 0;
}