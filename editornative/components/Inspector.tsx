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
        <View style={{flex: 1}}>
            {
                (props.selected >= 0) ? (
                    <Text>
                        entity {props.selected}

                        <View style={{display: 'flex', flexDirection: 'row'}}>
                            <TransformComponentInput
                                vec3Name={'position'}
                                vec3Component={'x'}
                                transformStr={transformStr}
                                setTransformStr={setTransformStr}
                                transformVal={transformVal}
                                setTransformVal={setTransformVal}
                            />
                            {/*<FloatInput*/}
                            {/*    onChange={(value: string) => {*/}
                            {/*        const transformStrCopy = Object.assign({}, transformStr);*/}
                            {/*        transformStrCopy.position['x'] = value;*/}
                            {/*        setTransformStr(transformStr);*/}

                            {/*        const transformValCopy = Object.assign({}, transformVal);*/}
                            {/*        transformValCopy.position['x'] = parseFloat(value);*/}
                            {/*        setTransformVal(transformValCopy);*/}
                            {/*    }}*/}
                            {/*    value={transformStr.position['x'].toString()}*/}
                            {/*    placeholder={'x'}*/}
                            {/*/>*/}
                        </View>
                    </Text>
                ) : (
                    <Text>Nothing Selected</Text>
                )
            }
        </View>
    );
}

export default Inspector;
