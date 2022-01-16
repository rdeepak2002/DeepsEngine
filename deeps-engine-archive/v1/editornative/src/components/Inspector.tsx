import React from "react";
import {Text, View} from "react-native";
import {genTransform, Transform, TransformStr} from "../interfaces";
import TransformInput from "./TransformInput";
import {ipcRenderer} from "electron";

interface InspectorProps {
    selected: number;
}

const Inspector = (props: InspectorProps) => {
    // data of components associated to each entity
    const [entityComponentData, setEntityComponentData] = React.useState<any>({});

    // transform of the currently selected entity
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

    // persist component changes per entity to render in inspector
    React.useEffect(() => {
        if(!entityComponentData[props.selected]) {
            const entityComponentDataCopy = Object.assign({}, entityComponentData);

            // TODO: get all components associated with entity from engine
            entityComponentDataCopy[props.selected] = {
                "transformStr": genTransform(),
                "transform": genTransform()
            };

            setEntityComponentData(entityComponentDataCopy);

            // TODO: generalize this
            setTransformStr(entityComponentDataCopy[props.selected].transformStr);
            setTransformVal(entityComponentDataCopy[props.selected].transform);

            return;
        }

        // TODO: generalize this (also this is a clone of the above code)
        setTransformStr(entityComponentData[props.selected].transformStr);
        setTransformVal(entityComponentData[props.selected].transform);
    }, [props.selected]);

    // update component data whenever transform is updated
    React.useEffect(() => {
        const componentUpdateData = {
            transform: transformVal
        };

        if(props.selected >= 0) {
            updateComponent(props.selected, JSON.stringify(componentUpdateData));
        }
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
