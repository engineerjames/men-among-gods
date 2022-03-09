import { Stack, Divider, FormControlLabel, Switch } from '@mui/material';
import React from 'react'

export interface KindredDisplayProps {
    kindred?: number;
}

const KIN_MERCENARY = (1 << 0);
const KIN_SEYAN_DU = (1 << 1);
const KIN_PURPLE = (1 << 2);
const KIN_MONSTER = (1 << 3);
const KIN_TEMPLAR = (1 << 4);
const KIN_ARCHTEMPLAR = (1 << 5);
const KIN_HARAKIM = (1 << 6);
const KIN_MALE = (1 << 7);
const KIN_FEMALE = (1 << 8);
const KIN_ARCHHARAKIM = (1 << 9);
const KIN_WARRIOR = (1 << 10);
const KIN_SORCERER = (1 << 11);

const getFlagsFromKindred = (kindred: number) => {
    const isMale = Boolean(kindred & KIN_MALE);
    const isFemale = Boolean(kindred & KIN_FEMALE);
    const isMercenary = Boolean(kindred & KIN_MERCENARY);
    const isSeyanDu = Boolean(kindred & KIN_SEYAN_DU);
    const isPurple = Boolean(kindred & KIN_PURPLE);
    const isMonster = Boolean(kindred & KIN_MONSTER);
    const isTemplar = Boolean(kindred & KIN_TEMPLAR);
    const isArchTemplar = Boolean(kindred & KIN_ARCHTEMPLAR);
    const isHarakim = Boolean(kindred & KIN_HARAKIM);
    const isArchHarakim = Boolean(kindred & KIN_ARCHHARAKIM);
    const isWarrior = Boolean(kindred & KIN_WARRIOR);
    const isSorceror = Boolean(kindred & KIN_SORCERER);

    return {
        isMale: isMale,
        isFemale: isFemale,
        isMercenary: isMercenary,
        isSeyanDu: isSeyanDu,
        isPurple: isPurple,
        isMonster: isMonster,
        isTemplar: isTemplar,
        isArchTemplar: isArchTemplar,
        isHarakim: isHarakim,
        isArchHarakim: isArchHarakim,
        isWarrior: isWarrior,
        isSorceror: isSorceror,
    }
}

function KindredDisplay(props: KindredDisplayProps) {
    if (!props?.kindred) {
        return (<></>);
    }

    const flags = getFlagsFromKindred(props?.kindred);

    return (
        <>
            <h3>Kindred Flags</h3>
            <Stack spacing={3} direction="row" divider={<Divider orientation="vertical" flexItem />}>
                <FormControlLabel control={<Switch />} label='Male' checked={flags.isMale} />
                <FormControlLabel control={<Switch />} label='Female' checked={flags.isFemale} />
                <FormControlLabel control={<Switch />} label='Mercenary' checked={flags.isMercenary} />
                <FormControlLabel control={<Switch />} label='SeyanDu' checked={flags.isSeyanDu} />
                <FormControlLabel control={<Switch />} label='Purple' checked={flags.isPurple} />
                <FormControlLabel control={<Switch />} label='Monster' checked={flags.isMonster} />

            </Stack>
            <Stack spacing={3} direction="row" divider={<Divider orientation="vertical" flexItem />}>
                <FormControlLabel control={<Switch />} label='Templar' checked={flags.isTemplar} />
                <FormControlLabel control={<Switch />} label='ArchTemplar' checked={flags.isArchTemplar} />
                <FormControlLabel control={<Switch />} label='Harakim' checked={flags.isHarakim} />
                <FormControlLabel control={<Switch />} label='Arch-Harakim' checked={flags.isArchHarakim} />
                <FormControlLabel control={<Switch />} label='Warrior' checked={flags.isWarrior} />
                <FormControlLabel control={<Switch />} label='Sorceror' checked={flags.isSorceror} />
            </Stack>
        </>
    )
}

export default KindredDisplay