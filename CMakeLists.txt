cmake_minimum_required(VERSION 3.15)
project(DistributedBenchmark)

set(CMAKE_CXX_STANDARD 17)

# Find gRPC and Protobuf packages
find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

# Proto file
set(PROTO_FILE "calc.proto")

# Generated sources
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILE})
protobuf_generate_grpc_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_FILE})

# Monolithic application
add_executable(mono_app monolithic.cpp)

# Distributed server
add_executable(dist_server server.cpp ${PROTO_SRCS} ${GRPC_SRCS})
target_link_libraries(dist_server gRPC::grpc++ gRPC::grpc++_reflection)

# Distributed client
add_executable(dist_client client.cpp ${PROTO_SRCS} ${GRPC_SRCS})
target_link_libraries(dist_client gRPC::grpc++)

# Include directories
include_directories(${CMAKE_CURRENT_BINARY_DIR})