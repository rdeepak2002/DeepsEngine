import {PaletteMode} from "@mui/material";
import {makeStyles} from "@mui/styles";
// import {amber, deepOrange, grey} from "@mui/material/colors";

export const getDesignTokens = (mode: PaletteMode) => ({
    palette: {
        mode,
        ...(mode === 'light'
            ? {
                // palette values for light mode
                // primary: amber,
                // divider: amber[200],
                // text: {
                //     primary: grey[900],
                //     secondary: grey[800],
                // },
            }
            : {
                // palette values for dark mode
                // primary: deepOrange,
                // divider: deepOrange[700],
                // background: {
                //     default: deepOrange[900],
                //     paper: deepOrange[900],
                // },
                // text: {
                //     primary: '#fff',
                //     secondary: grey[500],
                // },
            }),
    },
});

export const useStyles = makeStyles(() => ({
    maxHeight: {
        height: "100%",
        maxHeight: "100%"
    },
    flexGrow:  {
        flexGrow: 1
    },
    screenViewContainer: {
        maxWidth: '500px',
        maxHeight: '500px'
    },
    sceneViewScreen: {
        width: '100%',
        height: '100%'
        // maxWidth: '100%',
        // maxHeight: '100%'
    },
    scrollOverflow: {
        overflow: 'scroll'
    },
    hiddenOverflow: {
        overflow: 'hidden'
    }
}));
