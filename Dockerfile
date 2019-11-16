FROM alpine:latest

RUN apk add qt5-qtbase qt5-qtbase-dev qt5-qtdeclarative-dev qt5-qttools qt5-qttools-dev make g++

WORKDIR /qmlog
COPY qmlog .
WORKDIR /qmlog/build
RUN qmake-qt5 .. && make && make install
ENTRYPOINT ["/bin/bash"]
