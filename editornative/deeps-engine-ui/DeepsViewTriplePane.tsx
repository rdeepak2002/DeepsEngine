import React, {FC, useEffect, useRef} from "react";
import {Animated, Dimensions, PanResponder, StyleSheet, View} from "react-native";

type Props = {
    children: React.ReactNode;
    initHeight: number;
    initWidth: number;
    horizontal?: boolean;
    initRatio?: Array<number>;
};

// return content if use is logged in, otherwise navigate to landing page
const DeepsViewTriplePane: FC<Props> = (props: Props) => {
    // console.log(props.children);
    const childrenObj: any = props.children as any;
    const numChildren: number = Object.keys(childrenObj).length;

    const dividerSize = 5;
    const numDividers = 2;

    const [parentSize, setParentSize] = React.useState<number>(props.horizontal ? props.initWidth : props.initHeight);
    const [parentSizeWithoutDividers, setParentSizeWithoutDividers] = React.useState<number>(((props.horizontal ? props.initWidth : props.initHeight) || 40) - dividerSize * numDividers);

    const equalSize = (parentSizeWithoutDividers) / numChildren;
    const minSize = 40;

    const [containerSizes, setContainerSizes] = React.useState<Array<any>>([props.initRatio ? props.initRatio[0] * parentSizeWithoutDividers : equalSize, props.initRatio ? props.initRatio[1] * parentSizeWithoutDividers : equalSize, props.initRatio ? props.initRatio[2] * parentSizeWithoutDividers : equalSize]);
    const [minContainerSizes, setMinContainerSizes] = React.useState<Array<any>>([minSize, minSize, minSize]);
    const [isDividerClicked, setIsDividerClicked] = React.useState<Array<boolean>>([false, false]);

    // const newContainerSizes = [];
    // const newMinContainerSizes = [];
    //
    // for(let i = 0; i < numChildren; i++) {
    //     setContainerSizes([]);
    //     containerSizes.push(equalSize);
    //
    //     setMinContainerSizes([]);
    //     minContainerSizes.push(minSize);
    // }

    const newIsDividerClicked = [];

    for(let i = 0; i < numChildren - 1; i++) {
        newIsDividerClicked.push(false);
    }

    // useEffect(() => {
    //     console.warn("TODO: handle parent resizing");
    // }, [parentSize]);

    const createPanResponder = (index1: number, index2: number) => {
        const panResponder = React.useRef(
            PanResponder.create({
                // Ask to be the responder:
                onStartShouldSetPanResponder: (evt, gestureState) => true,
                onStartShouldSetPanResponderCapture: (evt, gestureState) => true,
                onMoveShouldSetPanResponder: (evt, gestureState) => true,
                onMoveShouldSetPanResponderCapture: (evt, gestureState) => true,
                onPanResponderGrant: (evt, gestureState) => {
                    const dividersCopy = isDividerClicked;
                    dividersCopy[index1] = true;
                    setIsDividerClicked([...dividersCopy]);
                },
                onPanResponderMove: (evt, gestureState) => {
                    const pageLoc =  props.horizontal ? evt.nativeEvent.pageX : evt.nativeEvent.pageY;
                    let previousSizes = 0;
                    for(let i = 0; i < index1; i++) {
                        previousSizes += containerSizes[i] + dividerSize;
                    }
                    let newSize1 = pageLoc - previousSizes;

                    let maxContainerSize = (containerSizes[index1] + containerSizes[index2]) - minContainerSizes[index2]

                    if(newSize1 < minContainerSizes[index1]) {
                        newSize1 = minContainerSizes[index1];
                    }
                    else if(newSize1 > maxContainerSize) {
                        newSize1 = maxContainerSize;
                    }

                    const size1 = newSize1;
                    const size2 = (containerSizes[index1] + containerSizes[index2]) - size1;

                    const containerSizesCopy = containerSizes;

                    containerSizesCopy[index1] = size1;
                    containerSizesCopy[index2] = size2;

                    setContainerSizes([...containerSizesCopy]);
                },
                onPanResponderTerminationRequest: (evt, gestureState) => true,
                onPanResponderRelease: (evt, gestureState) => {
                    const dividersCopy = isDividerClicked;
                    dividersCopy[index1] = false;
                    setIsDividerClicked([...dividersCopy]);
                },
                onPanResponderTerminate: (evt, gestureState) => {
                    const dividersCopy = isDividerClicked;
                    dividersCopy[index1] = false;
                    setIsDividerClicked([...dividersCopy]);
                },
                onShouldBlockNativeResponder: (evt, gestureState) => true
            })
        ).current;

        return panResponder;
    }

    return (
        <View style={[{display: 'flex', flexDirection: props.horizontal ? 'row' : 'column'}, {width: '100%'}, {height: '100%'}]}>
            <Animated.View style={[{backgroundColor: 'white'}, props.horizontal ? {minWidth: minContainerSizes[0]} : {minHeight: minContainerSizes[0]}, props.horizontal ? {width: containerSizes[0]} : {height: containerSizes[0]}]}>
                {childrenObj[0]}
            </Animated.View>

            <View style = {[props.horizontal ? {width: dividerSize} : {height: dividerSize}, isDividerClicked[0] ? {backgroundColor: '#666'} : {backgroundColor: '#e2e2e2'}]} {...createPanResponder(0, 1).panHandlers} />

            <Animated.View style={[{backgroundColor: 'white'},  props.horizontal ? {minWidth: minContainerSizes[1]} : {minHeight: minContainerSizes[1]}, props.horizontal ? {width: containerSizes[1]} : {height: containerSizes[1]}]}>
                {childrenObj[1]}
            </Animated.View>

            <View style = {[props.horizontal ? {width: dividerSize} : {height: dividerSize}, isDividerClicked[1] ? {backgroundColor: '#666'} : {backgroundColor: '#e2e2e2'}]} {...createPanResponder(1, 2).panHandlers} />

            <Animated.View style={[{backgroundColor: 'white'},  props.horizontal ? {minWidth: minContainerSizes[2]} : {minHeight: minContainerSizes[2]}, props.horizontal ? {width: containerSizes[2]} : {height: containerSizes[2]}]}>
                {childrenObj[2]}
            </Animated.View>
        </View>
    );
}

export default DeepsViewTriplePane;
