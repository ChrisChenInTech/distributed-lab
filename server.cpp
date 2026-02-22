#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "calc.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using calculator::Calculator;
using calculator::CalcRequest;
using calculator::CalcResponse;

class CalculatorServiceImpl final : public Calculator::Service {
    Status Square(ServerContext* context, const CalcRequest* request, CalcResponse* response) override {
        int number = request->number();
        response->set_result(number * number);
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    CalculatorServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}

int main() {
    RunServer();
    return 0;
}