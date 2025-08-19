FROM python:3.9-slim

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \ 
    pkg-config \
    libopenbabel-dev \
    openbabel \
    && rm -rf /var/lib/apt/lists/*

# Install pybind11
RUN pip3 install pybind11 numpy==1.26.4 cython

# Create a working directory
WORKDIR /repo

# Set the entrypoint to the bash shell
ENTRYPOINT ["/bin/bash"]