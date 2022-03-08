import { Checkbox, FormControlLabel, FormGroup, Grid, Stack, TextField } from '@mui/material';
import React from 'react'

export interface CharacterDetailProps {

    name?: string;
    description?: string;
    loaded: boolean;
    used?: number;
}

//({ message }: AppProps) =>
const CharacterDetails = (props: CharacterDetailProps) => {

    console.log(props);

    if (props.loaded) {
        return (<>
            <Stack spacing={2}>
                <FormGroup>
                <TextField id="standard-basic" label='Name' value={props.name} variant="standard" InputProps={{ readOnly: true }} />
                <TextField id="standard-basic" label='Description' value={props.description} variant="standard" InputProps={{ readOnly: true }} />
                <FormControlLabel disabled control={<Checkbox />} label='Is Used' checked={props.used == 1} />
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