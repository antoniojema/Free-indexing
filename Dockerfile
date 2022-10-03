FROM debian:11

# Install packages
RUN apt-get update \
    && apt-get install -y cmake \
    && apt-get install -y g++ \
    && apt-get install -y clang \
    && apt-get install -y libgtest-dev

# Copy content
COPY ./src /project/src
COPY ./cmake_config /project/cmake_config
COPY ./build_scripts /project/build_scripts
COPY ./CMakeLists.txt /project/

WORKDIR /project

###########
#   RUN   #
###########
CMD \
    echo "--- BEGIN ---" \
    && cd /project/ \
    && ./build_scripts/make_deb_gcc_release.sh \
    && cmake --build ./build/deb_gcc_release \
    && cmake --build ./build/deb_gcc_release \
    && cd ./build && ctest && cd ../../ \
    && echo "--- DONE ---"
