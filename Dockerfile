FROM centos:8

RUN dnf -y update && \
    dnf -y install make sudo trace-cmd

RUN curl http://ftp.tu-chemnitz.de/pub/linux/dag/redhat/el6/en/x86_64/rpmforge/RPMS/ncc-2.7-1.el6.rf.x86_64.rpm -o ncc.rpm
RUN dnf -y install ncc.rpm

RUN curl https://sx-aurora.com/repos/llvm/x86_64/llvm-ve-rv-1.8.0-1.8.0-1.x86_64.rpm -o llvm-ve-re-1.8.0.rpm
RUN rpm -i llvm-ve-re-1.8.0.rpm --nodeps # TODO fix dependencies

RUN dnf clean all

COPY llvmvervvars.sh .

ENTRYPOINT . /llvmvervvars.sh && /bin/bash -i # TODO this executes bash in sh
