import { QIcon } from "@nodegui/nodegui";
import { hot, Text, View, Window } from "@nodegui/react-nodegui";
import path from "path";
import React from "react";
import nodeguiIcon from "../../assets/nodegui.jpg";
import Editor from "./Components/Editor";

const minSize = { width: 1024, height: 768 };
const winIcon = new QIcon(path.resolve(__dirname, nodeguiIcon));

const App = () => {
  return (
      <Window
          windowIcon={winIcon}
          windowTitle="Deeps Engine"
          minSize={minSize}
          styleSheet={styleSheet}
      >
        <Editor />
      </Window>
  );
}

const styleSheet = `
  #welcome-text {
    font-size: 24px;
    padding-top: 20px;
    qproperty-alignment: 'AlignHCenter';
    font-family: 'sans-serif';
  }

  #step-1, #step-2 {
    font-size: 18px;
    padding-top: 10px;
    padding-horizontal: 20px;
  }
`;

export default hot(App);
