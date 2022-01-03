import React from "react";
import {TextInput} from "react-native";

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

        if (str.length <= 0) {
            console.log('case 1');
            res = "0.0";
        }

        for (let i: number = 0; i < str.length; i++) {
            let letter: string = str.charAt(i);

            if (letter === "-" && i === 0) {
                res += "-";
                continue;
            }

            if (letter === ".") {
                if (!hasPeriod)
                    res += ".";
                hasPeriod = true;
                continue;
            }

            const isNumber = !isNaN(Number(letter));

            if (isNumber) {
                res += letter;
            }
        }

        if (res === "-") {
            console.log('case 2');
            res = "-0";
        }

        if (res === "-.") {
            console.log('case 3');
            res = "-0.0";
        }

        if (res === ".") {
            console.log('case 4');
            res = "0.0";
        }

        if(res === "-0") {
            console.log('case 5');
            res = "-0.0";
        }

        if(res.length >= 1 && res.charAt(res.length - 1) === ".") {
            console.log('case 6');
            res += "0";
            console.log('res', res);
        }

        if (res.trim() === "") {
            console.log('case 7');
            res = "0.0";
        }

        if(isNaN(parseFloat(res))) {
            console.log('case 8');
            res = "0.0";
        }

        return res;
    }

    return (
        <TextInput
            // style={styles.input}
            onChangeText={(value: string) => {
                const valueStr = filterFloatString(value.trim());
                props.onChange(valueStr);
            }}
            value={props.value}
            placeholder={props.placeholder}
            keyboardType="default"
            style={[props.style || {}]}
        />
    );
}

export default FloatInput;