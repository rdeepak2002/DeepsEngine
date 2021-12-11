import * as React from 'react';
import {useEffect, useState} from 'react';
import * as ReactDOM from 'react-dom';

const electron = require('electron');
const {ipcRenderer, remote} = electron;

const Index = () => {
    // message hook
    const [message, setMessage] = useState('no message');
    const [frameData, setFrameData] = useState(undefined);

    const requestForNewFrame = () => {
        const messageObj = {
            name: 'get-frame',
            data: {
                "createdAt": Date.now()
            }
        };

        ipcRenderer.send('asynchronous-message', messageObj);
    }

    const updateImageFrame = (data) => {
        const imageType: string = data.imageType;
        const imageEncoding: string = data.imageEncoding;
        const imageData: string = data.imageData;
        const encoded: string = `data:image/${imageType};${imageEncoding}, ${imageData}`;
        setFrameData(encoded);
    }

    useEffect(() => {
        // TODO: use callback function for this / call every time render is called in electron
        // renderLoop();

        // send ping message to server
        const messageObj = {
            name: 'ping',
            data: {
                "createdAt": Date.now()
            }
        };

        ipcRenderer.send('asynchronous-message', messageObj);

        // handle message or reply received from server
        const messageHandler = (event, arg) => {
            // console.log('got reply', arg);

            // handle invalid reply
            if (!arg || !arg.name || !arg.data || !arg.status) {
                console.error('invalid reply format: ', arg);
                return;
            }

            // get data and status retrieved
            const status = arg.status;
            const data = arg.data;

            // failure status received
            if (status === 'failure') {
                return;
            }

            // handle valid reply
            switch (arg.name) {
                case 'pong':
                    setMessage(`gotPong: ${JSON.stringify(arg)}`);
                    break;
                case 'new-frame-available':
                    requestForNewFrame();
                    break;
                case 'image-data':
                    updateImageFrame(data);
                    break;
                default:
                    console.warn('unknown message: ', arg);
                    break;
            }
        }

        // get message or reply from server
        ipcRenderer.on('asynchronous-reply', messageHandler);

        ipcRenderer.on('asynchronous-message', messageHandler);
    }, []);

    // render message
    return (
        <>
            <div>{message}</div>
            <div>test</div>
            <button onClick={() => {
                const messageObj = {
                    name: 'start-renderer',
                    data: {
                        "createdAt": Date.now()
                    }
                };

                ipcRenderer.send('asynchronous-message', messageObj);
            }}>Start Renderer
            </button>
            {frameData &&
                <img style={{width: 300, height: 300}} src={frameData}/>
            }
        </>
    );
};

ReactDOM.render(<Index/>, document.getElementById('app'));
