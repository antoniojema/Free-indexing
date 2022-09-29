FROM debian:11
RUN apt-get update && \
    apt-get install -y cmake
RUN cmake --version

# Copy content
COPY ./src /project/src
COPY ./cmake_config /project/cmake_config
COPY ./CMakeLists.txt /project/
COPY ./CMakeLists /project/

# WORKDIR /app

###########
#   RUN   #
###########
# CMD python3 app.py
