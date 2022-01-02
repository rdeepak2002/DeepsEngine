import React from "react";
import {Image, Text, View} from "react-native";
import TransformComponentInput from "./TransformComponentInput";
import {Transform, TransformStr} from "../interfaces";
import {capitalizeFirstLetter} from "../util/string-utils";

// @ts-ignore
import transform_icon from "../../assets/icons/transform_icon.png";

interface TransformInputProps {
    entitySelected: number;
    transformStr: TransformStr;
    setTransformStr: Function;
    transformVal: Transform;
    setTransformVal: Function;
    style?: any;
}

const TransformInput = (props: TransformInputProps) => {
    return (
        <View style={[props.style || {}, {
            padding: 10,
            marginBottom: 10,
            display: 'flex',
            flexDirection: 'column',
            borderStyle: 'dotted',
            borderTopColor: 'black',
            borderBottomColor: 'black',
            borderTopWidth: 1,
            borderBottomWidth: 1
        }]}>
            <View style={{marginBottom: 10, display: 'flex', flexDirection: 'row', alignItems: 'center'}}>
                <Image style={{width: 25, height: 25}} source={transform_icon}/>
                <Text style={{fontWeight: 'bold', marginLeft: 10, fontSize: 15}}>Transform</Text>
            </View>
            {['position', 'rotation', 'scale'].map((transformComponentName, key) => {
                return (
                    <View key={`${props.entitySelected}-${transformComponentName}-${key}`}
                          style={{marginBottom: 5, display: 'flex', flexDirection: 'row'}}>
                        <View style={{flexGrow: 1}}>
                            <Text>{capitalizeFirstLetter(transformComponentName)}</Text>
                        </View>
                        {['x', 'y', 'z'].map((vec3ComponentName, key) => {
                            return (
                                <View
                                    key={`${props.entitySelected}-${transformComponentName}-${vec3ComponentName}-${key}`}
                                    style={{display: 'flex', flexDirection: 'row'}}>
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