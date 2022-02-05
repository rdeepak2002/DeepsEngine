import React, {useEffect} from "react";
import {Text, View, Button} from "@nodegui/react-nodegui";
import {OpenGLCube} from "../OpenGLCube";
import {widget} from "../OpenGLCube/OpenGLComponent";

const Editor = () => {
    // keep track of entities in scene
    const [entityIds, setEntityIds] = React.useState<string>("test1");

    // TODO: create function reference for every time a new entity is created (call this from napi)
    // TODO: then, call widget.getEntities() in there and set state

    // TODO: maybe have to upgrade node-gui to newer version?

    /**
     * Handle 'create entity' button being clicked
     */
    const createEntity = {
        clicked: () => {
            // create entity
            widget.createEntity();
        }
    };

    /**
     * Callback for every time a new entity is created
     */
    const onEntityCreated = () => {
        const entitiesJSON: string = JSON.stringify(widget.getEntities());
        console.log('entities list', entitiesJSON);
        // setEntityIds(entitiesJSON);
        // setEntityIds("test")
    }

    /**
     * Register callbacks
     */
    useEffect(() => {
        widget.setOnCreateEntityCb(onEntityCreated);
    });

    // render screen content
    return (
        <View style={twoRowContainerStyle}>
            <View style={topViewContainer}>
                <View style={threeColumnContainerStyle}>
                    <View style={sceneItemsContainer}>
                        <View>
                            <Text>test 1</Text>
                        </View>
                        <View>
                            <Text>test 2</Text>
                        </View>
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
    background-color: blue;
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