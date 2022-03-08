import { Button, Stack, TextField } from '@mui/material'
import React, { useState } from 'react'
import CharacterDetails from './CharacterDetails';
import { CharacterDetail } from './CharacterDetails';

function CharacterSearch() {
    const [idToSearch, setIdToSearch] = useState('');
    const [loaded, setLoaded] = useState(false);
    const [characterDetails, setCharacterDetails] = useState<CharacterDetail>()

    const onClickHandler = async () => {
        try {
            setLoaded(false);

            const response = await fetch('http://localhost:5556/api/v1/characters/' + idToSearch);
            const myJson = await response.json(); //extract JSON from the http response

            if (response.status == 200) {
                console.log('SUCCESS');
                console.log(myJson);
                setCharacterDetails(myJson)
                setLoaded(true);
            }

        } catch (err) {
            console.log(err);
        }
    }

    return (
        <>
            <Stack direction="row" spacing={2}>
                <TextField onChange={(event) => { setIdToSearch(event.target.value) }} id="standard-basic" label="Enter Id" variant="standard" />
                <Button onClick={onClickHandler} variant="contained">Search</Button>
            </Stack>
            <CharacterDetails details={characterDetails} loaded={loaded} />
        </>
    )
}

export default CharacterSearch