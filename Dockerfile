FROM centos:8

RUN dnf -y update && \
    dnf -y install make && \
    dnf clean all

RUN curl https://sx-aurora.com/repos/llvm/x86_64/llvm-ve-rv-1.8.0-1.8.0-1.x86_64.rpm -o llvm-ve-re-1.8.0.rpm
RUN rpm -i llvm-ve-re-1.8.0.rpm --nodeps # TODO fix dependencies

COPY llvmvervvars.sh .

ENTRYPOINT . /llvmvervvars.sh && /bin/bash -i # TODO this executes bash in sh
