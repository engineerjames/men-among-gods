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
}

function SexSelection(props: RaceSelectionProps) {
    const [race, setRace] = useState(props.selectedRace);

    const onSelectRadioButtonHandler = (race: string) => {
        if (race === 'templar') {
            setRace(Race.Templar);
        }
        else if (race === 'harakim') {
            setRace(Race.Harakim);
        }
        else if (race === 'mercenary') {
            setRace(Race.Merecenary);
        }
        else {
            console.log("Indeterminate race: " + race);
        }
    }

    return (
        <FormControl>
            <FormLabel id="demo-radio-buttons-group-label">Race</FormLabel>
            <RadioGroup
                aria-labelledby="demo-radio-buttons-group-label"
                defaultValue="Templar"
                name="radio-buttons-group"
                row
            >
                <FormControlLabel value="templar"
                    control={<Radio checked={race === Race.Templar} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                    label="Templar" />
                <FormControlLabel value="mercenary"
                    control={<Radio checked={race === Race.Merecenary} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                    label="Mercenary" />
                <FormControlLabel value="harakim"
                    control={<Radio checked={race === Race.Harakim} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                    label="Harakim" />
            </RadioGroup>
        </FormControl>)
}

export default SexSelection