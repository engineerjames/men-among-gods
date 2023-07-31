import { Dispatch, FunctionComponent, SetStateAction } from "react";
import { Stack, Divider, RadioGroup, FormControlLabel, FormControl, InputLabel, Select, MenuItem } from "@mui/material";
import { Radio } from "theme-ui";

interface PropType {
    name: string,
    pass: string,
    desc: string,
    sex: string,
    characterClass: string,
    onChangeName: Dispatch<SetStateAction<string>>,
    onChangePass: Dispatch<SetStateAction<string>>,
    onChangeDesc: Dispatch<SetStateAction<string>>,
    onChangeSex: Dispatch<SetStateAction<string>>,
    onChangeCharacterClass: Dispatch<SetStateAction<string>>,
}

const CharacterDetails: FunctionComponent<PropType> = (props) => {
    let isSexMale = () => {
        return props.sex === "male";
    }

    return <>
        <Stack spacing={2}>
            <input
                value={props.name}
                onChange={(e) => props.onChangeName(e.currentTarget.value)}
                required id="outlined-basic"
                placeholder="Character Name" />

            <input
                value={props.desc}
                onChange={(e) => props.onChangeDesc(e.currentTarget.value)}
                required id="outlined-basic"
                placeholder="Description"
                type="text" />

            <input
                value={props.pass}
                onChange={(e) => props.onChangePass(e.currentTarget.value)}
                required id="outlined-basic"
                placeholder="Password"
                type="password" />

            <Stack spacing={3} direction="row" divider={<Divider orientation="vertical" />} >
                Gender:
                <FormControl>
                    <RadioGroup
                        row
                        onClick={(event) => { event?.target?.value && props.onChangeSex(event?.target?.value) }}
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
                        value={props.characterClass}
                        label="Class"
                        onChange={(e) => { props.onChangeCharacterClass(e.target.value); }}
                    >
                        <MenuItem value="templar">Templar</MenuItem>
                        <MenuItem value="harakim">Harakim</MenuItem>
                        <MenuItem value="mercenary">Mercenary</MenuItem>
                    </Select>
                </FormControl>
            </Stack>
        </Stack>
    </>;
}

export default CharacterDetails;