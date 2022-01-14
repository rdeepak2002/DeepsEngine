import { QIcon } from "@nodegui/nodegui";
import { hot, Text, View, Window } from "@nodegui/react-nodegui";
import path from "path";
import React from "react";
import nodeguiIcon from "../assets/nodegui.jpg";
import { OpenGLCube } from "./OpenGLCube";

const minSize = { width: 500, height: 520 };
const winIcon = new QIcon(path.resolve(__dirname, nodeguiIcon));
class App extends React.Component {
  render() {
    return (
      <Window
        windowIcon={winIcon}
        windowTitle="Hello 👋🏽"
        minSize={minSize}
        styleSheet={styleSheet}
      >
        <View style={containerStyle}>
          <Text id="welcome-text">Welcome to NodeGui 🐕</Text>
          <Text id="step-1">1. Play around</Text>
          <Text id="step-2">2. Debug</Text>
          <OpenGLCube />
        </View>
      </Window>
    );
  }
}

const containerStyle = `
  flex: 1;
`;

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
