# start with ubuntu
FROM ubuntu

# it me!
LABEL maintainer="coditva@gmail.com"

# install deps
RUN apt-get update && \
    apt-get -y install gcc build-essential

# setup environment
ENV app /root/app/
ENV BUILD_TYPE release

# copy source to app dir
ADD . $app

# change to app dir
WORKDIR $app

# export the library path
RUN echo 'export LD_LIBRARY_PATH=./src/:$LD_LIBRARY_PATH' >> ~/.bashrc

# compile it
RUN make

# drop me in a shell
ENTRYPOINT ["/bin/bash"]
