FROM ubuntu
RUN apt-get update && apt-get install -y g++ cmake graphviz-dev make libfmt-dev  bison flex  libreadline-dev
