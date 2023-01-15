FROM gcc:12.2
WORKDIR /app
COPY . .
RUN g++ -o gppapp socket_1.cc
CMD ["./gppapp"]
EXPOSE 9504