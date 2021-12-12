import * as ReactDOM from 'react-dom';
import * as React from 'react';

import * as MUI from "@mui/material";
import {createTheme, PaletteMode} from "@mui/material";
import {makeStyles} from "@mui/styles";
import {useEffect} from "react";
import {getDesignTokens} from "./design-tokens";

const electron = window.require('electron');
const {ipcRenderer, remote} = electron;

const Index = () => {
    // message hook
    const [message, setMessage] = React.useState('no message');
    const [frameData, setFrameData] = React.useState<any>(undefined);

    const requestForNewFrame = () => {
        const messageObj = {
            name: 'get-frame',
            data: {
                "createdAt": Date.now()
            }
        };

        ipcRenderer.send('asynchronous-message', messageObj);
    }

    const updateImageFrame = (data: any) => {
        const imageType: string = data.imageType;
        const imageEncoding: string = data.imageEncoding;
        const imageData: string = data.imageData;
        const encoded = `data:image/${imageType};${imageEncoding}, ${imageData}`;
        setFrameData(encoded);
    }

    React.useEffect(() => {
        // send ping message to server
        const messageObj = {
            name: 'ping',
            data: {
                "createdAt": Date.now()
            }
        };

        ipcRenderer.send('asynchronous-message', messageObj);

        // handle message or reply received from server
        const messageHandler = (event: any, arg: any) => {
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
                    updateImageFrame(data);
                    break;
                default:
                    console.warn('unknown message: ', arg);
                    break;
            }
        }

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

    const ColorModeContext = React.createContext({toggleColorMode: () => {
        console.log('unimplemented toggle color mode method')
    }});

    const theme = React.useMemo(() => createTheme(getDesignTokens(mode)), [mode]);

    const useStyles = makeStyles((theme) => ({
        maxHeight: {
            height: "100%",
        },
    }));

    const classes = useStyles();

    // render message
    return (
        <ColorModeContext.Provider value={colorMode}>
            <MUI.ThemeProvider theme={theme}>
                <MUI.CssBaseline>
                    <MUI.Grid container direction="row" alignItems="stretch" justifyContent="center" className={classes.maxHeight}>
                        <MUI.Grid item xs>
                            <MUI.Typography color="primary" variant="body1" align="center">
                                TODO: scene objects panel
                            </MUI.Typography>
                        </MUI.Grid>

                        <MUI.Grid item>
                            <MUI.Grid container direction="column" alignItems="stretch" justifyContent="center">
                                <MUI.Grid item xs>
                                    <MUI.Typography color="primary" variant="body1" align="center">
                                        TODO: header with play button to run game
                                    </MUI.Typography>
                                </MUI.Grid>

                                <MUI.Grid item xs>
                                    {frameData ?
                                        (
                                            <img style={{width: 300, height: 300}} src={frameData}/>
                                        )
                                        :
                                        (
                                            <MUI.Typography color="primary" variant="body1" align="center">
                                                loading...
                                                {/*<MUI.Button variant="contained" onClick={() => {*/}
                                                {/*    const messageObj = {*/}
                                                {/*        name: 'start-renderer',*/}
                                                {/*        data: {*/}
                                                {/*            "createdAt": Date.now()*/}
                                                {/*        }*/}
                                                {/*    };*/}

                                                {/*    ipcRenderer.send('asynchronous-message', messageObj);*/}
                                                {/*}}>Start Renderer</MUI.Button>*/}
                                            </MUI.Typography>
                                        )
                                    }
                                </MUI.Grid>

                                <MUI.Grid item xs>
                                    <MUI.Typography color="primary" variant="body1" align="center">
                                        TODO: console
                                    </MUI.Typography>
                                </MUI.Grid>
                            </MUI.Grid>
                        </MUI.Grid>

                        <MUI.Grid item xs>
                            <MUI.Typography color="primary" variant="body1" align="center">
                                TODO: inspector
                            </MUI.Typography>
                        </MUI.Grid>
                    </MUI.Grid>


                </MUI.CssBaseline>
            </MUI.ThemeProvider>
        </ColorModeContext.Provider>
    );
};

ReactDOM.render(<Index/>, document.getElementById('app'));
