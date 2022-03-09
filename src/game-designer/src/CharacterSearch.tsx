import { Button, Stack, TextField } from '@mui/material'
import React, { useState } from 'react'
import CharacterDetails from './CharacterDetails';
import { CharacterDetail } from './CharacterDetails';

function CharacterSearch() {
    let [idToSearch, setIdToSearch] = useState('');
    let [nameToSearch] = useState('');
    const [loaded, setLoaded] = useState(false);
    const [characterDetails, setCharacterDetails] = useState<CharacterDetail>()

    const onClickHandler = async () => {
        try {
            setLoaded(false);

            const response = await fetch('http://localhost:5556/api/v1/characters/' + idToSearch);
            const myJson = await response.json(); //extract JSON from the http response

            if (response.status == 200) {
                console.log(myJson);
                setCharacterDetails(myJson)
                setLoaded(true);
            }

        } catch (err) {
            console.log(err);
        }
    }

    const onNameClickHandler = async () => {
        try {
            setLoaded(false);

            const response = await fetch('http://localhost:5556/api/v1/characters/name/' + nameToSearch);
            const myJson = await response.json(); //extract JSON from the http response

            if (response.status == 200) {
                console.log(myJson);
                //setCharacterDetails(myJson)
                //setLoaded(true);
            }

        } catch (err) {
            console.log(err);
        }
    }

    return (
        <>
            <Stack direction="row" spacing={2} margin={2}>
                <TextField onChange={(event) => { idToSearch = event.target.value; }} id="standard-basic" label="Enter Id" variant="standard" />
                <Button onClick={onClickHandler} variant="contained">Search</Button>
                <TextField onChange={(event) => { nameToSearch = event.target.value; }} id="standard-basic" label="Enter Name" variant="standard" />
                <Button onClick={onNameClickHandler} variant="contained">Search By Name</Button>
            </Stack>
            <CharacterDetails details={characterDetails} loaded={loaded} />
        </>
    )
}

export default CharacterSearch