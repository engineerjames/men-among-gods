import { Checkbox, Divider, FormControlLabel, Stack, TextField } from '@mui/material';
import React, { useEffect, useState } from 'react'
import CharacterAttributes, { CharacterAttribute } from './CharacterAttributes';
import CharacterFlags from './CharacterFlags';
import CharacterSkills, { CharacterSkill } from './CharacterSkills';
import KindredDisplay from './KindredDisplay';
import TextDisplay from './TextDisplay';

export interface CharacterFlag {
    name: string;
    isActive: boolean;
}

export interface CharacterDetail {
    name?: string;
    description?: string;
    used?: number;
    x?: number;
    y?: number;
    alignment?: number;
    flags?: Array<CharacterFlag>;
    hp?: Array<number>;
    mana?: Array<number>;
    end?: Array<number>;
    attributes?: Array<CharacterAttribute>;
    skills?: Array<CharacterSkill>;
    kindred?: number;
    text?: Array<string>;
    id?: number;
}

export interface CharacterDetailProps {
    details?: CharacterDetail
    loaded: boolean;
}

const CharacterDetails = ({ details, loaded }: CharacterDetailProps) => {
    const positionString = `( ${details?.x}, ${details?.y} )`;
    const lifeString = `${details?.hp?.at(0)} / ${details?.end?.at(0)} / ${details?.mana?.at(0)}`;

    const [name, setName] = useState(details?.name);
    const [description, setDescription] = useState(details?.description);

    useEffect(() => {
        if (details?.name) {
            details.name = name;
        }

        if (details?.description) {
            details.description = description;
        }
    }, [name, description])


    if (loaded) {
        return (<>
            <Stack spacing={2}>
                <TextField id="filled-basic" label='Id' value={details?.id} variant="filled" InputProps={{ readOnly: true }} />
                <TextField id="filled-basic" label='Name' onChange={(event) => { setName(event.target.value); }} value={name} variant="filled" />
                <TextField id="filled-basic" label='Description' onChange={(event) => { setDescription(event.target.value); }} value={description} variant="filled" />

                <Stack spacing={3} direction="row" divider={<Divider orientation="vertical" flexItem />}>
                    <FormControlLabel control={<Checkbox />} label='Is Used' checked={details?.used === 1} />
                    <TextField id="filled-basic" label='Position' value={positionString} variant="filled" InputProps={{ readOnly: true }} />
                    <TextField id="filled-basic" label='Alignment' value={details?.alignment} variant="filled" InputProps={{ readOnly: true }} />
                    <TextField id="filled-basic" label='Hp/End/Mana' value={lifeString} variant="filled" InputProps={{ readOnly: true }} />
                </Stack>
                <CharacterFlags flags={details?.flags} />
                <CharacterAttributes attributes={details?.attributes} />
                <CharacterSkills skills={details?.skills} />
                <KindredDisplay kindred={details?.kindred} />
                <TextDisplay text={details?.text} />
            </Stack>
        </>
        )
    }
    else {
        return (<div></div>)
    }
}

export default CharacterDetails