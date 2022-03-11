import { FormControl, FormControlLabel, FormLabel, Radio, RadioGroup, Tooltip } from '@mui/material';
import React from 'react'

export enum Race {
    None = 0,
    Templar,
    Harakim,
    Mercenary,
    Seyan,
    ArchTemplar,
    ArchHarakim,
    Sorceror,
    Warrior,
    God,
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
            props.setRace(Race.Mercenary);
        }
        else if (race === 'archtemplar') {
            props.setRace(Race.ArchTemplar);
        }
        else if (race === 'archharakim') {
            props.setRace(Race.ArchHarakim);
        }
        else if (race === 'warrior') {
            props.setRace(Race.Warrior);
        }
        else if (race === 'sorceror') {
            props.setRace(Race.Sorceror);
        }
        else if (race === 'seyan') {
            props.setRace(Race.Seyan);
        }
        else if (race === 'god') {
            props.setRace(Race.God);
        }
        else {
            console.log("Indeterminate race: " + race);
        }
    }

    return (
        <FormControl sx={{ m: 2 }}>
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
                    control={<Radio checked={props.selectedRace === Race.Mercenary} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                    label="Mercenary" />
                <FormControlLabel value="harakim"
                    control={<Radio checked={props.selectedRace === Race.Harakim} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                    label="Harakim" />

                <Tooltip title={"This cannot be chosen--it must be earned."} >
                    <FormControlLabel value="seyan"
                        control={<Radio checked={props.selectedRace === Race.Seyan} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                        label="Seyan-Du" disabled />
                </Tooltip>
                <Tooltip title={"This cannot be chosen--it must be earned."} >
                    <FormControlLabel value="archtemplar"
                        control={<Radio checked={props.selectedRace === Race.ArchTemplar} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                        label="Arch-Templar" disabled />
                </Tooltip>
                <Tooltip title={"This cannot be chosen--it must be earned."} >
                    <FormControlLabel value="archharakim"
                        control={<Radio checked={props.selectedRace === Race.ArchHarakim} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                        label="Arch-Harakim" disabled />
                </Tooltip>
                <Tooltip title={"This cannot be chosen--it must be earned."} >
                    <FormControlLabel value="warrior"
                        control={<Radio checked={props.selectedRace === Race.Warrior} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                        label="Warrior" disabled />
                </Tooltip>
                <Tooltip title={"This cannot be chosen--it must be earned."} >
                    <FormControlLabel value="sorceror"
                        control={<Radio checked={props.selectedRace === Race.Sorceror} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                        label="Sorceror" disabled />
                </Tooltip>
                <Tooltip title={"This cannot be chosen--it must be earned."} >
                    <FormControlLabel value="god"
                        control={<Radio checked={props.selectedRace === Race.God} onChange={(event) => { onSelectRadioButtonHandler(event.target.value); }} />}
                        label="God" disabled />
                </Tooltip>
            </RadioGroup>
        </FormControl>)
}

export default SexSelection