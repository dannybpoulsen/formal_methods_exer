FROM alpine:3.21
RUN apk update && apk add bison flex g++ cmake readline-dev git make flex-dev graphviz-dev fmt-dev 
