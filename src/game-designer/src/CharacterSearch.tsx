import { Button, Pagination, Stack, TextField, Typography } from '@mui/material'
import React, { useState } from 'react'
import CharacterDetails from './CharacterDetails';
import { CharacterDetail } from './CharacterDetails';

function CharacterSearch() {
    let [idToSearch] = useState('');
    let [nameToSearch] = useState('');
    const [loaded, setLoaded] = useState(false);
    const [characterDetails, setCharacterDetails] = useState<CharacterDetail>();
    const [multiCharacterDetails, setMultiCharacterDetails] = useState<Array<CharacterDetail>>();
    const [page, setPage] = useState(0);

    const handlePageChange = (event: React.ChangeEvent<unknown>, value: number) => {
        setPage(value - 1);
    };

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
            setCharacterDetails(undefined);

            const response = await fetch('http://localhost:5556/api/v1/characters/name/' + nameToSearch);
            const myJson = await response.json(); //extract JSON from the http response

            if (response.status == 200) {
                console.log(myJson);
                setMultiCharacterDetails(myJson);
                setLoaded(true);
            }

        } catch (err) {
            console.log(err);
        }
    }
    
    const onCopyTemplateHandler = async () => {
        // API should return the new template so that way we can load it on the screen
        // for editing
        if (! multiCharacterDetails && ! characterDetails )
        {
            console.log("No loaded template.");
            return;
        }

        if (multiCharacterDetails)
        {
            console.log("COPY" + multiCharacterDetails[page]?.id)
        }
        else
        {
            console.log("COPY" + characterDetails?.id)
        }

        console.log("Not implemented yet");
    }

    return (
        <>
            <Stack direction="row" spacing={2} margin={2}>
                <TextField onChange={(event) => { idToSearch = event.target.value; }} id="standard-basic" label="Enter Id" variant="standard" />
                <Button onClick={onClickHandler} variant="contained">Search</Button>
                <TextField onChange={(event) => { nameToSearch = event.target.value; }} id="standard-basic" label="Enter Name" variant="standard" />
                <Button onClick={onNameClickHandler} variant="contained">Search By Name</Button>
                <Button onClick={onCopyTemplateHandler} variant="contained">Copy Template</Button>
            </Stack>
            {characterDetails && <CharacterDetails details={characterDetails} loaded={loaded} />}
            {multiCharacterDetails &&
                <>
                    <Pagination onChange={handlePageChange} count={multiCharacterDetails.length} shape="rounded" />
                    <CharacterDetails details={multiCharacterDetails[page]} loaded={loaded} />
                </>}
        </>
    )
}

export default CharacterSearch