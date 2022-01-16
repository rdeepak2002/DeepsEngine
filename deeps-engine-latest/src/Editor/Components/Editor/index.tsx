import React from "react";
import {Text, View} from "@nodegui/react-nodegui";
import {OpenGLCube} from "../OpenGLCube";

const Editor = () => {
    return(
        <View style={containerStyle}>
            <Text id="welcome-text">Welcome to NodeGui 🐕</Text>
            <OpenGLCube />
        </View>
    );
}

const containerStyle = `
  flex: 1;
`;

export default Editor;