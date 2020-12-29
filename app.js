var robot = require("robotjs"); //simulate keyboard action from http://robotjs.io/
var net = require('net');
var volume = 0;
const port = 8080;

const server = net.createServer(onClientConnection);

server.listen(port, ()=>{
    console.log(`listening on port ${port} ...`)
})

function onClientConnection(socket){
    console.log(`${socket.remoteAddress}:${socket.remotePort} Conncted`);
    socket.on('data', (data)=>{
        socket.write('true');
        keyboard((data).toString());
    })
    socket.on('close', ()=>{
        console.log("Connection Terminated")
    })
    socket.on('error', (error)=>{
        console.error(`Error occur: ${error}`);
    })
}

function keyboard(cmd){
    switch (cmd) {
        case "space":
            robot.keyTap("space");
            break;
        case "f":
            robot.keyTap("f");
            break;
        default:
            volume_now = parseInt(cmd);
            while(volume_now > volume){
                volume++;
                robot.keyTap("audio_vol_up");
            }
            while(volume_now < volume){
                volume--;
                robot.keyTap("audio_vol_down");
            }
            break;
    }
}