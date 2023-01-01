const http = require('http');

const hostname = '0.0.0.0'; // this machine, in docker 127.0.0.1 means this container
const port = 9500;

const server = http.createServer((req, res) => {
    console.log(process)
    res.statusCode = 200
    res.setHeader('Content-Type', 'text/html')
    res.end("<h1>Hello World<h1>")
})

server.listen(port, hostname, () => {
    console.log('server listening on p. 9500')
})

