import { TextField } from '@mui/material'
import React from 'react'

export interface CharacterInputProps {
    name: string;
    description: string;
    password: string;
    setName: React.Dispatch<React.SetStateAction<string>>;
    setDesc: React.Dispatch<React.SetStateAction<string>>;
    setPass: React.Dispatch<React.SetStateAction<string>>;
}

function CharacterInput(props: CharacterInputProps) {

    const handleNameChange = (newName: string) => {
        props.setName(newName);
    }

    const handlePassChange = (newDesc: string) => {
        props.setPass(newDesc);
    }

    const handleDescChange = (newPass: string) => {
        props.setDesc(newPass);
    }

    return (
        <>
            <TextField
                sx={{ m: 2 }}
                required
                id="standard-required"
                label="Name"
                value={props.name}
                variant="standard"
                onChange={(event) => { handleNameChange(event.target.value); }}
            />
            <TextField
                sx={{ m: 2 }}
                id="standard-password-input"
                label="Password"
                type="password"
                value={props.password}
                autoComplete="current-password"
                variant="standard"
                onChange={(event) => { handlePassChange(event.target.value); }}
            />
            <div>
                <TextField
                    sx={{ m: 2 }}
                    id="filled-multiline-static"
                    label="Description"
                    value={props.description}
                    helperText="Descriptions must be at least 10 characters and include your character name."
                    multiline
                    rows={4}
                    variant="filled"
                    onChange={(event) => { handleDescChange(event.target.value); }}
                />
            </div>
        </>
    )
}

export default CharacterInput