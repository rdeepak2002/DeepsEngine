import * as React from 'react';
import * as ReactDOM from 'react-dom';
import {useEffect, useState} from "react";
const electron = require('electron');
const { ipcRenderer, remote } = electron;

const Index = () => {
    // message hook
    const [message, setMessage] = useState('no message');

    useEffect(() => {
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
                    data: {}
                };

                ipcRenderer.send('asynchronous-message', messageObj);
            }}>Start Renderer</button>
        </>
    );
};

ReactDOM.render(<Index />, document.getElementById('app'));
