import React, {useEffect} from "react";
import {Text, View, Button} from "@nodegui/react-nodegui";
import {OpenGLCube} from "../OpenGLCube";
import {widget} from "../OpenGLCube/OpenGLComponent";

const Editor = () => {
    // keep track of entities in scene
    const [entityIds, setEntityIds] = React.useState<any>([]);

    // TODO: maybe have to upgrade react node-gui to newer version

    /**
     * Handle 'create entity' button being clicked
     */
    const handleCreateEntityButton = {
        clicked: () => {
            // create entity
            widget.createEntity();
        }
    };

    /**
     * Callback for every time a new entity is created
     */
    const onEntityCreated = () => {
        const entityIds: Array<string> = widget.getEntities();
        setEntityIds(entityIds);
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
                        {
                            entityIds.map((entityId: string) => (
                                <View key={entityId}>
                                    <Text>{entityId}</Text>
                                </View>
                            ))
                        }
                        <Button text={"Create Entity"} on={handleCreateEntityButton}/>
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
    height: 384;
    background-color: black;
`;

const bottomViewContainer = `
    height: 384;
    background-color: purple;
`;

const sceneItemsContainer = `
    width: 341;
    height: 384;
    background-color: blue;
`;

const rendererContainer = `
    width: 342;
    height: 384;
    background-color: red;
`;

const rendererScreen = `
    width: 342;
    height: 384;
`;

const inspectorContainer = `
    width: 341;
    height: 384;
    background-color: green;
`;


export default Editor;