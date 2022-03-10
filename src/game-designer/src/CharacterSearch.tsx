import { Button, Pagination, Stack, TextField } from '@mui/material'
import React, { useState } from 'react'
import CharacterDetails from './CharacterDetails';
import { CharacterDetail } from './CharacterDetails';

function CharacterSearch() {
    let [idToSearch, setIdToSearch] = useState('');
    let [nameToSearch, setNameToSearch] = useState('');
    const [loaded, setLoaded] = useState(false);
    const [characterDetails, setCharacterDetails] = useState<CharacterDetail>();
    const [multiCharacterDetails, setMultiCharacterDetails] = useState<Array<CharacterDetail>>();
    const [page, setPage] = useState(0);

    const handlePageChange = moduleHandlePageChange(setPage);
    const onClickHandler = moduleClickHandler(setLoaded, setMultiCharacterDetails, idToSearch, setCharacterDetails);
    const onNameClickHandler = moduleOnNameClickHandler(setLoaded, setCharacterDetails, nameToSearch, setMultiCharacterDetails);
    const onSaveChangesHandler = moduleOnSaveChangesHandler(characterDetails, multiCharacterDetails, page);

    const onCopyTemplateHandler = async () => {
        // API should return the new template so that way we can load it on the screen
        // for editing
        if (!multiCharacterDetails && !characterDetails) {
            console.log("No loaded template.");
            return;
        }

        let id: number | undefined = 0;
        if (multiCharacterDetails) {
            id = multiCharacterDetails[page]?.id;
        }
        else {
            id = characterDetails?.id;
        }

        const response = await fetch('http://localhost:5556/api/v1/characters/' + id + '/copy', {
            method: "POST"
        });

        const newestId = await response.json(); //extract JSON from the http response

        if (response.status == 200) {
            setIdToSearch(newestId.id);
            moduleClickHandler(setLoaded, setMultiCharacterDetails, newestId.id, setCharacterDetails)();
        }
    }

    return (
        <>
            <Stack direction="row" spacing={2} margin={2}>
                <TextField value={idToSearch}
                    onChange={(event) => {
                        setIdToSearch(event.target.value);
                        setCharacterDetails(undefined);
                        setMultiCharacterDetails(undefined);
                    }}
                    id="standard-basic" label="Enter Id" variant="standard" />
                <Button onClick={onClickHandler} variant="contained">Search</Button>
                <TextField value={nameToSearch}
                    onChange={(event) => {
                        setNameToSearch(event.target.value);
                        setMultiCharacterDetails(undefined);
                        setCharacterDetails(undefined);
                    }}
                    id="standard-basic" label="Enter Name" variant="standard" />
                <Button onClick={onNameClickHandler} variant="contained">Search By Name</Button>
                <Button onClick={onCopyTemplateHandler} variant="contained">Copy Template</Button>
                <Button onClick={onSaveChangesHandler} variant="contained">Save Changes</Button>
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

function moduleOnSaveChangesHandler(characterDetails: CharacterDetail | undefined, multiCharacterDetails: Array<CharacterDetail> | undefined, page: number) {
    return async () => {
        try {
            let detailsToSave: CharacterDetail = {};
            if (characterDetails) {
                detailsToSave = characterDetails;
            }
            else if (multiCharacterDetails) {
                detailsToSave = multiCharacterDetails[page];
            }
            else {
                console.log("No character details capable of saving.");
            }

            const response = await fetch('http://localhost:5556/api/v1/characters/' + detailsToSave.id + '/update',
                {
                    method: "PUT",
                    headers: {
                        'Content-Type': 'application/json',
                        'Access-Control-Allow-Origin': '*',
                    },
                    body: JSON.stringify(detailsToSave)
                });

            const myJson = await response.json(); //extract JSON from the http response

            if (response.status == 200) {
                console.log('SUCCESS');
                console.log(myJson);
            }
        }
        catch (err) {
            console.log(err);
        }
    };
}

function moduleHandlePageChange(setPage: React.Dispatch<React.SetStateAction<number>>) {
    return (event: React.ChangeEvent<unknown>, value: number) => {
        setPage(value - 1);
    };
}

function moduleOnNameClickHandler(setLoaded: React.Dispatch<React.SetStateAction<boolean>>, setCharacterDetails: React.Dispatch<React.SetStateAction<CharacterDetail | undefined>>, nameToSearch: string, setMultiCharacterDetails: React.Dispatch<React.SetStateAction<CharacterDetail[] | undefined>>) {
    return async () => {
        try {
            setLoaded(false);
            setCharacterDetails(undefined);

            const response = await fetch('http://localhost:5556/api/v1/characters/name/' + nameToSearch);
            const myJson = await response.json(); //extract JSON from the http response

            if (response.status == 200) {
                setMultiCharacterDetails(myJson);
                setLoaded(true);
            }

        } catch (err) {
            console.log(err);
        }
    };
}

function moduleClickHandler(setLoaded: React.Dispatch<React.SetStateAction<boolean>>, setMultiCharacterDetails: React.Dispatch<React.SetStateAction<CharacterDetail[] | undefined>>, idToSearch: string, setCharacterDetails: React.Dispatch<React.SetStateAction<CharacterDetail | undefined>>) {
    return async () => {
        try {
            setLoaded(false);
            setMultiCharacterDetails(undefined);

            const response = await fetch('http://localhost:5556/api/v1/characters/' + idToSearch);
            const myJson = await response.json(); //extract JSON from the http response

            if (response.status == 200) {
                setCharacterDetails(myJson);
                setLoaded(true);
            }

        } catch (err) {
            console.log(err);
        }
    };
}
