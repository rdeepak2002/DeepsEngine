// sockets:
// https://stackoverflow.com/questions/7045614/can-node-js-listen-on-unix-socket

// better: use callback function to call node whenever new image has been saved

const fs = require ('fs');
const testAddon = require('../engine/build/Release/addon.node');

const frameImagePath = './frame.png';

console.log('calling napi');

// console.log(testAddon.hello(2));
testAddon.createRenderer();

const render = () => {
    if(!testAddon.rendererShuttingDown()) {
        testAddon.updateRenderer();
    }
}

const hrtimeMs = function() {
    let time = process.hrtime()
    return time[0] * 1000 + time[1] / 1000000
}

const TICK_RATE = 20
let tick = 0
let previous = hrtimeMs()
let tickLengthMs = 1000 / TICK_RATE

const loop = () => {
    setTimeout(loop, tickLengthMs)
    let now = hrtimeMs()
    let delta = (now - previous) / 1000
    console.log('delta', delta)
    render();
    // game.update(delta, tick) // game logic would go here
    previous = now
    tick++
}

loop() // starts the loop

// try {
//   const bitmap = fs.readFileSync(frameImagePath);
//   const buffer = new Buffer(bitmap).toString('base64');
//   // console.log('frame buffer', buffer);
//   console.log('got frame buffer');
// } catch (err) {
//   console.error('error getting frame', err);
// }

// keep process running
// setInterval(() => {}, 1 << 30);

console.log('program ended');
