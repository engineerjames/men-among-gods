import { FunctionComponent, useState } from "react";
import { invoke } from "@tauri-apps/api/tauri";
import { Stack, Divider, CircularProgress, Backdrop, RadioGroup, FormControlLabel, FormControl, InputLabel, Select, MenuItem } from "@mui/material";
import { Radio } from "theme-ui";

const CharacterDetails: FunctionComponent<{}> = () => {
    const [name, setName] = useState("");
    const [pass, setPass] = useState("");
    const [desc, setDesc] = useState("");
    const [sex, setSex] = useState('male');
    const [buttonsAreEnabled, setbuttonsAreEnabled] = useState(true);
    const [characterClass, setCharacterClass] = useState('templar');

    let clearValues = () => {
        setName("");
        setPass("");
        setDesc("");
        setSex('male');
    }

    let isSexMale = () => {
        return sex === "male";
    }

    async function play() {
        let sexAsInt = sex === "male" ? 1 : 2;

        let characterClassAsInt = 1;
        switch (characterClass) {
            case "templar":
                characterClassAsInt = 1;
                break;
            case "harakim":
                characterClassAsInt = 2;
                break;
            case "mercenary":
                characterClassAsInt = 3;
                break;
            default:
                break;
        }


        await invoke("play", {
            name: name,
            pass: pass,
            desc: desc,
            sex: sexAsInt,
            race: characterClassAsInt
        });
    }

    return <>
        <Stack spacing={2}>

            <input hidden={!buttonsAreEnabled}
                value={name}
                onChange={(e) => setName(e.currentTarget.value)}
                required id="outlined-basic"
                placeholder="Character Name" />

            <input hidden={!buttonsAreEnabled}
                value={desc}
                onChange={(e) => setDesc(e.currentTarget.value)}
                required id="outlined-basic"
                placeholder="Description"
                type="text" />

            <input hidden={!buttonsAreEnabled}
                value={pass}
                onChange={(e) => setPass(e.currentTarget.value)}
                required id="outlined-basic"
                placeholder="Password"
                type="password" />

            <Stack spacing={3} direction="row" divider={<Divider orientation="vertical" />} >
                Gender:
                <FormControl>
                    <RadioGroup
                        row
                        onClick={(event) => { event?.target?.value && setSex(event?.target?.value) }}
                        aria-labelledby="demo-controlled-radio-buttons-group"
                        name="radio-buttons-group"
                    >
                        <FormControlLabel value="female" checked={!isSexMale()} control={<Radio />} label="Female" />
                        <FormControlLabel value="male" checked={isSexMale()} control={<Radio />} label="Male" />
                    </RadioGroup>
                </FormControl>

                <br />Class:
                <FormControl fullWidth>
                    <InputLabel id="demo-simple-select-label">Class</InputLabel>
                    <Select
                        labelId="demo-simple-select-label"
                        id="demo-simple-select"
                        value={characterClass}
                        label="Class"
                        onChange={(e) => { setCharacterClass(e.target.value); }}
                    >
                        <MenuItem value="templar">Templar</MenuItem>
                        <MenuItem value="harakim">Harakim</MenuItem>
                        <MenuItem value="mercenary">Mercenary</MenuItem>
                    </Select>
                </FormControl>
            </Stack>

            <Stack spacing={2} direction="row" divider={<Divider orientation="vertical" flexItem />} >
                <button hidden={!buttonsAreEnabled} onClick={() => {
                    setbuttonsAreEnabled(false);
                    play();
                }}>Play</button>
                <button hidden={!buttonsAreEnabled} onClick={() => {
                    clearValues()
                }}>New</button>
            </Stack>
        </Stack >
        <Backdrop
            sx={{ color: '#fff', zIndex: (theme) => theme.zIndex.drawer + 1 }}
            open={!buttonsAreEnabled}
        >
            <CircularProgress color="inherit" />
        </Backdrop>
    </>;
}

export default CharacterDetails;