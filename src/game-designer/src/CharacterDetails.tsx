import { TextField } from '@mui/material';
import React from 'react'

export interface CharacterDetailProps {

    name?: string;
    description?: string;
    loaded: boolean;
}

//({ message }: AppProps) =>
const CharacterDetails = (props: CharacterDetailProps) => {
    const { name, description, loaded, ...other } = props;

    console.log(name);

    if (loaded) {
        return (
            <div><TextField id="standard-basic" label={name} variant="standard" InputProps={{
                readOnly: true
            }} /></div>
        )
    }
    else {
        return (<div></div>)
    }
}

export default CharacterDetails