const { app, BrowserWindow } = require('electron')
const path = require('path')

function createWindow () {
    const win = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            preload: path.join(__dirname, 'preload.js')
        }
    })

    win.loadFile(path.join(__dirname, 'index.html'));
}

app.whenReady().then(() => {
    createWindow()

    app.on('activate', () => {
        if (BrowserWindow.getAllWindows().length === 0) {
            createWindow();
        }
    });
});

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit();
    }

    process.exit(0);
});


// sockets:
// https://stackoverflow.com/questions/7045614/can-node-js-listen-on-unix-socket

// better: use callback function to call node whenever new image has been saved

const fs = require ('fs');
const core = require('../engine/build/Release/core');

const frameImagePath = './frame.png';

try {
    console.log(core.checkEngineStatus(3));
}
catch (e) {
    console.error('error connecting to engine: ', e);
    process.exit(1);
}

// update OpenGL Window
const update = (delta) => {
    if(!core.rendererShuttingDown()) {
        core.updateRenderer();
    }
    else {
        core.shutDownRenderer();
    }
}

// length of a tick in milliseconds
const fps = 30;
let tickLengthMs = 1000 / fps;

/* renderLoop related variables */
// timestamp of each loop
let previousTick = Date.now();

// number of times gameLoop gets called
let actualTicks = 0

const renderLoop = function () {
    // get the time now and number of ticks
    const now = Date.now();
    actualTicks++;

    // update when allowed to
    if (previousTick + tickLengthMs <= now) {
        const delta = (now - previousTick) / 1000;
        previousTick = now;

        update(delta);

        if(core.rendererShuttingDown()) {
            return;
        }

        // console.log('delta', delta, '(target: ' + tickLengthMs +' ms)', 'node ticks', actualTicks);
        actualTicks = 0;
    }

    // blend setImmediate (which is accurate) and setTimeout (which uses less CPU) to have accurate update loop
    if (Date.now() - previousTick < tickLengthMs - 16) {
        setTimeout(renderLoop);
    } else {
        setImmediate(renderLoop);
    }
}

// method to create render loop
const startRenderLoop = () => {
    // init OpenGL
    core.createRenderer();

    // begin the game loop!
    renderLoop();
}

startRenderLoop();
