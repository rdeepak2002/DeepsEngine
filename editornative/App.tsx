import React from "react";
import {Animated, Button, Dimensions, Image, PanResponder, StyleSheet, Text, TouchableOpacity, View} from 'react-native';
import {getEntitiesData, imageData, messageData, playModeData} from "./src/interfaces";
import {ipcRenderer} from "electron";
import DeepsViewTriplePane from "./src/components/deeps-engine-ui/DeepsViewTriplePane";
import DeepsViewDoublePane from "./src/components/deeps-engine-ui/DeepsViewDoublePane";
import SceneViewEntity from "./src/components/SceneViewEntity";
import Inspector from "./src/components/Inspector";

// @ts-ignore
import play_btn from "./assets/icons/play_btn.png";
import {capitalizeFirstLetter} from "./src/util/string-utils";
import TransformComponentInput from "./src/components/TransformComponentInput";

export default function App() {
    // frame data to display from engine
    const [frameData, setFrameData] = React.useState<string>('');
    const [imageDimensions, setImageDimensions] = React.useState<any>({width: 100, height: 100});

    const [screenWidth, setScreenWidth] = React.useState<number>(Dimensions.get('window').width);
    const [screenHeight, setScreenHeight] = React.useState<number>(Dimensions.get('window').height);

    const [playMode, setPlayMode] = React.useState<boolean>(false);
    const [entitySelected, setEntitySelected] = React.useState<number>(-1);
    const [entities, setEntities] = React.useState<Array<number>>([]);

    // resize the editor
    const handleEditorResize = (width: number, height: number) => {
        if (width && height) {
            const messageObj = {
                name: 'handle-editor-resize',
                data: {
                    "width": width,
                    "height": height
                }
            };

            ipcRenderer.send('asynchronous-message', messageObj);
        }
    }

    // add entity
    const addEntity = (entityName: string) => {
        const messageObj = {
            name: 'add-entity',
            data: {
                "name": entityName
            }
        };

        ipcRenderer.send('asynchronous-message', messageObj);
    }

    // move camera
    const handleEditorDragging = (dx: number, dy: number) => {
        const messageObj = {
            name: 'handle-editor-dragging',
            data: {
                "dx": dx,
                "dy": dy
            }
        };

        ipcRenderer.send('asynchronous-message', messageObj);
    }

    // shutdown
    const shutDownRenderer = () => {
        const messageObj = {
            name: 'shutdown-renderer',
            data: {
                "createdAt": Date.now()
            }
        };

        ipcRenderer.send('asynchronous-message', messageObj);
    }

    // get entities
    const getEntities = () => {
        const messageObj = {
            name: 'get-entities',
            data: {}
        };

        ipcRenderer.send('asynchronous-message', messageObj);
    }

    // start renderer
    const startRenderer = () => {
        // start renderer
        const messageObj = {
            name: 'start-renderer',
            data: {
                "createdAt": Date.now()
            }
        };

        ipcRenderer.send('asynchronous-message', messageObj);
    }

    // play mode
    const turnOnPlayMode = () => {
        const messageObj = {
            name: 'play-mode',
            data: {
                "createdAt": Date.now()
            }
        };

        ipcRenderer.send('asynchronous-message', messageObj);
    }

    // request for a new frame
    const requestForNewFrame = () => {
        const messageObj = {
            name: 'get-frame',
            data: {
                "createdAt": Date.now()
            }
        };

        ipcRenderer.send('asynchronous-message', messageObj);
    }

    // update the image frame
    const updateImageFrame = (data: imageData) => {
        const imageType: string = data.imageType;
        const imageEncoding: string = data.imageEncoding;
        const imageData: string = data.imageData;
        const encoded = `data:image/${imageType};${imageEncoding},${imageData}`;
        setFrameData(encoded);
    }

    const updatePlayState = (data: playModeData) => {
        setPlayMode(data.playMode);
    }

    const updateEntitiesArr = (data: getEntitiesData) => {
        setEntities(data.entities);
    }

    // handle message or reply received from server
    const messageHandler = (event: unknown, arg: messageData) => {
        // console.log('got reply', arg);

        // handle invalid reply
        if (!arg || !arg.name || !arg.data || !arg.status) {
            console.error('invalid reply format: ', arg);
            return;
        }

        // get data and status retrieved
        const status = arg.status;
        const data = arg.data;

        // failure status received
        if (status === 'failure') {
            return;
        }

        // handle valid reply
        switch (arg.name) {
            case 'get-entities':
                updateEntitiesArr(data as getEntitiesData);
                break;
            case 'new-frame-available':
                requestForNewFrame();
                break;
            case 'image-data':
                updateImageFrame(data as imageData);
                break;
            case 'update-play-state':
                updatePlayState(data as playModeData);
                break;
            default:
                console.warn('unknown message: ', arg);
                break;
        }
    }

    React.useEffect(() => {
        // get message or reply from server
        ipcRenderer.on('asynchronous-reply', messageHandler);
        ipcRenderer.on('asynchronous-message', messageHandler);

        startRenderer();
        getEntities();
    }, []);

    const panResponder = React.useRef(
        PanResponder.create({
            // Ask to be the responder:
            onStartShouldSetPanResponder: (evt, gestureState) => true,
            onStartShouldSetPanResponderCapture: (evt, gestureState) =>
                true,
            onMoveShouldSetPanResponder: (evt, gestureState) => true,
            onMoveShouldSetPanResponderCapture: (evt, gestureState) =>
                true,

            onPanResponderGrant: (evt, gestureState) => {
                // The gesture has started. Show visual feedback so the user knows
                // what is happening!
                // gestureState.d{x,y} will be set to zero now
            },
            onPanResponderMove: (evt, gestureState) => {
                // The most recent move distance is gestureState.move{X,Y}
                // The accumulated gesture distance since becoming responder is
                // gestureState.d{x,y}
                const scale = 0.01;
                const dx = gestureState.dx * scale;
                const dy = gestureState.dy * scale;

                console.log(dx, dy);
                handleEditorDragging(dx, dy);
            },
            onPanResponderTerminationRequest: (evt, gestureState) =>
                true,
            onPanResponderRelease: (evt, gestureState) => {
                // The user has released all touches while this view is the
                // responder. This typically means a gesture has succeeded
            },
            onPanResponderTerminate: (evt, gestureState) => {
                // Another component has become the responder, so this gesture
                // should be cancelled
            },
            onShouldBlockNativeResponder: (evt, gestureState) => {
                // Returns whether this component should block native components from becoming the JS
                // responder. Returns true by default. Is currently only supported on android.
                return true;
            }
        })
    ).current;

    return (
        <View style={{flex: 1}}>
            <DeepsViewDoublePane initHeight={screenHeight} initWidth={screenWidth} initRatio={[0.7, 0.3]}>
                <DeepsViewTriplePane initHeight={screenHeight} initWidth={screenWidth} horizontal
                                     initRatio={[0.2, 0.5, 0.3]}>
                    {/*scene view panel*/}
                    <View style={{display: 'flex', height: '100%'}}>
                        <View style={{flexGrow: 1, flexDirection: 'column'}}>
                            {entities.map((entityId, key) => {
                                return (
                                    <SceneViewEntity key={`entity-${entityId}-${key}`} entityId={entityId} selected={entitySelected} setSelected={setEntitySelected}/>
                                );
                            })}
                            {/*<SceneViewEntity entityId={0} selected={entitySelected} setSelected={setEntitySelected}/>*/}
                            {/*<SceneViewEntity entityId={1} selected={entitySelected} setSelected={setEntitySelected}/>*/}
                        </View>
                        <Button title='Add Entity' onPress={() => {
                            addEntity('cube');
                            getEntities();
                        }}/>
                    </View>
                    {/*rendered scene*/}
                    <View style={styles.container} {...panResponder.panHandlers} onLayout={(event) => {
                        const {x, y, width, height} = event.nativeEvent.layout;
                        setImageDimensions({
                            width: width,
                            height: height
                        });
                        // handleEditorResize(width, height);
                    }}>
                        <Image source={{uri: frameData}}
                               style={{width: imageDimensions.width, height: imageDimensions.height}}/>
                        {!playMode &&
                            <View style={styles.headerContainer}>
                                <TouchableOpacity onPress={() => {
                                    if (!playMode) {
                                        setPlayMode(true);
                                        turnOnPlayMode();
                                    }
                                }}/>
                                <Image style={{resizeMode: "cover", width: 20, height: 20}} source={play_btn}
                                       width={20} height={20}/>
                            </View>
                        }
                    </View>
                    {/*inspector*/}
                    <View style={{display: 'flex', height: '100%'}}>
                        <Inspector selected={entitySelected}/>
                    </View>
                </DeepsViewTriplePane>
                {/*console*/}
                <View>
                    <Text>TODO: console</Text>
                </View>
            </DeepsViewDoublePane>
            {playMode && <View
                style={{position: 'absolute', width: '100%', height: '100%', backgroundColor: 'rgba(0, 0, 0, 0.7)'}}/>}
        </View>
    );
}

const styles = StyleSheet.create({
    container: {
        width: '100%',
        flex: 1,
        backgroundColor: '#fff',
        alignItems: 'center',
        justifyContent: 'center'
    },
    image: {
        flex: 1,
        height: '100%',
        width: '100%'
    },
    headerContainer: {
        backgroundColor: 'rgba(0, 0, 0, 0.4)',
        position: 'absolute',
        width: '100%',
        top: 0,
        borderRadius: 1,
        padding: 5,
        display: 'flex',
        flexDirection: 'row',
        alignContent: 'center',
        alignItems: 'center',
        justifyContent: 'center'
    }
});
