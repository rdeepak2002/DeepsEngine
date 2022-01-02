import React from "react";
import {Text, TouchableOpacity, View} from "react-native";

interface SceneViewEntityProps {
    entityId: number;
    selected: number;
    setSelected: Function;
}

const SceneViewEntity = (props: SceneViewEntityProps) => {
    const isSelected = (props.entityId === props.selected);

    return (
        <TouchableOpacity onPress={() => {
            props.setSelected(props.entityId);
        }}>
            <View style={[isSelected ? {backgroundColor: 'rgba(0, 0, 0, 0.3)'} : {}]}>
                <Text>Entity {props.entityId}</Text>
            </View>
        </TouchableOpacity>
    );
}

export default SceneViewEntity;