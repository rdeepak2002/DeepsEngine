import React from "react";
import {View, Text, TextInput} from "react-native";

interface FloatInputProps {
    onChange: Function;
    value: string;
    placeholder: string;
    style?: any;
}

const FloatInput = (props: FloatInputProps) => {
    const filterFloatString = (str: string) => {
        let res: string = "";
        let hasPeriod = false;

        if(str.length <= 0) {
            return res;
        }

        for(let i: number = 0; i < str.length; i++) {
            let letter: string= str.charAt(i);

            if(letter === '-' && i === 0) {
                res += letter;
                continue;
            }

            if(letter === ".") {
                if(!hasPeriod)
                    res += ".";
                hasPeriod = true;
                continue;
            }

            const isNumber = !isNaN(Number(letter));

            if(isNumber) {
                res += letter;
            }
        }

        if(res === "-") {
            res = "-0";
        }

        if(res === "-.") {
            res = "-0.0";
        }

        if(res === ".") {
            res = "0.0"
        }

        if(res.trim() === "" || isNaN(parseFloat(res))) {
            res = "0"
        }

        return res;
    }

    return(
        <TextInput
            // style={styles.input}
            onChangeText={(value: string) => {
                let valueStr = filterFloatString(value.trim());
                if(valueStr.trim() === "") {
                    valueStr = "0";
                }
                props.onChange(valueStr);
            }}
            defaultValue={"0.0"}
            value={props.value}
            placeholder={props.placeholder}
            keyboardType="default"
            style={[props.style || {}]}
        />
    );
}

export default FloatInput;