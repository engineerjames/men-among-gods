import { Accordion, AccordionDetails, AccordionSummary, Divider, FormControlLabel, Stack, Switch, Typography } from '@mui/material';
import ExpandMoreIcon from '@material-ui/icons/ExpandMore';
import React from 'react'
import { CharacterFlag } from './CharacterDetails';

export interface CharacterFlagsProps {
    flags?: Array<CharacterFlag>;
}

function FlagDisplay({ name, isActive }: CharacterFlag) {
    // Capitalize first letter of the flag
    name = name.at(0)?.toUpperCase() + name.substring(1);

    return (
        <>
            <Stack spacing={3} direction="row" divider={<Divider orientation="vertical" flexItem />}>
                <FormControlLabel control={<Switch />} label={name} checked={isActive} />
            </Stack>
        </>
    )

}

function CharacterFlags(props: CharacterFlagsProps) {

    const flagDisplays = [];

    if (props.flags == undefined || Object.entries(props.flags) == undefined) { return (<></>); }

    for (const [flagName, flag] of Object.entries(props.flags)) {
        flagDisplays.push(<FlagDisplay key={flagName} name={flagName} isActive={Boolean(flag)} />);
    }

    return (
        <div>
            <Accordion>
                <AccordionSummary expandIcon={<ExpandMoreIcon />} aria-controls="panel1a-content" id="panel1a-header" >
                    <Typography>Character Flags</Typography>
                </AccordionSummary>
                <AccordionDetails>
                    <Stack divider={<Divider orientation="horizontal" flexItem />}>
                        {flagDisplays}
                    </Stack>
                </AccordionDetails>
            </Accordion>
        </div>
    )
}

export default CharacterFlags