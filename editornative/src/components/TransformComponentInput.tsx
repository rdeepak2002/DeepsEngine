import React from "react";
import FloatInput from "./FloatInput";
import {Transform, TransformStr, Vec3, Vec3Str} from "../interfaces";

interface Vec3ComponentInput {
    vec3Name: 'position' | 'rotation' | 'scale';
    vec3Component: 'x' | 'y' | 'z';
    transformStr: TransformStr;
    setTransformStr: Function;
    transformVal: Transform;
    setTransformVal: Function;
    style?: any;
}

const TransformComponentInput = (props: Vec3ComponentInput) => {
    return(
        <FloatInput
            style={[props.style || {}]}
            onChange={(value: string) => {
                const transformStrCopy = Object.assign({}, props.transformStr);
                transformStrCopy[props.vec3Name][props.vec3Component] = value;
                props.setTransformStr(props.transformStr);

                const transformValCopy = Object.assign({}, props.transformVal);
                transformValCopy[props.vec3Name][props.vec3Component] = parseFloat(value);
                props.setTransformVal(transformValCopy);
            }}
            value={props.transformStr[props.vec3Name][props.vec3Component].toString()}
            placeholder={props.vec3Name}
        />
    );
}

export default TransformComponentInput;