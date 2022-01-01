import React from "react";
import {View, Text} from "react-native";

interface InspectorProps {
    selected: number;
}

const Inspector = (props: InspectorProps) => {
    return(
        <View style={{flex: 1}}>
            {
                (props.selected >= 0) ? (
                    <Text>
                        entity {props.selected}

                        <View style={{display: 'flex', flexDirection: 'row'}}>

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
