'use strict';

import {app, BrowserWindow, ipcMain} from 'electron';
import * as path from 'path';
import { format as formatUrl } from 'url';
const core = require('../../../engine/build/Release/core.node');

console.log(core);

const isDevelopment = process.env.NODE_ENV !== 'production';

// global reference to mainWindow (necessary to prevent window from being garbage collected)
let mainWindow;

function createMainWindow() {
  const browserWindow = new BrowserWindow({
    minWidth: 620,
    minHeight: 400,
    width: 1240,
    height: 800,
    webPreferences: { nodeIntegration: true } },
  );

  // TODO: make panes responsive
  // TODO: make panes responsive
  // TODO: make panes responsive
  // TODO: make panes responsive
  browserWindow.setResizable(false);

  // set title of window
  browserWindow.setTitle('Deeps Engine');

  browserWindow.on('page-title-updated', (evt) => {
    evt.preventDefault();
  });

  if (isDevelopment) {
    browserWindow.webContents.openDevTools();
  }

  if (isDevelopment) {
    browserWindow.loadURL(`http://localhost:${process.env.ELECTRON_WEBPACK_WDS_PORT}`);
  } else {
    browserWindow.loadURL(
      formatUrl({
        pathname: path.join(__dirname, 'index.html'),
        protocol: 'file',
        slashes: true,
      })
    );
  }

  browserWindow.on('closed', () => {
    mainWindow = null;
  });

  browserWindow.webContents.on('devtools-opened', () => {
    browserWindow.focus();
    setImmediate(() => {
      browserWindow.focus();
    });
  });

  return browserWindow;
}

// quit application when all windows are closed
app.on('window-all-closed', () => {
  // on macOS it is common for applications to stay open until the user explicitly quits
  // if (process.platform !== 'darwin') {
  //   app.quit();
  // }
  app.quit();
  process.exit(0);
});

app.on('activate', () => {
  // on macOS it is common to re-create a window even after all windows have been closed
  if (mainWindow === null) {
    mainWindow = createMainWindow();
  }
});

// create main BrowserWindow when electron is ready
app.on('ready', () => {
  mainWindow = createMainWindow();
});

/**
 * Handle async message received from client
 */
ipcMain.on('asynchronous-message', (event, arg) => {
  // console.log('got message', arg);

  // handle invalid message
  if (!arg || !arg.name) {
    console.error('invalid message format: ', arg);
    return;
  }

  // TODO: implement stopping of renderer (when application closes or other things)

  // respond to valid messages
  switch (arg.name) {
      // when client asks for ping
    case 'ping':
      const reply = {
        name: 'pong',
        data: {
          "pingTime": Date.now() - arg.data.createdAt,
          "createdAt": Date.now(),
          "status": "success"
        },
        status: 'success'
      };

      event.reply('asynchronous-reply', reply);

      break;
    case 'play-mode':
      let showWindow = true;
      let saveOutputRender = true;

      console.log('play mode on')

      core.createRenderer(showWindow, saveOutputRender, blankProjectPath);
      core.startPlayMode();

      console.log('play mode off')

      showWindow = false;
      saveOutputRender = true;

      core.createRenderer(showWindow, saveOutputRender, blankProjectPath);
      core.updateRenderer();

      const playModeReply = {
        name: 'update-play-state',
        status: 'success',
        data: {
          playMode: false
        }
      };

      event.reply('asynchronous-reply', playModeReply);

      break;
    case 'shutdown-renderer':
      core.shutDownRenderer();
      break;
    case 'get-frame':
      // get image frame
      const imageData = core.getCachedFrame();

      if (imageData === 'no frame') {
        const reply = {
          name: 'image-data',
          status: 'failure',
          data: {}
        };

        event.reply('asynchronous-reply', reply);
      }

      const imageReply = {
        name: 'image-data',
        status: 'success',
        data: {
          imageType: 'png',
          imageEncoding: 'base64',
          imageData: imageData
        }
      };

      event.reply('asynchronous-reply', imageReply);
      break;
    case 'start-renderer':
      startRenderLoop();
      break;
    case 'handle-editor-resize':
      const width = arg.data.width;
      const height = arg.data.height;
      core.handleEditorResize(width, height);
      break;
    default:
      console.warn('unknown message: ', arg);
      break;
  }
});

try {
  console.log(core.checkEngineStatus(3));
} catch (e) {
  console.error('error connecting to engine: ', e);
  process.exit(1);
}

// update OpenGL Window
// const update = (delta) => {
//   if (!core.rendererShuttingDown()) {
//     core.updateRenderer();
//     if (mainWindow) {
//       try {
//         mainWindow.webContents.send('asynchronous-message', {
//           name: 'new-frame-available',
//           data: {},
//           status: 'success'
//         });
//       } catch (e) {
//         console.error('error sending async message to window', e);
//       }
//     }
//   } else {
//     core.shutDownRenderer();
//   }
// }

// length of a tick in milliseconds
// const fps = 30;
// let tickLengthMs = 1000 / fps;

/* renderLoop related variables */
// timestamp of each loop
// let previousTick = Date.now();

// number of times gameLoop gets called
// let actualTicks = 0

// const renderLoop = function () {
//   // get the time now and number of ticks
//   const now = Date.now();
//   actualTicks++;
//
//   // update when allowed to
//   if (previousTick + tickLengthMs <= now) {
//     const delta = (now - previousTick) / 1000;
//     previousTick = now;
//
//     update(delta);
//
//     if (core.rendererShuttingDown()) {
//       return;
//     }
//
//     // console.log('delta', delta, '(target: ' + tickLengthMs +' ms)', 'node ticks', actualTicks);
//     actualTicks = 0;
//   }
//
//   // blend setImmediate (which is accurate) and setTimeout (which uses less CPU) to have accurate update loop
//   if (Date.now() - previousTick < tickLengthMs - 16) {
//     setTimeout(renderLoop);
//   } else {
//     setImmediate(renderLoop);
//   }
// }

// method to create render loop
// get the path of the engine
const blankProjectPath = path.resolve(path.join("example_projects", "blank_project"));

const startRenderLoop = () => {
  // init OpenGL
  const showWindow = false;
  const saveOutputRender = true;

  core.createRenderer(showWindow, saveOutputRender, blankProjectPath);
  core.updateRenderer();

  if (mainWindow) {
    try {
      mainWindow.webContents.send('asynchronous-message', {
        name: 'new-frame-available',
        data: {},
        status: 'success'
      });
    } catch (e) {
      console.error('error sending async message to window', e);
    }
  }

  // begin the game loop!
  // renderLoop();
}
