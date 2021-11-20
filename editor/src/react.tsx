import * as React from 'react';
import * as ReactDOM from 'react-dom';

const electron = require('electron');
console.log(electron);

// console.log(core);

const Index = () => {
    return <div>Hello React!</div>;
};

ReactDOM.render(<Index />, document.getElementById('app'));
