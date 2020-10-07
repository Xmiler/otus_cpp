FROM ubuntu:18.04
RUN apt-get update
RUN apt-get install wget gnupg -y
RUN wget --no-check-certificate -O - https://bintray.com/user/downloadSubjectPublicKey?username=bintray | apt-key add -
RUN echo "deb http://dl.bintray.com/xmiler/otus_cpp trusty main" | tee -a /etc/apt/sources.list
RUN apt-get update
RUN apt-get install helloworld -y
