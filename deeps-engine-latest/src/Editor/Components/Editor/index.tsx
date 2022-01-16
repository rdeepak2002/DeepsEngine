import React from "react";
import {Text, View, Button} from "@nodegui/react-nodegui";
import {OpenGLCube} from "../OpenGLCube";
import {widget} from "../OpenGLCube/OpenGLComponent";

const Editor = () => {
    const createEntity = {
        clicked: () => {
            console.log('button clicked, data from widget (2): ', widget.test());
        }
    };

    return (
        <View style={twoRowContainerStyle}>
            <View style={topViewContainer}>
                <View style={threeColumnContainerStyle}>
                    <View style={sceneItemsContainer}>
                        <Text id="text">Scene Items</Text>
                        <Button text={"Create Entity"} on={createEntity}/>
                    </View>
                    <View style={rendererContainer}>
                        <OpenGLCube style={rendererScreen}/>
                    </View>
                    <View style={inspectorContainer}>
                        <Text id="text">Inspector</Text>
                    </View>
                </View>
            </View>
            <View style={bottomViewContainer}>
                <Text id="text">Console</Text>
            </View>
        </View>
    );
}

const twoRowContainerStyle = `
  flex: 1;
  flex-direction: column;
`;

const threeColumnContainerStyle = `
  flex: 1;
  flex-direction: row;
`;

const topViewContainer = `
    flex: 0.9;
`;

const bottomViewContainer = `
    flex: 0.1;
`;

const sceneItemsContainer = `
    flex: 0.15;
`;

const rendererContainer = `
    flex: 0.7;
`;

const rendererScreen = `
    width: '100%';
    height: '100%';
`;

const inspectorContainer = `
    flex: 0.15;
`;


export default Editor;