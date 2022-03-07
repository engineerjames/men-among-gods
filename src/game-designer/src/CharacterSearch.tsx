import { Button, TextField } from '@mui/material'
import React, { useState } from 'react'
import CharacterDetails from './CharacterDetails';
import { CharacterDetailProps } from './CharacterDetails';

function CharacterSearch() {
    const [idToSearch, setIdToSearch] = useState('');
    const [loaded, setLoaded] = useState(false);
    const [characterDetails, setCharacterDetails] = useState<CharacterDetailProps>()

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
        <div>
            <TextField onChange={(event) => { setIdToSearch(event.target.value) }} id="standard-basic" label="Enter Id" variant="standard" />
            <Button onClick={onClickHandler} variant="contained">Search</Button>
            <CharacterDetails name={characterDetails?.name} 
                              description={characterDetails?.description}
                              loaded={loaded} />
        </div>
    )
}

export default CharacterSearch