import * as React from 'react';
import * as ReactDOM from 'react-dom';
import {useEffect, useState} from "react";
const electron = require('electron');
const { ipcRenderer, remote } = electron;

const Index = () => {
    // message hook
    const [message, setMessage] = useState('no message');
    const [frameData, setFrameData] = useState(undefined);

    const renderLoop = () => {
        console.log("TODO: HAVE CALLBACK FUNCTION INSTEAD OF POLLING LIKE THIS");
        window.requestAnimationFrame(renderLoop);

        const messageObj = {
            name: 'get-frame',
            data: {
                "createdAt": Date.now()
            }
        };

        ipcRenderer.send('asynchronous-message', messageObj);
    }

    useEffect(() => {
        // TODO: use callback function for this / call every time render is called in electron
        renderLoop();

        // send ping message to server
        const messageObj = {
          name: 'ping',
          data: {
              "createdAt": Date.now()
          }
        };

        ipcRenderer.send('asynchronous-message', messageObj);

        // get message from server
        ipcRenderer.on('asynchronous-reply', (event, arg) => {
            console.log('got reply', arg);

            // handle invalid reply
            if(!arg || !arg.name) {
                console.error('invalid reply format: ', arg);
                return;
            }

            // handle valid reply
            switch (arg.name) {
                case 'pong':
                    setMessage(`gotPong: ${JSON.stringify(arg)}`);
                    break;
                case 'image-data':
                    const status = arg.status;
                    const data = arg.data;

                    if(status === 'success') {
                        const imageType: string = data.imageType;
                        const imageEncoding: string = data.imageEncoding;
                        const imageData: string = data.imageData;
                        const encoded: string = `data:image/${imageType};${imageEncoding}, ${imageData}`;
                        setFrameData(encoded);
                    }
                    else {
                        console.error('error status when getting image frame from server');
                    }

                    break;
                default:
                    console.warn('unknown message: ', arg);
                    break;
            }
        });
    }, []);

    // render message
    return (
        <>
            <div>{message}</div>
            <button onClick={() => {
                const messageObj = {
                    name: 'start-renderer',
                    data: {
                        "createdAt": Date.now()
                    }
                };

                ipcRenderer.send('asynchronous-message', messageObj);
            }}>Start Renderer</button>
            { frameData &&
                <img src={frameData}></img>
            }
        </>
    );
};

ReactDOM.render(<Index />, document.getElementById('app'));
