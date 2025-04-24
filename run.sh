#!/bin/bash


set -e

ROOT_DIR=$(pwd)

echo "[Display server] Building display server..."
cd "$ROOT_DIR/display_server"
mkdir -p build && cd build
cmake .. && make

echo "[Processing server] Building processing server..."
cd "$ROOT_DIR/processing_server"
mkdir -p build && cd build
cmake .. && make

echo "[Client server] Building client server..."
cd "$ROOT_DIR/client"
mkdir -p build && cd build
cmake .. && make

cd "$ROOT_DIR"

echo "Starting servers..."

gnome-terminal -- bash -c "./display_server/build/display_server; exec bash"

sleep 1.5

gnome-terminal -- bash -c "./processing_server/build/processing_server; exec bash"

sleep 1.5

gnome-terminal -- bash -c "./client/build/client_app; exec bash"

# Опционально

#echo "[Run tests] Building tests..."
#cd "$ROOT_DIR/tests"
#mkdir -p build && cd build
#cmake .. && make
#
#cd "$ROOT_DIR"
#
#sleep 1.5
#
#gnome-terminal -- bash -c "./tests/build/run_tests; exec bash"