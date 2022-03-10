import { FormControl, FormControlLabel, FormLabel, Radio, RadioGroup } from '@mui/material';
import React, { useState } from 'react'

export enum Race {
    None = 0,
    Templar,
    Harakim,
    Merecenary
}

export interface RaceSelectionProps {
    selectedRace: Race;
    setRace: React.Dispatch<React.SetStateAction<Race>>;
}

function SexSelection(props: RaceSelectionProps) {

    const onSelectRadioButtonHandler = (race: string) => {
        if (race === 'templar') {
            props.setRace(Race.Templar);
        }
        else if (race === 'harakim') {
            props.setRace(Race.Harakim);
        }
        else if (race === 'mercenary') {
            props.setRace(Race.Merecenary);
        }
        else {
            console.log("Indeterminate race: " + race);
        }
    }

    return (
        <FormControl sx={{m: 2}}>
            <FormLabel id="demo-radio-buttons-group-label">Race</FormLabel>
            <RadioGroup
                aria-labelledby="demo-radio-buttons-group-label"
                defaultValue="Templar"
                name="radio-buttons-group"
                row
            >
                <FormControlLabel value="templar"
                    control={<Radio checked={props.selectedRace === Race.Templar} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                    label="Templar" />
                <FormControlLabel value="mercenary"
                    control={<Radio checked={props.selectedRace === Race.Merecenary} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                    label="Mercenary" />
                <FormControlLabel value="harakim"
                    control={<Radio checked={props.selectedRace === Race.Harakim} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                    label="Harakim" />
            </RadioGroup>
        </FormControl>)
}

export default SexSelection