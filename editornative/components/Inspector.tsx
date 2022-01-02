import React from "react";
import {View, Text} from "react-native";
import FloatInput from "./FloatInput";
import {genTransform, Transform, TransformStr} from "../interfaces";
import TransformComponentInput from "./TransformComponentInput";
import TransformInput from "./TransformInput";

interface InspectorProps {
    selected: number;
}

const Inspector = (props: InspectorProps) => {
    const [transformStr, setTransformStr] = React.useState<Transform | TransformStr>(genTransform());
    const [transformVal, setTransformVal] = React.useState<Transform>(genTransform());

    return(
        <View style={{flex: 1, overflow: 'scroll'}}>
            {
                (props.selected >= 0) ? (
                    <View  style={{display: 'flex', flexDirection: 'column'}}>
                        <Text>Entity {props.selected}</Text>
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
