#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <grpcpp/grpcpp.h>
#include "calc.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using calculator::Calculator;
using calculator::CalcRequest;
using calculator::CalcResponse;

class CalculatorClient {
public:
    CalculatorClient(std::shared_ptr<Channel> channel) : stub_(Calculator::NewStub(channel)) {}

    int Square(int number) {
        CalcRequest request;
        request.set_number(number);

        CalcResponse response;
        ClientContext context;

        Status status = stub_->Square(&context, request, &response);

        if (status.ok()) {
            return response.result();
        } else {
            std::cerr << "RPC failed: " << status.error_message() << std::endl;
            return -1;
        }
    }

private:
    std::unique_ptr<Calculator::Stub> stub_;
};

int main() {
    CalculatorClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    const int warmup_iterations = 10;
    const int benchmark_iterations = 10000;

    // Warm-up loop
    for (int i = 0; i < warmup_iterations; ++i) {
        client.Square(i);
    }

    // Benchmark loop
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < benchmark_iterations; ++i) {
        client.Square(i);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Total round-trip time: " << duration << " microseconds" << std::endl;

    return 0;
}