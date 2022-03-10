import { Box, TextField } from '@mui/material'
import React from 'react'

export interface CharacterInputProps {
    name: string;
    description: string;
    password: string;
}

function CharacterInput() {
    return (
        <>
            <TextField
                required
                id="standard-required"
                label="Name"
                defaultValue=""
                variant="standard"
            />
            <TextField
                id="standard-password-input"
                label="Password"
                type="password"
                autoComplete="current-password"
                variant="standard"
            />
            <div>
                <TextField
                    id="filled-multiline-static"
                    label="Description"
                    helperText="Descriptions must be at least 10 characters and include your character name."
                    multiline
                    rows={4}
                    defaultValue=""
                    variant="filled"
                />
            </div>
        </>
    )
}

export default CharacterInput