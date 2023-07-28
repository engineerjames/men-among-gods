import { FunctionComponent, useState } from "react";
import { invoke } from "@tauri-apps/api/tauri";
import { Stack, Divider, CircularProgress, Backdrop } from "@mui/material";

async function play(name: string, pass: string) {
    await invoke("play", { name: name, pass: pass });
}

const CharacterDetails: FunctionComponent<{}> = () => {
    const [name, setName] = useState("");
    const [pass, setPass] = useState("");

    const [buttonsAreEnabled, setbuttonsAreEnabled] = useState(true);

    return <>
        <Stack spacing={2}>
            <input hidden={!buttonsAreEnabled} value={name} onChange={(e) => setName(e.currentTarget.value)} required id="outlined-basic" placeholder="Character Name" />
            <input hidden={!buttonsAreEnabled} value={pass} onChange={(e) => setPass(e.currentTarget.value)} required id="outlined-basic" placeholder="Password" type="password" />

            <Stack spacing={2} direction="row" divider={<Divider orientation="vertical" flexItem />} >
                <button hidden={!buttonsAreEnabled} onClick={() => {
                    setbuttonsAreEnabled(false);
                    play(name, pass);
                }}>Play</button>
                <button hidden={!buttonsAreEnabled} onClick={() => {
                    setName("");
                    setPass("");
                }}>New</button>
            </Stack>
        </Stack>
        <Backdrop
            sx={{ color: '#fff', zIndex: (theme) => theme.zIndex.drawer + 1 }}
            open={!buttonsAreEnabled}
        >
            <CircularProgress color="inherit" />
        </Backdrop>
    </>;
}

export default CharacterDetails;