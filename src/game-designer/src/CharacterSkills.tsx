import { TableContainer, Paper, Table, TableHead, TableRow, TableCell, TableBody } from '@mui/material';
import React from 'react'

export interface CharacterSkill {
    data: Array<number>;
    name: string;
}

export interface CharacterSkillsProps {
    skills?: Array<CharacterSkill>;
}

function CharacterSkills(props: CharacterSkillsProps) {
    return (
        <>
        <h3>Character Skills</h3>
        <TableContainer component={Paper}>
            <Table sx={{ minWidth: 650 }} aria-label="simple table">
                <TableHead>
                    <TableRow>
                        <TableCell>Attribute Name</TableCell>
                        <TableCell align="right">Base Value</TableCell>
                        <TableCell align="right">Preset Modifier</TableCell>
                        <TableCell align="right">Maximum Value</TableCell>
                        <TableCell align="right">Difficulty to Raise [0-10]</TableCell>
                        <TableCell align="right">Dynamic Modifier (equip + spells)</TableCell>
                        <TableCell align="right">Total</TableCell>
                    </TableRow>
                </TableHead>
                <TableBody>
                    {props?.skills?.map((skill) => (
                        <TableRow
                            key={skill.name}
                            sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
                        >
                            <TableCell component="th" scope="row">
                                {skill.name}
                            </TableCell>
                            <TableCell align="right">{skill.data[0]}</TableCell>
                            <TableCell align="right">{skill.data[1]}</TableCell>
                            <TableCell align="right">{skill.data[2]}</TableCell>
                            <TableCell align="right">{skill.data[3]}</TableCell>
                            <TableCell align="right">{skill.data[4]}</TableCell>
                            <TableCell align="right">{skill.data[5]}</TableCell>

                        </TableRow>
                    ))}
                </TableBody>
            </Table>
        </TableContainer>
        </>
    )
}

export default CharacterSkills