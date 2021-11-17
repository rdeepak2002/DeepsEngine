// sockets:
// https://stackoverflow.com/questions/7045614/can-node-js-listen-on-unix-socket

// better: use callback function to call node whenever new image has been saved

const fs = require ('fs');
const testAddon = require('../engine/build/Release/addon.node');

const frameImagePath = './frame.png';

console.log('calling napi');

// console.log(testAddon.hello(2));
testAddon.createRenderer();

while(!testAddon.rendererShuttingDown()) {
    testAddon.updateRenderer();
}

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
