import React from "react";
import {Text, View} from "react-native";
import {genTransform, Transform, TransformStr} from "../interfaces";
import TransformInput from "./TransformInput";
import {ipcRenderer} from "electron";

interface InspectorProps {
    selected: number;
}

const Inspector = (props: InspectorProps) => {
    const [transformStr, setTransformStr] = React.useState<Transform | TransformStr>(genTransform());
    const [transformVal, setTransformVal] = React.useState<Transform>(genTransform());

    // update component
    const updateComponent = (entityId: number, componentData: string) => {
        const messageObj = {
            name: 'update-component',
            data: {
                "entityId": entityId,
                "componentData": componentData,
                "createdAt": Date.now()
            }
        };

        ipcRenderer.send('asynchronous-message', messageObj);
    }

    React.useEffect(() => {
        const componentUpdateData = {
            transform: transformVal
        };

        updateComponent(0, JSON.stringify(componentUpdateData));
    }, [transformVal]);

    return (
        <View style={{flex: 1, overflow: 'scroll'}}>
            {
                (props.selected >= 0) ? (
                    <View style={{display: 'flex', flexDirection: 'column'}}>
                        <View style={{padding: 10}}>
                            <Text style={{fontWeight: 'bold', fontSize: 15}}>Entity {props.selected}</Text>
                        </View>
                        <TransformInput
                            entitySelected={props.selected}
                            transformStr={transformStr}
                            setTransformStr={setTransformStr}
                            transformVal={transformVal}
                            setTransformVal={setTransformVal}
                        />
                    </View>
                ) : (
                    <></>
                )
            }
        </View>
    );
}

export default Inspector;
