// const express = require('express')
// const app = express()
// var http = require('http').createServer(app);
// var robot = require('robotjs');
// var io = require('socket.io')(http);
// const port = 3000

// // var io = require('socket.io')(http);
// // io.on('connection', (socket)=>{
// //     console.log('User connected');
// // })
// app.get('/', (req, res) => {
//     res.sendFile(__dirname + '/index.html');
//   });
// io.on('connection', (socket) => {
//   console.log('a user connected');
//   socket.on('disconnect', () => {
//     console.log('user disconnected');
//   });
// });
// http.listen(port, () => {
//   console.log(`Example app listening at http://localhost:${port}`)
// })

var net = require('net')
const port = 8080;
const host = '127.0.0.1';

const server = net.createServer(onClientConnection);

server.listen(port, ()=>{
    console.log(`listening on port ${port} at ${host}`)
})

function onClientConnection(socket){
    console.log(`${socket.remoteAddress}:${socket.remotePort} Conncted`);
    socket.on('data', (data)=>{
        console.log(`Received: ${data}`)
        socket.write(`true`);
    })
    socket.on('close', ()=>{
        console.log("Connection Terminated")
    })
    socket.on('error', (error)=>{
        console.error(`Error occur: ${error}`);
    })
}