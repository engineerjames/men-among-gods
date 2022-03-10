import { FormControl, FormControlLabel, FormLabel, Radio, RadioGroup } from '@mui/material';
import React, { useState } from 'react'

export enum Sex {
    None = 0,
    Male = 1,
    Female,
}

export interface SexSelectionProps {
    selectedSex: Sex;
}

function SexSelection(props: SexSelectionProps) {
    const [sex, setSex] = useState(props.selectedSex);

    const onSelectRadioButtonHandler = (sex: string) => {
        if (sex === 'female') {
            setSex(Sex.Female);
        }
        else if (sex === 'male') {
            setSex(Sex.Male);
        }
        else {
            console.log("Indeterminate sex: " + sex);
        }
    }

    return (
        <FormControl>
            <FormLabel id="demo-radio-buttons-group-label">Sex</FormLabel>
            <RadioGroup
                aria-labelledby="demo-radio-buttons-group-label"
                defaultValue="female"
                name="radio-buttons-group"
                row
            >
                <FormControlLabel value="female"
                    control={<Radio checked={sex === Sex.Female} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                    label="Female" />
                <FormControlLabel value="male"
                    control={<Radio checked={sex === Sex.Male} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                    label="Male" />
            </RadioGroup>
        </FormControl>)
}

export default SexSelection