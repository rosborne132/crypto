FROM alpine:latest

RUN apk update && \
    apk add --no-cache \
    git \
    nodejs \
    neovim \
    ripgrep \
    build-base \
    gcc \
    g++ \
    make \
    libc-dev \
    wget --update

RUN git clone https://github.com/NvChad/starter ~/.config/nvim

COPY ./hello.c .
COPY ./Makefile .
