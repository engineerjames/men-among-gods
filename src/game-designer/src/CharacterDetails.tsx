import { Checkbox, FormControlLabel, FormGroup, Grid, Stack, TextField } from '@mui/material';
import React from 'react'


export interface CharacterDetail {
    name?: string;
    description?: string;
    used?: number;
}

export interface CharacterDetailProps {
    details?: CharacterDetail
    loaded: boolean;
}

//({ message }: AppProps) =>
const CharacterDetails = ({details, loaded}: CharacterDetailProps) => {

    if (loaded) {
        return (<>
            <Stack spacing={2}>
                <FormGroup>
                    <TextField id="standard-basic" label='Name' value={details?.name} variant="standard" InputProps={{ readOnly: true }} />
                    <TextField id="standard-basic" label='Description' value={details?.description} variant="standard" InputProps={{ readOnly: true }} />
                    <FormControlLabel disabled control={<Checkbox />} label='Is Used' checked={details?.used == 1} />
                </FormGroup>
            </Stack>
        </>
        )
    }
    else {
        return (<div></div>)
    }
}

export default CharacterDetails