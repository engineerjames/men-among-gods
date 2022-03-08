import { Checkbox, Divider, FormControlLabel, FormGroup, Grid, Stack, TextField } from '@mui/material';
import React from 'react'


export interface CharacterDetail {
    name?: string;
    description?: string;
    used?: number;
    x?: number;
    y?: number;
    alignment?: number;
    flags?: Array<Boolean>;
    hp?: Array<number>;
    mana?: Array<number>;
    end?: Array<number>;
}

export interface CharacterDetailProps {
    details?: CharacterDetail
    loaded: boolean;
}

const CharacterDetails = ({ details, loaded }: CharacterDetailProps) => {

    const positionString = `( ${details?.x}, ${details?.y} )`;
    const lifeString = `${details?.hp?.at(0)} / ${details?.end?.at(0)} / ${details?.mana?.at(0)}`;

    if (loaded) {
        return (<>
            <h3>Character Template Details:</h3>
            <Stack spacing={2}>
                <TextField id="filled-basic" label='Name' value={details?.name} variant="filled" InputProps={{ readOnly: true }} />
                <TextField id="filled-basic" label='Description' value={details?.description} variant="filled" InputProps={{ readOnly: true }} />

                <Stack spacing={3} direction="row" divider={<Divider orientation="vertical" flexItem />}>
                    <FormControlLabel control={<Checkbox />} label='Is Used' checked={details?.used === 1} />
                    <TextField id="filled-basic" label='Position' value={positionString} variant="filled" InputProps={{ readOnly: true }} />
                    <TextField id="filled-basic" label='Alignment' value={details?.alignment} variant="filled" InputProps={{ readOnly: true }} />
                    <TextField id="filled-basic" label='Hp/Mana/End' value={lifeString} variant="filled" InputProps={{ readOnly: true }} />
                </Stack>
            </Stack>
        </>
        )
    }
    else {
        return (<div></div>)
    }
}

export default CharacterDetails