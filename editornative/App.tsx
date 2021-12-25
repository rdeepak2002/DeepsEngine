import React from "react";
import { StatusBar } from 'expo-status-bar';
import {
  Animated, Button,
  Dimensions,
  GestureResponderEvent,
  Image,
  PanResponder,
  PanResponderGestureState,
  StyleSheet,
  Text, TouchableOpacity,
  View
} from 'react-native';
import {imageData, messageData, playModeData} from "./interfaces";
import {ipcRenderer} from "electron";
import DeepsViewTriplePane from "./deeps-engine-ui/DeepsViewTriplePane";
import DeepsViewDoublePane from "./deeps-engine-ui/DeepsViewDoublePane";

export default function App() {
    // frame data to display from engine
    const [frameData, setFrameData] = React.useState<string>('');
    const [imageDimensions, setImageDimensions] = React.useState<any>({width: 100, height: 100});

    const [screenWidth, setScreenWidth] = React.useState<number>(Dimensions.get('window').width);
    const [screenHeight, setScreenHeight] = React.useState<number>(Dimensions.get('window').height);

    const [playMode, setPlayMode] = React.useState<boolean>(false);

  // resize the editor
  const handleEditorResize = (width: number, height: number) => {
    if(width && height) {
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
  }, []);

  return (
      <View style={{flex: 1}}>
        <DeepsViewDoublePane initHeight={screenHeight} initWidth={screenWidth} initRatio={[0.7, 0.3]}>
          <DeepsViewTriplePane initHeight={screenHeight} initWidth={screenWidth} horizontal initRatio={[0.2, 0.6, 0.2]}>
            <View>
              <Text>TODO: scene view</Text>
            </View>
            <View style={styles.container} onLayout={(event) => {
              const {x, y, width, height} = event.nativeEvent.layout;
              setImageDimensions({
                width: width,
                height: height
              });
              // handleEditorResize(width, height);
            }} >
              <Image source={{uri: frameData}} style={{width: imageDimensions.width, height: imageDimensions.height}}/>
              {!playMode &&
                  <TouchableOpacity style={styles.playBtn} onPress={() => {
                    if(!playMode) {
                      setPlayMode(true);
                      turnOnPlayMode();
                    }
                  }}>
                    <Text style={{color: 'white', fontSize: 20}}>Play</Text>
                  </TouchableOpacity>
              }
            </View>
            <View>
              <Text>TODO: inspector</Text>
            </View>
          </DeepsViewTriplePane>
          <View>
            <Text>TODO: console</Text>
          </View>
        </DeepsViewDoublePane>
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
  playBtn: {
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
