import { FormControl, FormControlLabel, FormLabel, Radio, RadioGroup } from '@mui/material';
import React from 'react'

export enum Sex {
    None = 0,
    Male = 1,
    Female,
}

export interface SexSelectionProps {
    selectedSex: Sex;
    setSex: React.Dispatch<React.SetStateAction<Sex>>;
}

function SexSelection(props: SexSelectionProps) {
    const onSelectRadioButtonHandler = (sex: string) => {
        if (sex === 'female') {
            props.setSex(Sex.Female);
        }
        else if (sex === 'male') {
            props.setSex(Sex.Male);
        }
        else {
            console.log("Indeterminate sex: " + sex);
        }
    }

    return (
        <FormControl sx={{m: 2}}>
            <FormLabel id="demo-radio-buttons-group-label">Sex</FormLabel>
            <RadioGroup
                aria-labelledby="demo-radio-buttons-group-label"
                defaultValue="female"
                name="radio-buttons-group"
                row
            >
                <FormControlLabel value="female"
                    control={<Radio checked={props.selectedSex === Sex.Female} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                    label="Female" />
                <FormControlLabel value="male"
                    control={<Radio checked={props.selectedSex === Sex.Male} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                    label="Male" />
            </RadioGroup>
        </FormControl>)
}

export default SexSelection