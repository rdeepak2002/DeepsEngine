import React from "react";
import {Text, View} from "react-native";
import TransformComponentInput from "./TransformComponentInput";
import {Transform, TransformStr} from "../interfaces";
import {capitalizeFirstLetter} from "../util/string-utils";

interface TransformInputProps {
    entitySelected: number;
    transformStr: TransformStr;
    setTransformStr: Function;
    transformVal: Transform;
    setTransformVal: Function;
    style?: any;
}

const TransformInput = (props: TransformInputProps) => {
    return(
        <View style={[props.style || {}, {display: 'flex', flexDirection: 'column'}]}>
            <View>
                <Text>Transform</Text>
            </View>
            {['position', 'rotation', 'scale'].map((transformComponentName, key) => {
                return (
                    <View key={`${props.entitySelected}-${transformComponentName}-${key}`} style={{display: 'flex', flexDirection: 'row'}}>
                        <View style={{flexGrow: 1}}>
                            <Text>{capitalizeFirstLetter(transformComponentName)}</Text>
                        </View>
                        {['x', 'y', 'z'].map((vec3ComponentName, key) => {
                            return (
                                <View key={`${props.entitySelected}-${transformComponentName}-${vec3ComponentName}-${key}`}  style={{display: 'flex', flexDirection: 'row'}}>
                                    <View style={{width: 10, marginRight: 10}}>
                                        <Text>{(vec3ComponentName).toUpperCase()}</Text>
                                    </View>
                                    <TransformComponentInput
                                        style={{width: 50, marginRight: 10}}
                                        vec3Name={transformComponentName as any}
                                        vec3Component={vec3ComponentName as any}
                                        transformStr={props.transformStr}
                                        setTransformStr={props.setTransformStr}
                                        transformVal={props.transformVal}
                                        setTransformVal={props.setTransformVal}
                                    />
                                </View>
                            );
                        })}
                    </View>
                );
            })}
        </View>
    );
}

export default TransformInput;