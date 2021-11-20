import * as React from 'react';
import * as ReactDOM from 'react-dom';
import {useState} from "react";
const electron = require('electron');
const { ipcRenderer, remote } = electron;

const Index = () => {
    // message hook
    const [message, setMessage] = useState('no message');

    // send ping message to server
    ipcRenderer.send('asynchronous-message', 'ping');

    // get message from server
    ipcRenderer.on('asynchronous-reply', (event, arg) => {
        switch (arg) {
            case 'pong':
                setMessage('got pong');
                break;
        }
    })

    // render message
    return <div>{message}</div>;
};

ReactDOM.render(<Index />, document.getElementById('app'));
