FROM alpine:latest

RUN apk update && \
    apk add --no-cache \
    build-base \
    gcc \
    g++ \
    make \
    libc-dev

COPY ./hello.c .
