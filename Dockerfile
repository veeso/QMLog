FROM ubuntu:18.04

RUN apt-get update \
  && apt-get install -y -qq --no-install-recommends \
  cmake \
  dpkg-dev \
  file \
  g++ \
  make \
  qt5-default \
  qtbase5-dev \
  qttools5-dev

WORKDIR /qmlog
COPY qmlog .
WORKDIR /qmlog/build
RUN qmake .. && make && make install
ENTRYPOINT ["/bin/bash"]
