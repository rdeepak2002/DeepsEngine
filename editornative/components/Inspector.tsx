import React from "react";
import {View, Text} from "react-native";
import FloatInput from "./FloatInput";
import {genTransform, Transform, TransformStr} from "../interfaces";
import TransformComponentInput from "./TransformComponentInput";

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
                        <Text>entity {props.selected}</Text>
                        <View style={{display: 'flex', flexDirection: 'row'}}>
                            <View style={{flexGrow: 1}}>
                                <Text>Position</Text>
                            </View>
                            <View style={{width: 10, marginRight: 10}}>
                                <Text>X</Text>
                            </View>
                            <TransformComponentInput
                                style={{width: 50, marginRight: 10}}
                                vec3Name={'position'}
                                vec3Component={'x'}
                                transformStr={transformStr}
                                setTransformStr={setTransformStr}
                                transformVal={transformVal}
                                setTransformVal={setTransformVal}
                            />
                            <View style={{width: 10, marginRight: 10}}>
                                <Text>Y</Text>
                            </View>
                            <TransformComponentInput
                                style={{width: 50, marginRight: 10}}
                                vec3Name={'position'}
                                vec3Component={'y'}
                                transformStr={transformStr}
                                setTransformStr={setTransformStr}
                                transformVal={transformVal}
                                setTransformVal={setTransformVal}
                            />
                            <View style={{width: 10, marginRight: 10}}>
                                <Text>Z</Text>
                            </View>
                            <TransformComponentInput
                                style={{width: 50, marginRight: 10}}
                                vec3Name={'position'}
                                vec3Component={'z'}
                                transformStr={transformStr}
                                setTransformStr={setTransformStr}
                                transformVal={transformVal}
                                setTransformVal={setTransformVal}
                            />
                        </View>
                    </View>
                ) : (
                    <Text>Nothing Selected</Text>
                )
            }
        </View>
    );
}

export default Inspector;
