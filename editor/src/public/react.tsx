import * as ReactDOM from 'react-dom';
import * as React from 'react';
import {useEffect} from 'react';

import * as MUI from "@mui/material";
import {createTheme, PaletteMode} from "@mui/material";
import {getDesignTokens, useStyles} from "./theme";
import {imageData, messageData} from "./interfaces";

const electron = window.require('electron');
const {ipcRenderer} = electron;

const Index = () => {
    // message hook
    const [, setMessage] = React.useState('no message');
    const [frameData, setFrameData] = React.useState<string>('');
    const screenContainerRef = React.useRef<any>(null);

    const handleEditorResize = (width: number, height: number) => {
        const messageObj = {
            name: 'handle-editor-resize',
            data: {
                "width": width,
                "height": height
            }
        };

        ipcRenderer.send('asynchronous-message', messageObj);
    }

    const requestForNewFrame = () => {
        const messageObj = {
            name: 'get-frame',
            data: {
                "createdAt": Date.now()
            }
        };

        ipcRenderer.send('asynchronous-message', messageObj);
    }

    const updateImageFrame = (data: imageData) => {
        const imageType: string = data.imageType;
        const imageEncoding: string = data.imageEncoding;
        const imageData: string = data.imageData;
        const encoded = `data:image/${imageType};${imageEncoding}, ${imageData}`;
        setFrameData(encoded);
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
            case 'pong':
                setMessage(`gotPong: ${JSON.stringify(arg)}`);
                break;
            case 'new-frame-available':
                requestForNewFrame();
                break;
            case 'image-data':
                updateImageFrame(data as imageData);
                break;
            default:
                console.warn('unknown message: ', arg);
                break;
        }
    }

    React.useEffect(() => {
        window.addEventListener('resize', () => {
            if (screenContainerRef && screenContainerRef.current) {
                const newContainerWidth = screenContainerRef.current.offsetWidth;
                const newContainerHeight = screenContainerRef.current.offsetHeight;
                // console.log('ref change', newContainerWidth);
                handleEditorResize(newContainerWidth, newContainerHeight);
            }
        });
    }, [screenContainerRef]);

    React.useEffect(() => {
        // send ping message to server
        const messageObj = {
            name: 'ping',
            data: {
                "createdAt": Date.now()
            }
        };

        ipcRenderer.send('asynchronous-message', messageObj);

        // get message or reply from server
        ipcRenderer.on('asynchronous-reply', messageHandler);

        ipcRenderer.on('asynchronous-message', messageHandler);
    }, []);

    useEffect(() => {
        // automatically start renderer
        const messageObj = {
            name: 'start-renderer',
            data: {
                "createdAt": Date.now()
            }
        };

        ipcRenderer.send('asynchronous-message', messageObj);
    }, []);

    const [mode, setMode] = React.useState<PaletteMode>('dark');
    const colorMode = React.useMemo(
        () => ({
            // The dark mode switch would invoke this method
            toggleColorMode: () => {
                setMode((prevMode: PaletteMode) =>
                    prevMode === 'light' ? 'dark' : 'light',
                );
            },
        }),
        [],
    );

    const ColorModeContext = React.createContext({
        toggleColorMode: () => {
            console.log('unimplemented toggle color mode method')
        }
    });

    const theme = React.useMemo(() => createTheme(getDesignTokens(mode)), [mode]);
    const classes = useStyles();

    // render message
    return (
        <ColorModeContext.Provider value={colorMode}>
            <MUI.ThemeProvider theme={theme}>
                <MUI.CssBaseline>
                    <MUI.Grid container direction="column" justifyContent="center">
                        <MUI.Grid item xs={2}>
                            <MUI.Typography color="primary" variant="body1" align="center">
                                TODO: header with play button to run game
                            </MUI.Typography>
                        </MUI.Grid>

                        <MUI.Grid item xs={8} className={classes.hiddenOverflow}>
                            <MUI.Grid container direction="row" justifyContent="center">
                                <MUI.Grid item xs={3} className={classes.scrollOverflow}>
                                    <MUI.Typography color="primary" variant="body1" align="center">
                                        TODO: scene objects panel
                                    </MUI.Typography>
                                </MUI.Grid>

                                <MUI.Grid item xs={6} className={classes.screenViewContainer} ref={screenContainerRef}>
                                    <img src={frameData || 'loading'} className={classes.sceneViewScreen}/>
                                </MUI.Grid>

                                <MUI.Grid item xs={3} className={classes.scrollOverflow}>
                                    <MUI.Typography color="primary" variant="body1" align="center">
                                        TODO: inspector
                                    </MUI.Typography>
                                </MUI.Grid>
                            </MUI.Grid>
                        </MUI.Grid>

                        <MUI.Grid item xs={2}>
                            <MUI.Typography color="primary" variant="body1" align="center">
                                TODO: console
                            </MUI.Typography>
                        </MUI.Grid>
                    </MUI.Grid>
                </MUI.CssBaseline>
            </MUI.ThemeProvider>
        </ColorModeContext.Provider>
    );
};

ReactDOM.render(<Index/>, document.getElementById('app'));
